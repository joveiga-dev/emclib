#include "emc_gpio.h"

static void delay(volatile uint32_t count)
{
    while (count--)
        ;
}

int main(void)
{
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
        delay(200000);
    }

    return 0;
}