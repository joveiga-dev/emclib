#include "emc_clock.h"
#include "stm32_clock.h"

uint32_t emc_clock_get_freq(emc_clock_domain_t domain)
{
    switch (domain) {
        case EMC_CLOCK_CPU:
            return stm32_rcc_get_sysclk_freq();
        case EMC_CLOCK_BUS:
            return stm32_rcc_get_sysclk_freq(); 
            //return stm32_rcc_get_hclk_freq();
        default:
            return 0;
    }
}