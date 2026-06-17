#include "emc_gpio.h"
#include "emc_time.h"


int main(void)
{
    emc_time_init(1000U);    /* 1ms tick */ 
    
    emc_gpio_t led = { 
        .port = EMC_GPIO_PORTA, 
        .pin = 5
    };

    emc_gpio_config_t led_cfg = {
        .mode = EMC_GPIO_MODE_OUT,
        .otype = EMC_GPIO_OTYPE_PP,
        .ospeed = EMC_GPIO_OSPEED_LOW,
        .pupd = EMC_GPIO_PUPD_NONE
    };

    emc_gpio_init(&led, &led_cfg);

    while (1)
    {
        emc_gpio_toggle(&led);
        emc_time_delay_ms(100);
    }

    return 0;
}