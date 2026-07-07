#include "stm32_spi.h"
#include "emc_log.h"
#include "emc_gpio.h"
#include "emc_periph.h"
#include "stm32l4xx.h"

#include <stddef.h>

// SPI handle structure
typedef struct {
    SPI_RegDef_t *instance;          /**< SPI peripheral base address */
    emc_gpio_t sck_pin;              /**< SCK pin */
    emc_gpio_t miso_pin;             /**< MISO pin */
    emc_gpio_t mosi_pin;             /**< MOSI pin */
    uint8_t af;                      /**< Alternate function */
    emc_periph_t periph;            /**< Peripheral */
#if (SPI_USE_DMA)
    emc_dma_t dma_tx;               /**< DMA channel for TX */
    emc_dma_t dma_rx;               /**< DMA channel for RX */
#endif
} stm32_spi_hw_t;

static const stm32_spi_hw_t spi_desc[] = {
    // Populate SPI1 module
    [EMC_SPI1] = {
        .instance = SPI1,
        // SCK pin: PA5
        .sck_pin.port = EMC_GPIO_PORTA,
        .sck_pin.pin = 5,
        // MISO pin: PA6
        .miso_pin.port = EMC_GPIO_PORTA,
        .miso_pin.pin = 6,
        // MOSI pin: PA7
        .mosi_pin.port = EMC_GPIO_PORTA,
        .mosi_pin.pin = 7,
        .af = 5,
        .periph = EMC_PERIPH_SPI1
    },

    [EMC_SPI2] = {
        .instance = SPI2,
        // SCK pin: PB13
        .sck_pin.port = EMC_GPIO_PORTB,
        .sck_pin.pin = 13,
        // MISO pin: PB14
        .miso_pin.port = EMC_GPIO_PORTB,
        .miso_pin.pin = 14,
        // MOSI pin: PB15
        .mosi_pin.port = EMC_GPIO_PORTB,
        .mosi_pin.pin = 15,
        .af = 5,
        .periph = EMC_PERIPH_SPI2
    }

};

static SPI_RegDef_t *stm32_get_spi_instance(emc_spi_id_t spi_id)
{
    if (spi_id >= EMC_SPI_ALL) {
        return NULL;
    }
    return spi_desc[spi_id].instance;
}

static void stm32_spi_gpio_init(emc_spi_id_t spi_id)
{
    emc_gpio_config_t cfg;

    const stm32_spi_hw_t *desc = &spi_desc[spi_id];
    cfg.mode = EMC_GPIO_MODE_AF;
    cfg.otype = EMC_GPIO_OTYPE_PP;
    cfg.ospeed = EMC_GPIO_OSPEED_HIGH;
    cfg.pupd = EMC_GPIO_PUPD_NONE;
    cfg.alternate_function = desc->af;

    emc_gpio_init((emc_gpio_t *)&desc->sck_pin, &cfg);
    emc_gpio_init((emc_gpio_t *)&desc->miso_pin, &cfg);
    emc_gpio_init((emc_gpio_t *)&desc->mosi_pin, &cfg);

}

static void _stm32_spi_set_mode(SPI_RegDef_t *spi_instance, emc_spi_clock_mode_t mode)
{
    uint32_t reg = spi_instance->SPI_CR1;
    reg &= ~(SPI_CR1_CPOL | SPI_CR1_CPHA); // Clear bits

    switch (mode) {
        case EMC_SPI_MODE0:
            break;
        case EMC_SPI_MODE1:
            reg |= SPI_CR1_CPHA; 
            break;  
        case EMC_SPI_MODE2:
            reg |= SPI_CR1_CPOL; 
            break;
        case EMC_SPI_MODE3:
            reg |= (SPI_CR1_CPOL | SPI_CR1_CPHA); 
            break;
        default:
            break;
    }

    spi_instance->SPI_CR1 = reg;
}

