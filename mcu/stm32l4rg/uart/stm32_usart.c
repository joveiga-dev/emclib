#include "stm32_usart.h"
#include "emc_periph.h"
#include "emc_gpio.h"
#include "emc_log.h"
#include "stm32_clock.h"

#include <stddef.h>

#define UART_USE_DMA          0

#if (UART_USE_DMA)
#include "emc_dma.h"
#endif

// UART handle structure
typedef struct {
    USART_RegDef_t *instance;           /**< USART peripheral base address */
    emc_gpio_t tx;                      /**< TX pin */
    emc_gpio_t rx;                      /**< RX pin */
    uint8_t af;                         /**< Alternate function */
    emc_periph_t uart_clk;              /**< UART clock */
#if (UART_USE_DMA)
    
#endif

} stm32_uart_hw_t;


static const stm32_uart_hw_t stm32_uart_desc[] = {
    [EMC_USART2] = {
        .instance = USART2,
        .tx = {
            .port = EMC_GPIO_PORTA,
            .pin = 2
        },
        .rx = {
            .port = EMC_GPIO_PORTA,
            .pin = 3
        },
        .af = 7,
        .uart_clk = EMC_PERIPH_USART2,
        //.gpio_clk = EMC_RCC_PERIPH_PORTA
    }
};

static void stm32_uart_enable(emc_uart_id_t uart_id, bool uart_enable)
{
    if(uart_enable) {
        switch(uart_id) {
            case EMC_UART1:
                emc_periph_enable(EMC_PERIPH_UART1);
                break;
            case EMC_USART2:
                emc_periph_enable(EMC_PERIPH_USART2);
                break;
            default:
                return;
        }
    }
    else {
        switch(uart_id) {
            case EMC_UART1:
                emc_periph_disable(EMC_PERIPH_UART1);
                break;
            case EMC_USART2:
                emc_periph_disable(EMC_PERIPH_USART2);
                break;
            default:
                return;
        }
    }
}


static USART_RegDef_t *stm32_get_uart_instance(emc_uart_id_t uart_id)
{
    switch(uart_id) {
        case EMC_UART1:
            return USART1;
        case EMC_USART2:
            return USART2;
        default:
            return NULL;
    }
}

/* Common Set_ utilities */
static int8_t stm32_set_parity(USART_RegDef_t *uart_instance, emc_uart_parity_t parity)
{
    if (uart_instance == NULL || parity > EMC_UART_PARITY_ODD) {
        return -1;
    }

    uart_instance->USART_CR1 &= ~(USART_CR1_PCE | USART_CR1_PS);
    switch (parity) {
        case EMC_UART_PARITY_NONE:
            break;
        case EMC_UART_PARITY_EVEN:
            uart_instance->USART_CR1 |= USART_CR1_PCE;
            break;
        case EMC_UART_PARITY_ODD:
            uart_instance->USART_CR1 |= (USART_CR1_PCE | USART_CR1_PS);
            break;
    }
    return 0;
}

static int8_t stm32_set_wordlen(USART_RegDef_t *uart_instance, emc_uart_wordlen_t word_length)
{
    if (uart_instance == NULL || word_length > EMC_UART_WORD_LENGTH_7B) {
        return -1;
    }

    uart_instance->USART_CR1 &= ~(USART_CR1_M0 | USART_CR1_M1);
    switch (word_length) {
        case EMC_UART_WORD_LENGTH_8B:
            break;
        case EMC_UART_WORD_LENGTH_9B:
            uart_instance->USART_CR1 |= USART_CR1_M0;
            break;
        case EMC_UART_WORD_LENGTH_7B:
            uart_instance->USART_CR1 |= USART_CR1_M1;
            break;
    }
    return 0;
}

static int8_t stm32_set_stopbits(USART_RegDef_t *uart_instance, emc_uart_stopbits_t stop_bits)
{
    if (uart_instance == NULL || stop_bits > EMC_UART_STOPBITS_1_5) {
        return -1;
    }

    uart_instance->USART_CR2 &= ~(USART_CR2_STOP);

    switch (stop_bits) {
        case EMC_UART_STOPBITS_1:
            break;
        case EMC_UART_STOPBITS_0_5:
            uart_instance->USART_CR2 |= USART_CR2_STOP_0;
            break;
        case EMC_UART_STOPBITS_2:
            uart_instance->USART_CR2 |= USART_CR2_STOP_1;
            break;
        case EMC_UART_STOPBITS_1_5:
            uart_instance->USART_CR2 |= USART_CR2_STOP;
            break;
    }
    return 0;
}

