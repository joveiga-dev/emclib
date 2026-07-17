#include "board_led.h"
#include "emc_time.h"
#include "emc_log.h"

static emc_uart_t uart = {0};

static void uart_init(void)
{
    emc_uart_config_t cfg;
    emc_uart_dft_config(&cfg);

    uart.uart_id = EMC_USART2;
    uart.config = cfg;

    emc_uart_init(&uart);
}

int main(void)
{
    
    emc_time_init(1000U);
    uart_init();
    emc_log_init(&uart);
    board_led_init(BOARD_LED_GREEN);

    EMC_LOGI("MAIN", "emclib Blinky example started");

    while (1)
    {
        board_led_toggle(BOARD_LED_GREEN);
        emc_time_delay_ms(500);
        EMC_LOGI("MAIN", "LED toggled");
    }

    return 0;
}