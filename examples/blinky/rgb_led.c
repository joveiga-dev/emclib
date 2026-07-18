#include "emc_rgb_led.h"
#include "emc_timer.h"
#include "emc_time.h"

static emc_timer_t timer;

static const emc_rgb_led_t rgb_leds = {
    .red_led = {
        .gpio = {
            .port = EMC_GPIO_PORTB,
            .pin = 5,
        },
        .active_high = true,
    },
    .green_led = {
        .gpio = {
            .port = EMC_GPIO_PORTB,
            .pin = 9,
        },
        .active_high = true,
    },
    .blue_led = {
        .gpio = {
            .port = EMC_GPIO_PORTB,
            .pin = 8,
        },
        .active_high = true,
    },
};

static void system_init(void)
{
    /* Initialize 1ms system tick */
    emc_time_init(1000U);

    emc_timer_setup(&timer, 500U, false);
}

int main(void)
{
    system_init();
    emc_rgb_led_init(&rgb_leds);

    bool on = true;

    while (1) {
        if (emc_timer_has_elapsed(&timer)) {
            if (on) {
                emc_rgb_led_off(&rgb_leds);
            } else {
                emc_rgb_led_set_color(&rgb_leds, EMC_RGB_LED_COLOR_RED);
            }
            on = !on;
            emc_timer_reset(&timer);
        }
        
    }

    return 0;
}