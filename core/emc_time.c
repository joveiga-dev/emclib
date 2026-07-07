#include "emc_time.h"
#include "stm32_time.h"
#include <stddef.h>


int emc_time_init(uint32_t tick_hz)
{
    return stm32_time_init(tick_hz);
}

uint32_t emc_time_get(void)
{
    return stm32_time_get();
}

void emc_time_delay_ms(uint32_t ms)
{
    stm32_time_delay_ms(ms);
}

void emc_time_delay_us(uint32_t us)
{
    stm32_time_delay_us(us);
}

void emc_time_get_timestamp(emc_time_timestamp_t *timestamp)
{
    if(timestamp == NULL) {
        return;
    }
    
    uint32_t total_ms = emc_time_get();

    timestamp->hours = total_ms / (1000 * 60 * 60);
    timestamp->minutes = (total_ms / (1000 * 60)) % 60;
    timestamp->seconds = (total_ms / 1000) % 60;
    timestamp->milliseconds = total_ms % 1000;
}