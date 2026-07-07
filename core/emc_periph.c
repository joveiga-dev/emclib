#include "emc_periph.h"
#include "stm32_periph.h"

emc_result_t emc_periph_enable(emc_periph_t periph)
{
    return stm32_periph_enable(periph);
}

emc_result_t emc_periph_disable(emc_periph_t periph)
{
    return stm32_periph_disable(periph);
}

emc_result_t emc_periph_reset(emc_periph_t periph)
{
    return stm32_periph_reset(periph);
}