static void _stm32_spi_set_transfer_mode(SPI_RegDef_t *spi_instance, emc_spi_transfer_mode_t transfer_mode)
{
    uint32_t reg = spi_instance->SPI_CR1;
    reg &= ~(SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE | SPI_CR1_RXONLY); // Clear bits

    switch (transfer_mode) {
        case EMC_SPI_FULL_DUPLEX:
            // Full-duplex mode
            break;
        case EMC_SPI_HALF_DUPLEX:
            reg |= SPI_CR1_BIDIMODE; // Half-duplex mode
            break;
        case EMC_SPI_SIMPLEX_RX:
            reg |= SPI_CR1_RXONLY; // Simplex receive-only mode
            break;
        case EMC_SPI_SIMPLEX_TX:
            reg |= (SPI_CR1_BIDIMODE | SPI_CR1_BIDIOE); // Simplex transmit-only mode
            break;
        default:
            // Invalid transfer mode
            break;
    }

    spi_instance->SPI_CR1 = reg;
}




static void _stm32_spi_set_baudrate_prescaler(SPI_RegDef_t *spi_instance, emc_spi_prescaler_t baudrate_prescaler)
{
    uint32_t reg = spi_instance->SPI_CR1;
    if (baudrate_prescaler > EMC_SPI_PRESCALER_256) {
        return;
    }

    reg &= ~SPI_CR1_BR; // Clear baud rate bits
    reg |= (baudrate_prescaler << SPI_CR1_BR_Pos) & SPI_CR1_BR_Msk; // Set new baud rate
    spi_instance->SPI_CR1 = reg;
}

static void _stm32_spi_config(SPI_RegDef_t *spi_instance, bool enable)
{
    if (enable) {
        spi_instance->SPI_CR1 |= SPI_CR1_SPE; // Enable SPI
    } else {
        spi_instance->SPI_CR1 &= ~SPI_CR1_SPE; // Disable SPI
    }
}


static void _stm32_spi_wait_txe(SPI_RegDef_t *spi_instance)
{
    while (!(spi_instance->SPI_SR & SPI_SR_TXE));
}

static void _stm32_spi_wait_rxne(SPI_RegDef_t *spi_instance)
{
    while(!(spi_instance->SPI_SR & SPI_SR_RXNE));
}

static void _stm32_spi_wait_bsy(SPI_RegDef_t *spi_instance)
{
    while(spi_instance->SPI_SR & SPI_SR_BSY);
}

static void _stm32_spi_flush_rxfifo(SPI_RegDef_t *spi_instance)
{
    while(spi_instance->SPI_SR & SPI_SR_RXNE) {
        (void)*((volatile uint8_t*)&spi_instance->SPI_DR);
    }
}

static void _stm32_spi_set_rxfifo_threshold(SPI_RegDef_t *spi_instance, uint32_t threshold)
{
    spi_instance->SPI_CR2 &= ~SPI_CR2_FRXTH;
    spi_instance->SPI_CR2 |= (threshold & SPI_CR2_FRXTH);
}

/**
 * @brief Transfer a byte over SPI bus (Polling method)
 * @param spi_instance Pointer to the SPI register
 * @param tx_data the byte to transmit
 * @return the received byte
 * 1- Wait until TXE flag is set (transmit buffer empty)
 * 2- Write the data to Data Register
 * 3- Wait until RXNE flag is set (receive buffer not empty)
 * 4- Read the received data from DR
 */
static uint8_t _stm32_spi_transfer_byte(SPI_RegDef_t *spi_instance, uint8_t tx_data)
{
    _stm32_spi_wait_txe(spi_instance);
    *((volatile uint8_t*)&spi_instance->SPI_DR) = tx_data;

    _stm32_spi_wait_rxne(spi_instance);
    return *((volatile uint8_t*)&spi_instance->SPI_DR);
}


static void _stm32_spi_select(const emc_spi_t *spi)
{
    if(!spi->cs.initialized) {
        return;
    }
    emc_gpio_write(&spi->cs.cs_gpio, spi->cs.active_low ? 0 : 1);
}

static void _stm32_spi_deselect(const emc_spi_t *spi)
{
    if(!spi->cs.initialized) {
        return;
    }
    emc_gpio_write(&spi->cs.cs_gpio, spi->cs.active_low ? 1 : 0);
}


/**
 * @brief Initialize the SPI peripheral with its configuration.
 * @param spi Pointer to the emc_spi_t structure
 */
