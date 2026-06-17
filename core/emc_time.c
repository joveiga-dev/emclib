#include "emc_time.h"
#include "stm32_time.h"

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