/**
 * @file examples/button/button_polling/main.c
 * @brief Button polling example
 * @author JC
 */

#include "emc_button.h"
#include "emc_log.h"
#include "emc_time.h"

static emc_uart_t uart = {0};

static void uart_init(void)
{
    emc_uart_config_t cfg;
    emc_uart_dft_config(&cfg);

    uart.uart_id = EMC_USART2;
    uart.config = cfg;

    emc_uart_init(&uart);
}

static const emc_button_t user_button = {
    .gpiox.port = BTN_USER_GPIO_PORT,
    .gpiox.pin = BTN_USER_PIN,
    .active_low = true,
    .debounce_ms = 20,
    .long_press_ms = 3000
};

static emc_button_handle_t user_button_handle;

static void system_init(void)
{
    /* Initialize 1ms system tick */
    emc_time_init(1000U);

    uart_init();

    emc_log_init(&uart);

    /* Initialize Button */
    emc_button_init(&user_button);
    emc_button_handle_init(&user_button_handle, &user_button);

}

int main(void)
{
    system_init();

    EMC_LOGI("MAIN", "emclib Button polling example started");
    EMC_LOGI("MAIN", "Press the USER button.");

    //bool last_state = false;

    while(1) {
        emc_button_event_t event;
        uint32_t now_ms = emc_time_get();
        emc_button_poll(&user_button_handle, &event);

        if(event != EMC_BTN_EVENT_NONE) {
            switch(event) {
                case EMC_BTN_EVENT_PRESS:
                    EMC_LOGI("BUTTON", "[%lu] PRESS", emc_time_get() - now_ms);
                    break;
                case EMC_BTN_EVENT_RELEASE:
                    EMC_LOGI("BUTTON", "[%lu] RELEASE", emc_time_get() - now_ms);
                    break;
                case EMC_BTN_EVENT_SHORT_PRESS:
                    EMC_LOGI("BUTTON", "[%lu] SHORT PRESS", emc_time_get() - now_ms);
                    break;
                case EMC_BTN_EVENT_LONG_PRESS:
                    EMC_LOGI("BUTTON", "[%lu] LONG PRESS", emc_time_get() - now_ms);
                    break;
                default:
                    break;
            }
        }
        
        emc_time_delay_ms(1);
    }

    return 0;
}