static int8_t stm32_set_mode(USART_RegDef_t *uart_instance, emc_uart_mode_t mode)
{
    if (uart_instance == NULL || mode > EMC_UART_MODE_TX_RX) {
        return -1;
    }

    uart_instance->USART_CR1 &= ~(USART_CR1_TE | USART_CR1_RE);
    switch (mode) {
        case EMC_UART_MODE_TX:
            uart_instance->USART_CR1 |= USART_CR1_TE;
            break;
        case EMC_UART_MODE_RX:
            uart_instance->USART_CR1 |= USART_CR1_RE;
            break;
        case EMC_UART_MODE_TX_RX:
            uart_instance->USART_CR1 |= (USART_CR1_TE | USART_CR1_RE);
            break;
        default:
            break;
    }
    return 0;
}

static int8_t stm32_set_hwflowctrl(USART_RegDef_t *uart_instance, emc_uart_hwflowctrl_t hw_flow_control)
{
    if (uart_instance == NULL) {
        return -1;
    }

    uart_instance->USART_CR3 &= ~(USART_CR3_CTSE | USART_CR3_RTSE);
    switch (hw_flow_control) {
        case EMC_UART_HW_FLOW_CTRL_NONE:
            break;
        case EMC_UART_HW_FLOW_CTRL_RTS:
            uart_instance->USART_CR3 |= USART_CR3_RTSE;
            break;
        case EMC_UART_HW_FLOW_CTRL_CTS:
            uart_instance->USART_CR3 |= USART_CR3_CTSE;
            break;
        case EMC_UART_HW_FLOW_CTRL_RTS_CTS:
            uart_instance->USART_CR3 |= (USART_CR3_CTSE | USART_CR3_RTSE);
            break;
        default:
            break;
    }
    return 0;
}

static int8_t stm32_set_oversampling(USART_RegDef_t *uart_instance, emc_uart_oversampling_t oversampling)
{
    if (uart_instance == NULL) {
        return -1;
    }

    if (oversampling == EMC_UART_OVERSAMPLING_8) {
        uart_instance->USART_CR1 |= USART_CR1_OVER8;
    } else {
        uart_instance->USART_CR1 &= ~USART_CR1_OVER8;
    }
    return 0;
}


emc_result_t stm32_uart_set_baudrate(emc_uart_t *uart, uint32_t baudrate)
{
    uint32_t usart_div;
    uint32_t brr_value;

    if (baudrate == 0) {
        return EMC_STATUS_ERR;
    }
    
    if(uart == NULL || uart->uart_id >= EMC_UART_ALL) {
        return EMC_STATUS_ERR;
    }
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    if(uart->config.oversampling == EMC_UART_OVERSAMPLING_8) {
        // oversampling by 8 (OVER8 = 1)
        usart_div = (2 * stm32_rcc_get_sysclk_freq()) / baudrate;
        // BRR[15:4] = USARTDIV[15:4]
        // BRR[2:0] = USARTDIV[3:0] >> 1
        brr_value = ((usart_div & 0xFFF0) | (uint16_t)((usart_div & (0x000FU)) >> 1U));
        uart_instance->USART_BRR = brr_value;
    } else {
        // oversampling by 16 (OVER8 = 0)
        uart_instance->USART_BRR = stm32_rcc_get_sysclk_freq() / baudrate;
    }

    return EMC_STATUS_OK;
}



emc_result_t stm32_uart_init(emc_uart_t *uart)
{
    if (uart == NULL || uart->uart_id >= EMC_UART_ALL) {
        EMC_LOGE("UART_MODULE" ,"Invalid UART configuration");
        return EMC_STATUS_ERR;
    }

    // disable uart before configuration
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        EMC_LOGE("UART_MODULE" ,"Invalid UART instance");
        return EMC_STATUS_ERR;
    }

    uart_instance->USART_CR1 &= ~USART_CR1_UE;
    // wait end of ongoing transmissions
    while (uart_instance->USART_ISR & USART_ISR_BUSY);
    // clear flags
    uart_instance->USART_ICR = 0xFFFFFFFF;

    // enable clock
    const stm32_uart_hw_t *desc = &stm32_uart_desc[uart->uart_id];
    emc_periph_enable(desc->uart_clk); // Enable UART clock
    
    emc_gpio_config_t gpio_cfg = {
        
        .mode = EMC_GPIO_MODE_AF,
        .otype = EMC_GPIO_OTYPE_PP,
        .ospeed = EMC_GPIO_OSPEED_HIGH,
        .pupd = EMC_GPIO_PUPD_NONE,
        .alternate_function = desc->af
    };

    emc_gpio_init(&desc->tx, &gpio_cfg);
    emc_gpio_init(&desc->rx, &gpio_cfg);
    
    // configure uart settings
    stm32_set_wordlen(uart_instance, uart->config.word_length);
    stm32_set_stopbits(uart_instance, uart->config.stop_bits);
    stm32_set_parity(uart_instance, uart->config.parity);
    stm32_set_mode(uart_instance, uart->config.mode);
    stm32_set_hwflowctrl(uart_instance, uart->config.hw_flow_control);
    stm32_set_oversampling(uart_instance, uart->config.oversampling);
    stm32_uart_set_baudrate(uart, uart->config.baudrate);

    uart_instance->USART_CR1 |= USART_CR1_RE | USART_CR1_TE; // Enable both transmitter and receiver
    uart_instance->USART_CR1 |= USART_CR1_UE;

    return EMC_STATUS_OK;
}

