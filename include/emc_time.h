#ifndef EMC_TIME_H
#define EMC_TIME_H

#include <stdint.h>

typedef struct {
    uint8_t hours;
    uint8_t minutes;
    uint8_t seconds;
    uint16_t milliseconds;
} emc_time_timestamp_t;

int emc_time_init(uint32_t tick_hz);
uint32_t emc_time_get(void);
void emc_time_delay_ms(uint32_t ms);
void emc_time_delay_us(uint32_t us);
void emc_time_get_timestamp(emc_time_timestamp_t *timestamp);


#endif // EMC_TIME_H