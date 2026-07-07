#include "board_led.h"
#include "emc_led.h"

// Hardware mapping table for led in the nucleo-476rg board and other added external leds
static const emc_led_t board_leds[BOARD_LED_MAX] = {
    [BOARD_LED_GREEN] = { // User led -> PA5
        .gpio = {
            .port = EMC_GPIO_PORTA,
            .pin = 5
        },
        .active_high = true
    },
    [BOARD_EXT_LED_RED] = {
        .gpio = {
            .port = EMC_GPIO_PORTB,
            .pin = 14
        },
        .active_high = true
    }
};

static emc_led_t *board_led_get(board_led_id_t id)
{
    if(id >= BOARD_LED_MAX) {
        return NULL;
    }

    return &board_leds[id];
}


emc_result_t board_led_init(board_led_id_t led_id)
{
    emc_led_t *led = board_led_get(led_id);
    if(led == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_init(led);
}

emc_result_t board_led_deinit(board_led_id_t led_id)
{
    emc_led_t *led = board_led_get(led_id);
    if(led == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_deinit(led);
}

emc_result_t board_led_write(board_led_id_t led_id, bool state)
{
    emc_led_t *led = board_led_get(led_id);
    if(led == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_write(led, state);
}

emc_result_t board_led_toggle(board_led_id_t led_id)
{
    emc_led_t *led = board_led_get(led_id);
    if(led == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_toggle(led);
}

emc_result_t board_led_on(board_led_id_t led_id)
{
    emc_led_t *led = board_led_get(led_id);
    if(led == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_on(led);
}

emc_result_t board_led_off(board_led_id_t led_id)
{
    emc_led_t *led = board_led_get(led_id);
    if(led == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_led_off(led);
}