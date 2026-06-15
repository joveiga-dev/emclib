#include "emc_rcc.h"
#include "stm32_rcc.h"

int emc_rcc_enable(emc_rcc_periph_t periph)
{
    return stm32_rcc_enable(periph);
}

int emc_rcc_disable(emc_rcc_periph_t periph)
{
    return stm32_rcc_disable(periph);
}