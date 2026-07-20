#include "emc_rgb_led.h"

typedef emc_result_t (*emc_rgb_led_operation_t)(const emc_led_t *);

static emc_result_t emc_rgb_led_apply(const emc_rgb_led_t *rgb, emc_rgb_led_operation_t op)
{
    if ((rgb == NULL) || (op == NULL)) {
        return EMC_STATUS_ERR;
    }

    const emc_led_t *leds[EMC_RGB_CHANNEL_COUNT] = {
        &rgb->red, 
        &rgb->green, 
        &rgb->blue
    };

    for (uint8_t i = 0; i < EMC_RGB_CHANNEL_COUNT; i++) {
        emc_result_t res = op(leds[i]);
        if (res != EMC_STATUS_OK) {
            return res;
        }
    }
    return EMC_STATUS_OK;
}

emc_result_t emc_rgb_led_init(const emc_rgb_led_t *rgb)
{
    return emc_rgb_led_apply(rgb, emc_led_init);
}

emc_result_t emc_rgb_led_deinit(const emc_rgb_led_t *rgb)
{
    return emc_rgb_led_apply(rgb, emc_led_deinit);
}

emc_result_t emc_rgb_led_on(const emc_rgb_led_t *rgb)
{
    return emc_rgb_led_apply(rgb, emc_led_on);
}

emc_result_t emc_rgb_led_off(const emc_rgb_led_t *rgb)
{
    return emc_rgb_led_apply(rgb, emc_led_off);
}

emc_result_t emc_rgb_led_set_color(const emc_rgb_led_t *rgb, const emc_rgb_led_color_code_t *color)
{
    if ((rgb == NULL) || (color == NULL)) {
        return EMC_STATUS_ERR;
    }

    emc_result_t res = emc_rgb_led_off(rgb);
    if (res != EMC_STATUS_OK) {
        return res;
    }

    if (color->red_val) {
        emc_led_on(&rgb->red);
    }
    if (color->green_val) {
        emc_led_on(&rgb->green);
    }
    if (color->blue_val) {
        emc_led_on(&rgb->blue);
    }

    return EMC_STATUS_OK;
}


