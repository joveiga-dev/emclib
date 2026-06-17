#ifndef EMC_TIME_H
#define EMC_TIME_H

#include <stdint.h>

int emc_time_init(uint32_t tick_ms);
uint32_t emc_time_get(void);
void emc_time_delay_ms(uint32_t ms);
void emc_time_delay_us(uint32_t us);


#endif // EMC_TIME_H