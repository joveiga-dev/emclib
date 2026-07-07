/**
 * @file examples/comms/spi/spi_loopback.c
 * @brief SPI loopback example
 * 
 * Connections:
 * - Connect SPI1_MOSI (PA7) to SPI1_MISO (PA6) or D13/D12 on Nucleo boards
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

static void uart_init(void)
{
    emc_uart_config_t cfg;
    emc_uart_dft_config(&cfg);

    uart.uart_id = EMC_USART2;
    uart.config = cfg;

    emc_uart_init(&uart);
}

static void spi_init(void)
{
    emc_spi_config_t cfg;
    
    emc_spi_dft_config(&cfg);

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

    /* Initialize SPI */
    spi_init();


}

int main(void)
{
    system_init();

    EMC_LOGI("MAIN", "emclib SPI loopback example started");


    uint8_t tx_data[] = {0x55, 0xAA, 0xFF, 0x00};
    uint8_t rx_data[sizeof(tx_data)] = {0};

    while(1) {
        emc_spi_transfer(&spix, tx_data, rx_data, sizeof(tx_data));

        for(uint32_t i = 0; i < sizeof(tx_data); i++) {
            if(tx_data[i] != rx_data[i]) {
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

        emc_time_delay_ms(1000);
    }

    


    return 0;
}