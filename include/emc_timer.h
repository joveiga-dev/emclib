#ifndef EMC_TIMER_H
#define EMC_TIMER_H
#include <stdint.h>

typedef struct {
    uint8_t wait_time;
    uint32_t src_time;
    uint8_t auto_reset : 1;
    uint8_t has_elapsed : 1;
} emc_timer_t;

void emc_timer_setup(emc_timer_t *timer, uint32_t wait_time, uint8_t auto_reset);
uint8_t emc_timer_has_elapsed(emc_timer_t *timer);
void emc_timer_reset(emc_timer_t *timer);


#endif // EMC_TIMER_H