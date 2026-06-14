#ifndef EMC_GPIO_H
#define EMC_GPIO_H

/*
 * @file emc_gpio.h
 * @brief GPIO library
 */

#include <stdint.h>
#include <stdbool.h>

typedef enum {
    EMC_GPIO_PORTA = 0,
    EMC_GPIO_PORTB,
    EMC_GPIO_PORTC,
    EMC_GPIO_PORTD,
    EMC_GPIO_PORTE,
    EMC_GPIO_PORTF,
    EMC_GPIO_PORTG,
    EMC_GPIO_PORTH,
} emc_gpio_port_t;

typedef enum {
    EMC_GPIO_MODE_IN = 0X00,   /*!< Input mode */
    EMC_GPIO_MODE_OUT = 0X01,  /*!< Output mode */
    EMC_GPIO_MODE_AF = 0X02,   /*!< Alternate function mode */
    EMC_GPIO_MODE_AN = 0X03,   /*!< Analog mode */
} emc_gpio_mode_t;

typedef enum {
    EMC_GPIO_OTYPE_PP = 0X00,   /*!< Push-pull output */
    EMC_GPIO_OTYPE_OD = 0X01,   /*!< Open-drain output */
} emc_gpio_otype_t;

typedef enum {
    EMC_GPIO_OSPEED_LOW = 0X00,       /*!< Low speed */
    EMC_GPIO_OSPEED_MEDIUM = 0X01,    /*!< Medium speed */
    EMC_GPIO_OSPEED_HIGH = 0X02,      /*!< High speed */
    EMC_GPIO_OSPEED_VERY_HIGH = 0X03, /*!< Very high speed */
} emc_gpio_ospeed_t;

typedef enum {
    EMC_GPIO_PUPD_NONE = 0X00,        /*!< No pull-up or pull-down */
    EMC_GPIO_PUPD_UP = 0X01,          /*!< Pull-up enabled */
    EMC_GPIO_PUPD_DOWN = 0X02,        /*!< Pull-down enabled */
} emc_gpio_pupd_t;

typedef struct {
    emc_gpio_port_t port;             /*!< GPIO port */
    uint16_t pin;                    /*!< GPIO pin number (0-15) */
} emc_gpio_t;

typedef struct {
    emc_gpio_mode_t mode;             /*!< GPIO mode */
    emc_gpio_otype_t otype;           /*!< GPIO output type */
    emc_gpio_ospeed_t ospeed;         /*!< GPIO output speed */
    emc_gpio_pupd_t pupd;             /*!< GPIO pull-up/pull-down configuration */
    uint8_t alternate_function;       /*!< GPIO alternate function (0-15), valid only if mode is EMC_GPIO_MODE_AF */
} emc_gpio_config_t;


int emc_gpio_init(emc_gpio_t *gpio, const emc_gpio_config_t *cfg);
void emc_gpio_deinit(emc_gpio_t *gpio);
void emc_gpio_write(const emc_gpio_t *gpio, bool state);
bool emc_gpio_read(const emc_gpio_t *gpio);
void emc_gpio_toggle(const emc_gpio_t *gpio);
void emc_gpio_set(const emc_gpio_t *gpio);
void emc_gpio_reset(const emc_gpio_t *gpio);
#endif // EMC_GPIO_H