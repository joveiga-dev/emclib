#include "emc_spi.h"
#include "stm32_spi.h"


emc_result_t emc_spi_init(emc_spi_t *spi)
{
    return stm32_spi_init(spi);
}

void emc_spi_dft_config(emc_spi_config_t *config)
{
    config->role = EMC_SPI_MASTER;
    config->transfer_mode = EMC_SPI_FULL_DUPLEX;
    config->prescaler = EMC_SPI_PRESCALER_2;
    config->clock = EMC_SPI_MODE0;
    config->data_size = 8;
    config->lsb_first = 0; 
}

emc_result_t emc_spi_transmit(emc_spi_t *spi, const uint8_t *tx, uint32_t length)
{
    return stm32_spi_transmit(spi, tx, length);
}

emc_result_t emc_spi_receive(emc_spi_t *spi, uint8_t *rx, uint32_t length)
{
    return stm32_spi_receive(spi, rx, length);
}

emc_result_t emc_spi_transfer(emc_spi_t *spi, const uint8_t *tx, uint8_t *rx, uint32_t length)
{
    return stm32_spi_transfer(spi, tx, rx, length);
}