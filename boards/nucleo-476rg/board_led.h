#ifndef BOARD_LED_H
#define BOARD_LED_H

#include "emc_common.h"

typedef enum {
    BOARD_LED_GREEN = 0,
    BOARD_EXT_LED_RED,
    BOARD_LED_MAX   
} board_led_id_t;

emc_result_t board_led_init(board_led_id_t led_id);
emc_result_t board_led_deinit(board_led_id_t led_id);
emc_result_t board_led_write(board_led_id_t led_id, bool state);
emc_result_t board_led_toggle(board_led_id_t led_id);
emc_result_t board_led_on(board_led_id_t led_id);
emc_result_t board_led_off(board_led_id_t led_id);


#endif /* BOARD_LED_H */