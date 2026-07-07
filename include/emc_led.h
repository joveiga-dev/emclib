#ifndef EMC_LED_H
#define EMC_LED_H

#include "emc_common.h"
#include "emc_gpio.h"

typedef enum {
    EMC_LED_OFF = 0,
    EMC_LED_ON = 1
} emc_led_state_t;

typedef struct {
    const emc_gpio_t gpio;         /*!< GPIO configuration for the LED */
    bool active_high;               /*!< true if LED is active high, false if active low */
} emc_led_t;

/**
 * @brief Initialize the LED
 * @param self Pointer to the LED configuration structure
 */
emc_result_t emc_led_init(const emc_led_t *self);

/**
 * @brief Deinitialize the LED
 * @param self Pointer to the LED configuration structure
 */
emc_result_t emc_led_deinit(const emc_led_t *self);

/**
 * @brief Toggle the LED state
 * @param self Pointer to the LED configuration structure
 */
emc_result_t emc_led_toggle(const emc_led_t *self);

/**
 * @brief Turn the LED on
 * @param self Pointer to the LED configuration structure
 */
emc_result_t emc_led_on(const emc_led_t *self);

/**
 * @brief Turn the LED off
 * @param self Pointer to the LED configuration structure
 */
emc_result_t emc_led_off(const emc_led_t *self);

/**
 * @brief Write a state to the LED
 * @param self Pointer to the LED configuration structure
 * @param state Desired state of the LED
 */
emc_result_t emc_led_write(const emc_led_t *self, bool state);


#endif // EMC_LED_H