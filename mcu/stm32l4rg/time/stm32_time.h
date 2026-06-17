#ifndef STM32_TIME_H
#define STM32_TIME_H

#include <stdint.h>
#include <stdbool.h>

int stm32_time_init(uint32_t tick_hz);
uint32_t stm32_time_get(void);
void stm32_time_delay_ms(uint32_t ms);
void stm32_time_delay_us(uint32_t us);
uint8_t stm32_time_elapsed(uint32_t start_tick, uint32_t delay_ms);

#endif // STM32_TIME_H