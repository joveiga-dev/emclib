#include "emc_button.h"
#include "emc_time.h"
#include "emc_log.h"

emc_result_t emc_button_init(const emc_button_t *pbtn)
{
    if(pbtn == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_gpio_config_t cfg;

    cfg.mode = EMC_GPIO_MODE_IN;
    cfg.otype = EMC_GPIO_OTYPE_PP;
    cfg.ospeed = EMC_GPIO_OSPEED_LOW;
    cfg.pupd = pbtn->active_low ? EMC_GPIO_PUPD_UP : EMC_GPIO_PUPD_DOWN;
    cfg.alternate_function = 0;

    return emc_gpio_init(&pbtn->gpiox, &cfg);
}

emc_result_t emc_button_deinit(const emc_button_t *pbtn)
{
    if(pbtn == NULL) {
        return EMC_STATUS_NOT_INITIALIZED;
    }

    return emc_gpio_deinit(&pbtn->gpiox);
}

emc_result_t emc_button_read(const emc_button_t *pbtn, bool *pressed)
{
    if(pbtn == NULL || pressed == NULL) {
        return EMC_STATUS_ERR;
    }
    emc_gpio_pin_state_t state;
    emc_result_t res = emc_gpio_read(&pbtn->gpiox, &state);
    if(res != EMC_STATUS_OK) {
        return res;
    }

    if(pbtn->active_low) {
        *pressed = (state == EMC_GPIO_PIN_STATE_LOW);
    } else {
        *pressed = (state == EMC_GPIO_PIN_STATE_HIGH);
    }

    return EMC_STATUS_OK;
}

emc_result_t emc_button_handle_init(emc_button_handle_t *handle, const emc_button_t *button)
{
    if(handle == NULL || button == NULL) {
        return EMC_STATUS_ERR;
    }

    bool pressed;
    emc_result_t res = emc_button_read(button, &pressed);
    if(res != EMC_STATUS_OK) {
        EMC_LOGE("BUTTON", "Failed to read button state during handle initialization");
        return res;
    }

    handle->button = button;
    handle->last_sample = pressed;
    handle->stable_state = pressed;
    handle->long_press_sent = false;
    handle->time_last_change = emc_time_get();
    handle->press_time = 0;

    return EMC_STATUS_OK;
}

emc_result_t emc_button_poll(emc_button_handle_t *handle, emc_button_event_t *event)
{
    if ((handle == NULL) || (event == NULL)) {
        return EMC_STATUS_ERR;
    }

    *event = EMC_BTN_EVENT_NONE;
    bool sample;

    emc_result_t res = emc_button_read(handle->button, &sample);
    if (res != EMC_STATUS_OK) {
        EMC_LOGE("BUTTON", "Failed to read button state during polling");
        return res;
    }

    uint32_t current_time_ms = emc_time_get();

    if (sample != handle->last_sample) {
        handle->last_sample = sample;
        handle->time_last_change = current_time_ms;
        return EMC_STATUS_OK;
    }

    if ((current_time_ms - handle->time_last_change) < handle->button->debounce_ms) {
        return EMC_STATUS_OK;
    }

    if (sample != handle->stable_state) {
        handle->stable_state = sample;

        if (sample) {
            /* Button pressed */
            handle->press_time = current_time_ms;
            handle->long_press_sent = false;

            *event = EMC_BTN_EVENT_PRESS;
        }
        else {
            /* Button released */
            if (!handle->long_press_sent){
                *event = EMC_BTN_EVENT_SHORT_PRESS;
            }
            else{
                *event = EMC_BTN_EVENT_RELEASE;
            }
        }

        return EMC_STATUS_OK;
    }

    /* Detect long press while button is held */
    if (sample && !handle->long_press_sent && ((current_time_ms - handle->press_time) >=handle->button->long_press_ms)){
        handle->long_press_sent = true;
        *event = EMC_BTN_EVENT_LONG_PRESS;
    }

    return EMC_STATUS_OK;
}
