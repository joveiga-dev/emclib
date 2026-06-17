#include "stm32_time.h"
#include "stm32l4xx.h"
#include "stm32_rcc.h"

typedef struct {
    volatile uint32_t SYST_CSR;   /* offset: 0x000 (R/W) SysTick Control and Status Register */
    volatile uint32_t SYST_RVR;   /* offset: 0x004 (R/W) SysTick Reload and Value Register */
    volatile uint32_t SYST_CVR;   /* offset: 0x008 (R/W) SysTick Current Value Register */
    volatile uint32_t SYST_CALIB; /* offset 0x00C (R/ )  SysTick Calibration Value Register*/
} Systick_RegDef_t;

#define SYSTICK ((Systick_RegDef_t *)SYSTICK_BASE)

static volatile uint32_t s_ticks = 0;

static void systick_start(uint32_t reload)
{
    SYSTICK->SYST_RVR = reload; 
    SYSTICK->SYST_CVR = 0UL; 
    SYSTICK->SYST_CSR = SYSTICK_CSR_CLKSOURCE | 
                        SYSTICK_CSR_TICKINT   | 
                        SYSTICK_CSR_ENABLE;
}

static void systick_stop(void)
{
    SYSTICK->SYST_CSR &= ~SYSTICK_CSR_TICKINT;
    SYSTICK->SYST_CSR &= ~SYSTICK_CSR_ENABLE;
    SYSTICK->SYST_CVR = 0;
}

void SysTick_Handler(void)
{
    s_ticks++;
}


int stm32_time_init(uint32_t tick_hz)
{
    uint32_t reload = (stm32_rcc_get_sysclk_freq() / tick_hz) - 1U;
    
    if ((tick_hz == 0) || (reload > SYSTICK_RVR_RELOAD_Msk)) // 24-bit
    {
        return -1;
    }

    systick_start(reload);
    return 0;
}

uint32_t stm32_time_get(void)
{
    return s_ticks;
}

void stm32_time_delay_ms(uint32_t ms)
{
    uint32_t start_tick = stm32_time_get();
    uint32_t delay_ticks = ms; // Assuming tick_hz is 1000 for 1ms tick

    while ((stm32_time_get() - start_tick) < delay_ticks) {
        __asm volatile ("WFI");
    }
}

void stm32_time_delay_us(uint32_t us)
{
    uint32_t start_tick = stm32_time_get();
    uint32_t delay_ticks = (us * (stm32_rcc_get_sysclk_freq() / 1000000U)) / (SYSTICK->SYST_RVR + 1U);

    while ((stm32_time_get() - start_tick) < delay_ticks) {
        __asm volatile ("WFI");
    }
}

uint8_t stm32_time_elapsed(uint32_t start_tick, uint32_t delay_ms)
{
    uint32_t current_tick = stm32_time_get();
    uint32_t elapsed_ticks = current_tick - start_tick;
    uint32_t delay_ticks = delay_ms; 

    return (elapsed_ticks >= delay_ticks) ? 1 : 0;
}



