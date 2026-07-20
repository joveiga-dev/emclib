#include "emc_rgb_led.h"
#include "emc_timer.h"
#include "emc_time.h"

static emc_timer_t timer;

static const emc_rgb_led_t rgb_leds = {
    .red = {
        .gpio = {
            .port = EMC_GPIO_PORTB,
            .pin = 5,
        },
        .active_high = true,
    },
    .green = {
        .gpio = {
            .port = EMC_GPIO_PORTA,
            .pin = 9,
        },
        .active_high = true,
    },
    .blue = {
        .gpio = {
            .port = EMC_GPIO_PORTA,
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
                {
                    emc_rgb_led_color_code_t color = {
                        .red_val = 255,
                        .green_val = 0,
                        .blue_val = 255
                    };
                    emc_rgb_led_set_color(&rgb_leds, &color);
                }
            }
            on = !on;
            emc_timer_reset(&timer);
        }
        
    }

    return 0;
}