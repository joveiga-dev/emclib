/**
 * @file examples/button/button_polling/main.c
 * @brief Button polling example
 * @author JC
 */

#include "emc_button.h"
#include "emc_time.h"
#include "board_button.h"
#include "board_led.h"


static void system_init(void)
{
    /* Initialize 1ms system tick */
    emc_time_init(1000U);

    /* Initialize LED */
    board_led_init(BOARD_LED_GREEN);

    /* Initialize Button */
    board_button_init(BOARD_BUTTON_USER);

}

int main(void)
{
    system_init();

    while(1) {
        emc_button_event_t event;

        if(board_button_poll(BOARD_BUTTON_USER, &event) != EMC_STATUS_OK) {
            continue;
        }

        switch(event) {
            case EMC_BTN_EVENT_PRESS:
                board_led_toggle(BOARD_LED_GREEN);
                break;
            case EMC_BTN_EVENT_RELEASE:
                break;
            case EMC_BTN_EVENT_CLICK:
                break;
            case EMC_BTN_EVENT_LONG_PRESS:
                board_led_off(BOARD_LED_GREEN);
                break;
            default:
                break;
        }

        emc_time_delay_ms(1);
    }

    return 0;
}