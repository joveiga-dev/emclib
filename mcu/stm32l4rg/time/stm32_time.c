#include "stm32_time.h"
#include "stm32l4xx.h"
#include "stm32_clock.h"

typedef struct {
    // SysTick Control and Status Register
    // COUNTFLAG   Returns 1 if the timer counted to 0 since last time was read
    // CLKSOURCE   SysTick clock source
    // TICKINIT    Enables SysTick exception request
    // ENABLE      Enable SysTick counter
    volatile uint32_t syst_csr;
    // SysTick Reload Value Register 
    // 0x00ffffff [23:0] RELOAD        The value to load into the SysTick Current Value Register when the counter reaches 0.  
    volatile uint32_t syst_rvr; 
    // SysTick Current Value Register
    // 0x00ffffff [23:0] CURRENT       The current value of the SysTick counter. This value is decremented by 1 every clock cycle. When it reaches 0, it is reloaded with the value in the SysTick Reload Value Register (SYST_RVR).  
    volatile uint32_t syst_cvr;
    // SysTick Calibration Value Register
    // 0X80000000 [31] NOREF         Indicates whether the reference clock is provided
    // 0X40000000 [30] SKEW          Indicates whether the calibration
    // 0x00ffffff [23:0] TENMS         Indicates the number of clock cycles for 10ms
    volatile uint32_t syst_calib; 
} Systick_RegDef_t;

#define systick_hw_desc ((Systick_RegDef_t *)SYSTICK_BASE)

static volatile uint32_t s_ticks = 0;

static void systick_start(uint32_t reload)
{
    systick_hw_desc->syst_rvr = reload; 
    systick_hw_desc->syst_cvr = 0UL; 
    systick_hw_desc->syst_csr = SYSTICK_CSR_CLKSOURCE | 
                                 SYSTICK_CSR_TICKINT   | 
                                 SYSTICK_CSR_ENABLE;
}

static void systick_stop(void)
{
    systick_hw_desc->syst_csr &= ~SYSTICK_CSR_TICKINT;
    systick_hw_desc->syst_csr &= ~SYSTICK_CSR_ENABLE;
    systick_hw_desc->syst_cvr = 0;
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
    uint32_t delay_ticks = (us * (stm32_rcc_get_sysclk_freq() / 1000000U)) / (systick_hw_desc->syst_rvr + 1U);

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



