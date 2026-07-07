/**
 * @file emc_spi.h´
 * SPI library
 * @author JC
 * @date 2024-06-25
 */

#ifndef EMC_SPI_H
#define EMC_SPI_H

#include "emc_gpio.h"
#include "emc_common.h"

typedef enum {
    EMC_SPI_OK = 0,
    EMC_SPI_ERROR,
    EMC_SPI_BUSY,
    EMC_SPI_TIMEOUT

} emc_spi_status_t;

typedef enum {
    EMC_SPI1 = 0,
    EMC_SPI2,
    EMC_SPI3,

    EMC_SPI_ALL
} emc_spi_id_t;

typedef enum {
    EMC_SPI_SPEED_LOW = 0,     /* Low speed */
    EMC_SPI_SPEED_MEDIUM,      /* Medium speed */
    EMC_SPI_SPEED_HIGH,        /* High speed */
} emc_spi_speed_t;

typedef enum {
    EMC_SPI_MODE0 = 0,  /* CPOL = 0, CPHA = 0 */
    EMC_SPI_MODE1,      /* CPOL = 0, CPHA = 1 */
    EMC_SPI_MODE2,     /* CPOL = 1, CPHA = 0 */
    EMC_SPI_MODE3,      /* CPOL = 1, CPHA = 1 */
    EMC_SPI_MODE_MAX
} emc_spi_clock_mode_t;

typedef enum {
    EMC_SPI_FULL_DUPLEX = 0,  /* Full-duplex transfer */
    EMC_SPI_HALF_DUPLEX,      /* Half-duplex transfer */
    EMC_SPI_SIMPLEX_RX,       /* Simplex receive-only transfer */
    EMC_SPI_SIMPLEX_TX        /* Simplex transmit-only transfer */
} emc_spi_transfer_mode_t;

typedef enum {
    EMC_SPI_MASTER = 0,  /* Master mode */
    EMC_SPI_SLAVE         /* Slave mode */
} emc_spi_role_t;

typedef struct {
    emc_gpio_t cs_gpio;
    bool initialized;
    bool active_low;
} emc_spi_chip_select_t;

typedef enum {
    EMC_SPI_PRESCALER_2 = 0,   /* fPCLK / 2 */
    EMC_SPI_PRESCALER_4,       /* fPCLK / 4 */
    EMC_SPI_PRESCALER_8,       /* fPCLK / 8 */
    EMC_SPI_PRESCALER_16,      /* fPCLK / 16 */
    EMC_SPI_PRESCALER_32,      /* fPCLK / 32 */
    EMC_SPI_PRESCALER_64,      /* fPCLK / 64 */
    EMC_SPI_PRESCALER_128,     /* fPCLK / 128 */
    EMC_SPI_PRESCALER_256      /* fPCLK / 256 */
} emc_spi_prescaler_t;

typedef struct {
    emc_spi_role_t role;
    emc_spi_transfer_mode_t transfer_mode;
    emc_spi_prescaler_t prescaler;
    emc_spi_clock_mode_t clock;
    uint32_t data_size;
    uint8_t lsb_first;  /* 0: MSB first, 1: LSB first */
} emc_spi_config_t;

/* SPI Handle */
typedef struct {
    emc_spi_id_t id;
    emc_spi_config_t config;
    emc_spi_chip_select_t cs;
} emc_spi_t;

emc_result_t emc_spi_init(emc_spi_t *spi);
void emc_spi_dft_config(emc_spi_config_t *config);
emc_result_t emc_spi_transmit(emc_spi_t *spi, const uint8_t *tx, uint32_t length);
emc_result_t emc_spi_receive(emc_spi_t *spi, uint8_t *rx, uint32_t length);
emc_result_t emc_spi_transfer(emc_spi_t *spi, const uint8_t *tx, uint8_t *rx, uint32_t length);


#endif // EMC_SPI_H