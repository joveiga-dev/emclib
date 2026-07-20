#ifndef EMC_RGB_LED_H
#define EMC_RGB_LED_H

#include "emc_common.h"
#include "emc_led.h"

typedef struct {
    //uint32_t last_time;
    emc_led_t red;
    emc_led_t green;
    emc_led_t blue;
} emc_rgb_led_t;

typedef struct {
    uint8_t red_val;
    uint8_t green_val;
    uint8_t blue_val;
} emc_rgb_led_color_code_t;

typedef enum {
    EMC_RGB_RED = 0,
    EMC_RGB_GREEN,
    EMC_RGB_BLUE,
    EMC_RGB_CHANNEL_COUNT
} emc_rgb_channel_t;

/**
 * @brief Initialize the RGB LED
 * @param rgb_instance Pointer to the RGB LED configuration structure
 * @return EMC_STATUS_OK if successful, error code otherwise
 */
emc_result_t emc_rgb_led_init(const emc_rgb_led_t *rgb);
/**
 * @brief Deinitialize the RGB LED
 * @param rgb_instance Pointer to the RGB LED configuration structure
 * @return EMC_STATUS_OK if successful, error code otherwise
 */
emc_result_t emc_rgb_led_deinit(const emc_rgb_led_t *rgb);

/**
 * @brief Turn on the RGB LED
 * @param rgb Pointer to the RGB LED configuration structure
 * @return EMC_STATUS_OK if successful, error code otherwise
 */
emc_result_t emc_rgb_led_on(const emc_rgb_led_t *rgb);
/**
 * @brief Turn off the RGB LED
 * @param rgb Pointer to the RGB LED configuration structure
 * @return EMC_STATUS_OK if successful, error code otherwise
 */
emc_result_t emc_rgb_led_off(const emc_rgb_led_t *rgb);
/**
 * @brief Set the RGB LED color
 * @param rgb Pointer to the RGB LED configuration structure
 * @param color Pointer to the color code structure
 * @return EMC_STATUS_OK if successful, error code otherwise
 */
emc_result_t emc_rgb_led_set_color(const emc_rgb_led_t *rgb, const emc_rgb_led_color_code_t *color);





#endif // EMC_RGB_LED_H