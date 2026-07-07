#include "emc_led.h"

emc_result_t emc_led_init(const emc_led_t *self)
{
    if(self == NULL) {
        return EMC_STATUS_ERR;
    }

    const emc_gpio_config_t cfg = {
        .mode = EMC_GPIO_MODE_OUT,
        .otype = EMC_GPIO_OTYPE_PP,
        .pupd = EMC_GPIO_PUPD_NONE,
        .ospeed = EMC_GPIO_OSPEED_LOW,
        .alternate_function = 0
    };

    emc_result_t result = emc_gpio_init(&self->gpio, &cfg);
    if(result != EMC_STATUS_OK) {
        return result;
    }

    return emc_led_off(self);
}

emc_result_t emc_led_deinit(const emc_led_t *self)
{
    if(self == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_gpio_deinit(&self->gpio);
}

emc_result_t emc_led_write(const emc_led_t *self, bool state)
{
    if(self == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_gpio_pin_state_t p_state;

    if(self->active_high) {
        p_state = state ? EMC_GPIO_PIN_STATE_HIGH : EMC_GPIO_PIN_STATE_LOW;
    } else {
        p_state = state ? EMC_GPIO_PIN_STATE_LOW : EMC_GPIO_PIN_STATE_HIGH;
    }

    return emc_gpio_write(&self->gpio, p_state);
}

emc_result_t emc_led_toggle(const emc_led_t *self)
{
    if(self == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_gpio_toggle(&self->gpio);
}

emc_result_t emc_led_on(const emc_led_t *self)
{
    if(self == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_write(self, true);
}

emc_result_t emc_led_off(const emc_led_t *self)
{
    if(self == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_write(self, false);
}

