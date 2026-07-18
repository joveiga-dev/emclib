#include "emc_rgb_led.h"

emc_result_t emc_rgb_led_init(const emc_rgb_led_t *rgb_instance)
{
    emc_led_t *leds[3] = {
        &rgb_instance->red, 
        &rgb_instance->green, 
        &rgb_instance->blue
    };

    for (uint8_t i = 0; i < 3; i++) {
        emc_result_t res = emc_led_init(leds[i]);
        if (res != EMC_STATUS_OK) {
            return res;
        }
    }
    return EMC_STATUS_OK;
}


emc_result_t emc_rgb_led_deinit(const emc_rgb_led_t *rgb_instance)
{
    if (rgb_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_led_t *leds[3] = {
        &rgb_instance->red, 
        &rgb_instance->green, 
        &rgb_instance->blue
    };

    for (uint8_t i = 0; i < 3; i++) {
        emc_result_t res = emc_led_deinit(leds[i]);
        if (res != EMC_STATUS_OK) {
            return res;
        }
    }
    return EMC_STATUS_OK;
}

emc_result_t emc_rgb_led_set_color(const emc_rgb_led_t *rgb_instance, emc_rgb_led_color_t color)
{
    if (rgb_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    switch (color) {
        case EMC_RGB_LED_COLOR_OFF:
            return emc_rgb_led_off(rgb_instance);
            break;
        case EMC_RGB_LED_COLOR_RED:
            return emc_led_on(&rgb_instance->red);
        case EMC_RGB_LED_COLOR_GREEN:
            return emc_led_on(&rgb_instance->green);
        case EMC_RGB_LED_COLOR_BLUE:
            return emc_led_on(&rgb_instance->blue);
        case EMC_RGB_LED_COLOR_YELLOW:
            emc_led_on(&rgb_instance->red);
            return emc_led_on(&rgb_instance->green);
        case EMC_RGB_LED_COLOR_CYAN:
            emc_led_on(&rgb_instance->green);
            return emc_led_on(&rgb_instance->blue);
        case EMC_RGB_LED_COLOR_MAGENTA:
            emc_led_on(&rgb_instance->red);
            return emc_led_on(&rgb_instance->blue);
        case EMC_RGB_LED_COLOR_WHITE:
            return emc_rgb_led_on(rgb_instance);
        default:
            return EMC_STATUS_NOT_SUPPORTED;
    }
}

emc_result_t emc_rgb_led_on(const emc_rgb_led_t *rgb_instance)
{
    if (rgb_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_led_t *leds[3] = {
        &rgb_instance->red, 
        &rgb_instance->green, 
        &rgb_instance->blue
    };

    for (uint8_t i = 0; i < 3; i++) {
        emc_result_t res = emc_led_on(leds[i]);
        if (res != EMC_STATUS_OK) {
            return res;
        }
    }
    return EMC_STATUS_OK;
}

emc_result_t emc_rgb_led_off(const emc_rgb_led_t *rgb_instance)
{
    if (rgb_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_led_t *leds[3] = {
        &rgb_instance->red, 
        &rgb_instance->green, 
        &rgb_instance->blue
    };

    for (uint8_t i = 0; i < 3; i++) {
        emc_result_t res = emc_led_off(leds[i]);
        if (res != EMC_STATUS_OK) {
            return res;
        }
    }
    return EMC_STATUS_OK;
}


