#include "emc_gpio.h"
//#include "gpio_ops.h"
#include "stm32_gpio.h"

emc_result_t emc_gpio_init(const emc_gpio_t *gpio, const emc_gpio_config_t *cfg)
{
    return stm32_gpio_init(gpio, cfg);
}

emc_result_t emc_gpio_deinit(const emc_gpio_t *gpio)
{
    return stm32_gpio_deinit(gpio);
}

emc_result_t emc_gpio_write(const emc_gpio_t *gpio, emc_gpio_pin_state_t state)
{
    return stm32_gpio_write(gpio, state);
}

emc_result_t emc_gpio_read(const emc_gpio_t *gpio, emc_gpio_pin_state_t *state)
{
    return stm32_gpio_read(gpio, state);
}

emc_result_t emc_gpio_toggle(const emc_gpio_t *gpio)
{
    return stm32_gpio_toggle(gpio);
}















































/*
static const gpio_ops_t *gpio_backend = 0;

void emc_gpio_bind_backend(const gpio_ops_t *backend) 
{
    gpio_backend = backend;
}

int emc_gpio_init(emc_gpio_t *gpio, const emc_gpio_config_t *cfg) 
{
    return gpio_backend->init(gpio, cfg);
}

void emc_gpio_deinit(emc_gpio_t *gpio) 
{
    gpio_backend->deinit(gpio);
}

void emc_gpio_write(const emc_gpio_t *gpio, bool state) 
{
    gpio_backend->write(gpio, state);
}

bool emc_gpio_read(const emc_gpio_t *gpio) 
{
    return gpio_backend->read(gpio);
}

void emc_gpio_toggle(const emc_gpio_t *gpio) 
{
    gpio_backend->toggle(gpio);
}

void emc_gpio_set(const emc_gpio_t *gpio)
{
    emc_gpio_write(gpio, true);
}

void emc_gpio_reset(const emc_gpio_t *gpio)
{
    emc_gpio_write(gpio, false);
}
*/