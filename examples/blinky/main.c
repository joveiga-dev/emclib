#include "emc_gpio.h"
#include "emc_time.h"
#include "emc_timer.h"


int main(void)
{
    emc_time_init(1000U);    /* 1ms tick */
    emc_gpio_config_t io_conf = {};

    emc_timer_t led_timer;
    emc_timer_setup(&led_timer, 500, 1);
    
    emc_gpio_t led = { 
        .port = EMC_GPIO_PORTA, 
        .pin = 5
    };


    io_conf.mode = EMC_GPIO_MODE_OUT;
    io_conf.otype = EMC_GPIO_OTYPE_PP;
    io_conf.pupd = EMC_GPIO_PUPD_NONE;
    io_conf.ospeed = EMC_GPIO_OSPEED_LOW;
    emc_gpio_init(&led, &io_conf);

    while (1)
    {
        if (emc_timer_has_elapsed(&led_timer)) {
            emc_gpio_toggle(&led);
        }
    }

    return 0;
}