#ifndef EMC_BUTTON_H
#define EMC_BUTTON_H

#include <stdbool.h>

#include "emc_common.h"
#include "emc_gpio.h"

#define BTN_USER_PIN           13
#define BTN_USER_GPIO_PORT     EMC_GPIO_PORTC
#define BBT_LONG_PRESS         600

/**
 * Button event
 */
typedef enum {
    EMC_BTN_EVENT_NONE = 0,
    EMC_BTN_EVENT_PRESS,
    EMC_BTN_EVENT_RELEASE,
    EMC_BTN_EVENT_SHORT_PRESS,
    EMC_BTN_EVENT_LONG_PRESS,   
    EMC_BTN_MAX
} emc_button_event_t;

//typedef void(*emc_button_cb_t)(emc_button_event_t event, void *arg);

// Hardware description of the button
typedef struct {
    const emc_gpio_t gpiox;    // GPIO connected to the button
    bool active_low;  // true = pressed when GPIO is low
    int16_t debounce_ms;
    uint16_t long_press_ms;
} emc_button_t;

// Runtime state of the button
typedef struct {
    const emc_button_t *button;
    uint8_t last_sample;
    bool stable_state;
    bool long_press_sent;
    uint32_t time_change;
    uint32_t time_last_change;
    uint32_t press_time;
} emc_button_handle_t;

/**
 * @brief Initialize button GPIO
 * @param pbtn Pointer to Button instance
 * @return EMC_STATUS_OK on success, error code otherwise
 */
emc_result_t emc_button_init(const emc_button_t *pbtn);
/**
 * @brief Deinitialize button GPIO
 * @param pbtn Pointer to Button instance
 * @return EMC_STATUS_OK on success, error code otherwise
 */
emc_result_t emc_button_deinit(const emc_button_t *pbtn);

/**
 * @brief Read button state
 * @param pbtn Pointer to Button instance
 * @param state Pointer to variable to store button state
 * @return EMC_STATUS_OK on success, error code otherwise
 */
emc_result_t emc_button_read(const emc_button_t *pbtn, bool *pressed);

/**
 * @brief Initialize button handle for polling
 * @param handle Pointer to button handle
 * @param button Pointer to button instance
 * @return EMC_STATUS_OK on success, error code otherwise
 */
emc_result_t emc_button_handle_init(emc_button_handle_t *handle, const emc_button_t *button);

/**
 * @brief Poll button state and detect events
 * @param handle Pointer to button handle
 * @param event Pointer to variable to store detected event
 * @return EMC_STATUS_OK on success, error code otherwise
 */
emc_result_t emc_button_poll(emc_button_handle_t *handle, emc_button_event_t *event);


emc_result_t emc_button_enable_int(const emc_button_t *pbtn);
emc_result_t emc_button_disable_int(const emc_button_t *pbtn);
void emc_button_irq_handler(const emc_button_t *pbtn);
emc_result_t emc_button_get_event(emc_button_handle_t *handle, emc_button_event_t *event);
#endif // EMC_BUTTON_H