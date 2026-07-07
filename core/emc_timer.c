#include "emc_timer.h"
#include "emc_time.h"

void emc_timer_setup(emc_timer_t *timer, uint32_t wait_time, uint8_t auto_reset)
{
    timer->wait_time = wait_time;
    timer->src_time = emc_time_get() + wait_time;
    timer->auto_reset = auto_reset;
    timer->has_elapsed = 0;
}

uint8_t emc_timer_has_elapsed(emc_timer_t *timer)
{
    uint32_t now = emc_time_get();
    uint8_t has_elapsed = (now >= timer->src_time) ? 1: 0;
    if (timer->has_elapsed) {
        return 0;
    }
    if (has_elapsed) {
        if(timer->auto_reset) {
            uint32_t drift = now - timer->src_time;
            timer->src_time = (now + timer->wait_time) - drift;
        } else {
            timer->has_elapsed = 1;
        }
    }
    return has_elapsed;
}

void emc_timer_reset(emc_timer_t *timer)
{
    emc_timer_setup(timer, timer->wait_time, timer->auto_reset);
}