emc_result_t stm32_spi_init(emc_spi_t *spi)
{
    if(spi == NULL || spi->id >= EMC_SPI_ALL) {
        return EMC_STATUS_ERR;
    }

    const stm32_spi_hw_t *desc = &spi_desc[spi->id];
    SPI_RegDef_t *spi_instance = desc->instance;
    
    if (spi_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_periph_enable(desc->periph);
    stm32_spi_gpio_init(spi->id);

    /* Configure Chip Select */
    if(spi->cs.initialized) {
        emc_gpio_config_t cs_cfg;
        cs_cfg.mode = EMC_GPIO_MODE_OUT;
        cs_cfg.otype = EMC_GPIO_OTYPE_PP;
        cs_cfg.ospeed = EMC_GPIO_OSPEED_HIGH;
        cs_cfg.pupd = EMC_GPIO_PUPD_NONE;

        emc_gpio_init(&spi->cs.cs_gpio, &cs_cfg);

        _stm32_spi_deselect(spi);
    }

    _stm32_spi_config(spi_instance, false); // Disable SPI

    spi_instance->SPI_CR1 = 0;
    spi_instance->SPI_CR2 = 0;
    // Software NSS
    spi_instance->SPI_CR1 |= SPI_CR1_SSM; 
    spi_instance->SPI_CR1 |= SPI_CR1_SSI; 

    if(spi->config.role == EMC_SPI_MASTER) {
        spi_instance->SPI_CR1 |= SPI_CR1_MSTR;
    } else {
        spi_instance->SPI_CR1 &= ~SPI_CR1_MSTR;
    }

    if(spi->config.lsb_first) {
        spi_instance->SPI_CR1 |= SPI_CR1_LSBFIRST;
    } else {
        spi_instance->SPI_CR1 &= ~SPI_CR1_LSBFIRST;
    }

    _stm32_spi_set_baudrate_prescaler(spi_instance, spi->config.prescaler);
    _stm32_spi_set_mode(spi_instance, spi->config.clock);
    _stm32_spi_set_transfer_mode(spi_instance, spi->config.transfer_mode);

    spi_instance->SPI_CR2 &= ~SPI_CR2_DS_Msk; // Clear data size bits
    spi_instance->SPI_CR2 |= ((spi->config.data_size - 1U) << SPI_CR2_DS_Pos);
    // RX FIFO threshold configuration
    if(spi->config.data_size <= 8) {
        spi_instance->SPI_CR2 |= SPI_CR2_FRXTH; // 8-bit threshold
    } else {
        spi_instance->SPI_CR2 &= ~SPI_CR2_FRXTH; // 16-bit threshold
    }

    _stm32_spi_config(spi_instance, true);

    EMC_LOGI("SPI", "SPI%d initialized: role=%s, mode=%d, prescaler=%d, data_size=%d, lsb_first=%d",
        spi->id + 1,
        (spi->config.role == EMC_SPI_MASTER) ? "MASTER" : "SLAVE",
        spi->config.clock,
        spi->config.prescaler + 1,
        spi->config.data_size,
        spi->config.lsb_first);

    return EMC_STATUS_OK;
}

emc_result_t stm32_spi_transfer(emc_spi_t *spi, const uint8_t *tx, uint8_t *rx, uint32_t length)
{
    if(spi == NULL || length == 0) {
        return EMC_STATUS_ERR;
    }

    SPI_RegDef_t *spi_instance = stm32_get_spi_instance(spi->id);
    if(spi_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    while(length--) {
        uint8_t tx_byte = 0xff;
        if(tx != NULL) {
            tx_byte = *tx++;
        }

        uint8_t rx_byte = _stm32_spi_transfer_byte(spi_instance, tx_byte);
        if(rx != NULL) {
            *rx++ = rx_byte;
        }
    }

    _stm32_spi_wait_txe(spi_instance);
    _stm32_spi_wait_bsy(spi_instance);
    _stm32_spi_flush_rxfifo(spi_instance);
    
    return EMC_STATUS_OK;
}

emc_result_t stm32_spi_transmit(emc_spi_t *spi, const uint8_t *tx, uint32_t length)
{
    return stm32_spi_transfer(spi, tx, NULL, length);
}

emc_result_t stm32_spi_receive(emc_spi_t *spi, uint8_t *rx, uint32_t length)
{
    return stm32_spi_transfer(spi, NULL, rx, length);
}