emc_result_t stm32_uart_deinit(emc_uart_t *uart)
{
    if(uart == NULL || uart->uart_id >= EMC_UART_ALL) {
        EMC_LOGE("UART_MODULE" ,"UART deinit failed: UART not initialized");
        return EMC_STATUS_ERR;
    }
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART deinit failed: Invalid UART instance");
        return EMC_STATUS_ERR;
    }
    // disable uart
    uart_instance->USART_CR1 &= ~USART_CR1_UE;
    // disable clock for the selected uart
    stm32_uart_enable(uart->uart_id, false);
    return EMC_STATUS_OK;
}


emc_result_t stm32_uart_transmit_byte(emc_uart_t *uart, uint8_t byte)
{
    if(uart == NULL || uart->uart_id >= EMC_UART_ALL) {
        EMC_LOGE("UART_MODULE" ,"UART transmit failed: Invalid UART configuration");
        return EMC_STATUS_ERR;
    }
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART transmit failed: Invalid UART instance");
        return EMC_STATUS_ERR;
    }

    // Wait until the transmit data register is empty (TXE flag)
    while(!(uart_instance->USART_ISR & USART_ISR_TXE));
    uart_instance->USART_TDR = byte; // Write the byte to the data register
    return EMC_STATUS_OK;
}

emc_result_t stm32_uart_transmit(emc_uart_t *uart, const uint8_t *data, uint16_t size)
{
    if (uart == NULL || uart->uart_id >= EMC_UART_ALL || data == NULL || size == 0) {
        EMC_LOGE("UART_MODULE" ,"UART transmit failed: Invalid UART configuration");
        return EMC_STATUS_ERR;
    }
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART transmit failed: Invalid UART instance");
        return EMC_STATUS_ERR;
    }

    for (uint16_t i = 0; i < size; i++) {
        // Wait until the transmit data register is empty (TXE flag)
        while(!(uart_instance->USART_ISR & USART_ISR_TXE));
        uart_instance->USART_TDR = data[i]; // Write the byte to the data register
    }
    return EMC_STATUS_OK;
}

emc_result_t stm32_uart_receive_byte(emc_uart_t *uart, uint8_t *byte)
{
    if(uart == NULL || uart->uart_id >= EMC_UART_ALL || byte == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART receive failed: Invalid UART configuration");
        return EMC_STATUS_ERR;
    }
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART receive failed: Invalid UART instance");
        return EMC_STATUS_ERR;
    }

    // Wait until the receive data register is not empty (RXNE flag)
    while(!(uart_instance->USART_ISR & USART_ISR_RXNE));
    *byte = (uint8_t)(uart_instance->USART_RDR & 0xFF); // Read the received byte from the data register
    return EMC_STATUS_OK;
}

emc_result_t stm32_uart_receive(emc_uart_t *uart, uint8_t *data, uint16_t size)
{
    if (uart == NULL || uart->uart_id >= EMC_UART_ALL || data == NULL || size == 0) {
        EMC_LOGE("UART_MODULE" ,"UART receive failed: Invalid UART configuration");
        return EMC_STATUS_ERR;
    }
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART receive failed: Invalid UART instance");
        return EMC_STATUS_ERR;
    }

    for (uint16_t i = 0; i < size; i++) {
        // Wait until the receive data register is not empty (RXNE flag)
        while(!(uart_instance->USART_ISR & USART_ISR_RXNE));
        data[i] = (uint8_t)(uart_instance->USART_RDR & 0xFF); // Read the received byte from the data register
    }
    return EMC_STATUS_OK;
}


emc_result_t emc_uart_transmit_string(emc_uart_t *uart, const char *str)
{
    if (uart == NULL || uart->uart_id >= EMC_UART_ALL || str == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART transmit failed: Invalid UART configuration");
        return EMC_STATUS_ERR;
    }
    USART_RegDef_t *uart_instance = stm32_get_uart_instance(uart->uart_id);
    if (uart_instance == NULL) {
        EMC_LOGE("UART_MODULE" ,"UART transmit failed: Invalid UART instance");
        return EMC_STATUS_ERR;
    }

    while (*str != '\0') {
        stm32_uart_transmit_byte(uart, (uint8_t)(*str & 0xFF));
        str++;
    }
    
    return EMC_STATUS_OK;
}