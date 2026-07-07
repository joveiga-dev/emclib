/**
 * @file examples/comms/spi/spi_modes.c
 * @brief SPI modes example
 * Understand how SPI modes affects data transmission and reception.
 * @author JC
 * @date 2024-06-27
 */

#include "emc_spi.h"
#include "emc_log.h"
#include "emc_time.h"
#include "emc_uart.h"

#include <stdio.h>

static emc_spi_t spix = {0};
static emc_uart_t uart = {0};

static const emc_spi_clock_mode_t spi_modes[] = {
    EMC_SPI_MODE0, // CPOL=0, CPHA=0
    EMC_SPI_MODE1, // CPOL=0, CPHA=1
    EMC_SPI_MODE2, // CPOL=1, CPHA=0
    EMC_SPI_MODE3  // CPOL=1, CPHA=1
};

static void uart_init(void)
{
    emc_uart_config_t cfg;
    emc_uart_dft_config(&cfg);

    uart.uart_id = EMC_USART2;
    uart.config = cfg;

    emc_uart_init(&uart);
}


static void spi_init(emc_spi_clock_mode_t mode)
{
    emc_spi_config_t cfg;

    emc_spi_dft_config(&cfg);
    
    cfg.clock = mode;

    spix.id = EMC_SPI1;
    spix.config = cfg;
    spix.cs.initialized = false;

    emc_spi_init(&spix);

}

static void system_init(void)
{
    /* Initialize 1ms system tick */
    emc_time_init(1000U);

    uart_init();

    emc_log_init(&uart);
}

static void test_spi_mode(emc_spi_clock_mode_t mode)
{
    EMC_LOGI("SPI", "Testing SPI different modes: %d", mode);
    spi_init(mode);

    uint8_t tx_data[] = {0x55, 0xAA, 0xFF, 0x00};
    uint8_t rx_data[sizeof(tx_data)] = {0};
    bool success = true;

    emc_spi_transfer(&spix, tx_data, rx_data, sizeof(tx_data));

        for(uint32_t i = 0; i < sizeof(tx_data); i++) {
            if(tx_data[i] != rx_data[i]) {
                success = false;
                EMC_LOGE(
                    "SPI",
                    "FAIL i=%d: TX=0x%02X, RX=0x%02X",
                    i,
                    tx_data[i],
                    rx_data[i]
                );
            }
            else {
                EMC_LOGI(
                    "SPI",
                    "PASS i=%d: TX=0x%02X, RX=0x%02X",
                    i,
                    tx_data[i],
                    rx_data[i]
                );
            }
        }

        EMC_LOGD(
            "SPI",
            "TX: 0x%02X 0x%02X 0x%02X 0x%02X | RX: 0x%02X 0x%02X 0x%02X 0x%02X",
            tx_data[0], tx_data[1], tx_data[2], tx_data[3],
            rx_data[0], rx_data[1], rx_data[2], rx_data[3]);

        if(success) {
            EMC_LOGI("SPI", "SPI mode %d test PASSED", mode);
        }
        else {
            EMC_LOGE("SPI", "SPI mode %d test FAILED", mode);
        }

        emc_time_delay_ms(2000);
}

int main(void)
{
    system_init();

    EMC_LOGI("MAIN", "========================================");
    EMC_LOGI("MAIN", "emclib SPI Clock Modes Example");
    EMC_LOGI("MAIN", "Connect PA7 (MOSI) to PA6 (MISO)");
    EMC_LOGI("MAIN", "========================================");

    while(1) {
        for(uint32_t i = 0; i< 4; i++) {
            test_spi_mode(spi_modes[i]);
            EMC_LOGI("MAIN", "Starting test for mode %d\n", spi_modes[i + 1]);
            emc_time_delay_ms(1000);
        }
    }

    return 0;
}