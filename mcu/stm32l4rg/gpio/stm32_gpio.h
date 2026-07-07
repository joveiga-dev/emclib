#ifndef STM32_GPIO_H
#define STM32_GPIO_H

#include "emc_gpio.h"

emc_result_t stm32_gpio_init(const emc_gpio_t *gpio, const emc_gpio_config_t *cfg);
emc_result_t stm32_gpio_deinit(const emc_gpio_t *gpio);
emc_result_t stm32_gpio_write(const emc_gpio_t *gpio, emc_gpio_pin_state_t state);
emc_result_t stm32_gpio_set(const emc_gpio_t *gpio);
emc_result_t stm32_gpio_clear(const emc_gpio_t *gpio);
emc_result_t stm32_gpio_read(const emc_gpio_t *gpio, emc_gpio_pin_state_t *state);
emc_result_t stm32_gpio_toggle(const emc_gpio_t *gpio);

#endif // STM32_GPIO_H