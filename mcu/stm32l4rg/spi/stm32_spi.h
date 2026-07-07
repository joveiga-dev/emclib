#ifndef STM32_SPI_H
#define STM32_SPI_H

#include "emc_spi.h"
#include "stm32l4xx.h"

#define SPI_USE_DMA        0

#if (SPI_USE_DMA)
#include "emc_dma.h"
#endif

typedef struct {
    volatile uint32_t SPI_CR1;
    volatile uint32_t SPI_CR2;
    volatile uint32_t SPI_SR;
    volatile uint32_t SPI_DR;
    volatile uint32_t SPI_CRCPR;
    volatile uint32_t SPI_RXCRCR;
    volatile uint32_t SPI_TXCRCR;
} SPI_RegDef_t;


#define SPI1 ((SPI_RegDef_t *) SPI1_BASE)
#define SPI2 ((SPI_RegDef_t *) SPI2_BASE)
#define SPI3 ((SPI_RegDef_t *) SPI3_BASE)

emc_result_t stm32_spi_init(emc_spi_t *spi);
emc_result_t stm32_spi_transmit(emc_spi_t *spi, const uint8_t *tx, uint32_t length);
emc_result_t stm32_spi_receive(emc_spi_t *spi, uint8_t *rx, uint32_t length);
emc_result_t stm32_spi_transfer(emc_spi_t *spi, const uint8_t *tx, uint8_t *rx, uint32_t length);




#endif // STM32_SPI_H