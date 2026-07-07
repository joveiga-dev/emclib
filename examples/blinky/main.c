#include "board_led.h"
#include "emc_time.h"

int main(void)
{
    
    emc_time_init(1000U);
    
    board_led_init(BOARD_LED_GREEN);

    while (1)
    {
        board_led_toggle(BOARD_LED_GREEN);
        emc_time_delay(500);
    }

    return 0;
}