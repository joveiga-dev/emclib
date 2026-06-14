#ifndef GPIO_OPS_H
#define GPIO_OPS_H

#include "emc_gpio.h"

typedef struct {
    int (*init)(emc_gpio_t *gpio, const emc_gpio_config_t *cfg);
    void (*deinit)(emc_gpio_t *gpio);
    void (*write)(const emc_gpio_t *gpio, bool state);
    bool (*read)(const emc_gpio_t *gpio);
    void (*toggle)(const emc_gpio_t *gpio);
} gpio_ops_t;

extern const gpio_ops_t gpio_ops;

#endif // GPIO_OPS_H