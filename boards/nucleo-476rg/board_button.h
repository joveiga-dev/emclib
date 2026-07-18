#ifndef BOARD_BUTTON_H
#define BOARD_BUTTON_H

#include "emc_common.h"
#include "emc_button.h"
typedef enum {
    BOARD_BUTTON_USER = 0,
    BOARD_BUTTON_MAX
} board_button_id_t;

emc_result_t board_button_init(board_button_id_t button_id);
emc_result_t board_button_deinit(board_button_id_t button_id);
emc_result_t board_button_read(board_button_id_t button_id, bool *pressed);
emc_result_t board_button_poll(board_button_id_t button_id, emc_button_event_t *event);





#endif /* BOARD_BUTTON_H */