/**
 * @file uart_echo.c
 * @brief UART echo example
 * @author JC
 */
#include "emc_uart.h"
#include "emc_log.h"
#include "emc_time.h"

#include <stdio.h>

static void uart_init(emc_uart_t *uartx)
{
    emc_uart_config_t cfg;
    emc_uart_dft_config(&cfg);

    uartx->uart_id = EMC_USART2;
    uartx->config = cfg;

    emc_uart_init(uartx);
}

static void system_init(emc_uart_t *uart)
{
    /* Initialize 1ms system tick */
    emc_time_init(1000U);

    /* Initialize debug UART */
    uart_init(uart);

    /* Initialize logger */
    emc_log_init(uart);
}

int main(void)
{
    emc_uart_t uart;
    system_init(&uart);

    EMC_LOGI("MAIN", "emclib UART echo example started");
    EMC_LOGI("MAIN", "Send a character to the UART and it will be echoed back with +1.");
    
    while (1) {
        uint8_t rx = emc_uart_receive_byte(&uart);
        uint8_t tx = rx + 1;

        emc_uart_transmit_byte(&uart, tx);
        EMC_LOGD(
            "UART",
            "RX='%c' (0x%02X) -> TX='%c' (0x%02X)",
            rx,
            rx, 
            tx, 
            tx); 
    }

    return 0;
}