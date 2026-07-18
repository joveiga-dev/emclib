#ifndef EMC_RGB_LED_H
#define EMC_RGB_LED_H

#include "emc_common.h"
#include "emc_led.h"

typedef enum {
    EMC_RGB_LED_COLOR_OFF = 0,  // 0, 0, 0
    EMC_RGB_LED_COLOR_RED,      // 255, 0, 0
    EMC_RGB_LED_COLOR_GREEN,    // 0, 255, 0
    EMC_RGB_LED_COLOR_BLUE,     // 0, 0, 255
    EMC_RGB_LED_COLOR_YELLOW,   // 255, 255, 0
    EMC_RGB_LED_COLOR_CYAN,     // 0, 255, 255
    EMC_RGB_LED_COLOR_MAGENTA,  // 255, 0, 255
    EMC_RGB_LED_COLOR_WHITE,    // 255, 255, 255
} emc_rgb_led_color_t;

typedef struct {
    uint32_t last_time;
    emc_led_t red;
    emc_led_t green;
    emc_led_t blue;
} emc_rgb_led_t;

// API
emc_result_t emc_rgb_led_init(const emc_rgb_led_t *rgb_instance);
emc_result_t emc_rgb_led_deinit(const emc_rgb_led_t *rgb_instance);
emc_result_t emc_rgb_led_set_color(const emc_rgb_led_t *rgb_instance, emc_rgb_led_color_t color);

emc_result_t emc_rgb_led_on(const emc_rgb_led_t *rgb_instance);
emc_result_t emc_rgb_led_off(const emc_rgb_led_t *rgb_instance);




#endif // EMC_RGB_LED_H