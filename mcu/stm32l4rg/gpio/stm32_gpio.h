#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include "emc_gpio.h"

int stm32_gpio_init(emc_gpio_t *gpio, const emc_gpio_config_t *cfg);
void stm32_gpio_deinit(emc_gpio_t *gpio);
void stm32_gpio_write(const emc_gpio_t *gpio, bool state);
void stm32_gpio_set(const emc_gpio_t *gpio);
void stm32_gpio_clear(const emc_gpio_t *gpio);
bool stm32_gpio_read(const emc_gpio_t *gpio);
void stm32_gpio_toggle(const emc_gpio_t *gpio);
#endif // STM32_GPIO_H