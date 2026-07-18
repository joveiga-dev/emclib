#include "board_button.h"
#include "emc_button.h"

static emc_button_handle_t board_button_handles[BOARD_BUTTON_MAX] = {0};

// Hardware mapping table for button
static const emc_button_t board_buttons[BOARD_BUTTON_MAX] = {
    [BOARD_BUTTON_USER] = { // User button -> PC13
        .gpiox.port = EMC_GPIO_PORTC,
        .gpiox.pin = 13,
        .active_low = true,
        .debounce_ms = 20,
        .long_press_ms = 3000
    }
    // Add more buttons

};

/**
 * @brief Helper to get the button instance by ID
 * @param id Button ID
 * @return Pointer to button instance, or NULL if ID is invalid
 */
static const emc_button_t *_board_button_get(board_button_id_t id) 
{
    if(id >= BOARD_BUTTON_MAX) {
        return NULL;
    }
    return &board_buttons[id];
}

emc_result_t board_button_get(board_button_id_t button_id, const emc_button_t **button)
{
    const emc_button_t *btn = _board_button_get(button_id);
    if (btn == NULL) {
        return EMC_STATUS_ERR;
    }
    *button = btn;
    return EMC_STATUS_OK;
}

emc_result_t board_button_init(board_button_id_t button_id)
{
    const emc_button_t *btn = _board_button_get(button_id);
    if (btn == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_result_t res =  emc_button_init(btn);
    if (res != EMC_STATUS_OK) {
        return res;
    }
    return emc_button_handle_init(&board_button_handles[button_id], btn);
}

emc_result_t board_button_deinit(board_button_id_t button_id)
{
    const emc_button_t *btn = _board_button_get(button_id);
    if (btn == NULL) {
        return EMC_STATUS_ERR;
    }

    return emc_button_deinit(btn);
}

emc_result_t board_button_read(board_button_id_t button_id, bool *pressed)
{
    const emc_button_t *btn = _board_button_get(button_id);
    if ((btn == NULL) || (pressed == NULL)) {
        return EMC_STATUS_ERR;
    }
    return emc_button_read(btn, pressed);
}

emc_result_t board_button_poll(board_button_id_t button_id, emc_button_event_t *event)
{
    if (event == NULL) {
        return EMC_STATUS_ERR;
    }

    if (button_id >= BOARD_BUTTON_MAX) {
        return EMC_STATUS_ERR;
    }

    return emc_button_poll(&board_button_handles[button_id], event);
}