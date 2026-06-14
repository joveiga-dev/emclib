#include "stm32_rcc.h"

void stm32_rcc_enable_gpio_clock(emc_gpio_port_t port)
{
    RCC->RCC_AHB2ENR |= (1U << port);
}

void stm32_rcc_disable_gpio_clock(emc_gpio_port_t port)
{
    RCC->RCC_AHB2ENR &= ~(1U << port);
}