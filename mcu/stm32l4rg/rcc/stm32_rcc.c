#include "stm32_rcc.h"

typedef struct {
    volatile uint32_t *enable_reg;
    volatile uint32_t *reset_reg;
    uint32_t mask;
} stm32_rcc_periph_desc_t;

static const stm32_rcc_periph_desc_t periph_desc[EMC_RCC_PERIPH_MAX] = {
    [EMC_RCC_PERIPH_PORTA] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIOAEN
    },

    [EMC_RCC_PERIPH_PORTB] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIOBEN
    },
    [EMC_RCC_PERIPH_PORTC] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIOCEN
    },
    [EMC_RCC_PERIPH_PORTD] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIODEN
    },
    [EMC_RCC_PERIPH_PORTE] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIOEEN
    },
    [EMC_RCC_PERIPH_PORTF] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIOFEN
    },
    [EMC_RCC_PERIPH_PORTG] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIOGEN
    },
    [EMC_RCC_PERIPH_PORTH] = {
        .enable_reg = &RCC->RCC_AHB2ENR,
        .reset_reg = &RCC->RCC_AHB2RSTR,
        .mask = RCC_AHB2ENR_GPIOHEN
    },
    [EMC_RCC_PERIPH_UART1] = {
        .enable_reg = &RCC->RCC_APB2ENR,
        .reset_reg = &RCC->RCC_APB2RSTR,
        .mask = RCC_APB2ENR_USART1EN
    },
    [EMC_RCC_PERIPH_UART2] = {
        .enable_reg = &RCC->RCC_APB1ENR1,
        .reset_reg = &RCC->RCC_APB1RSTR1,
        .mask = RCC_APB1ENR1_USART2EN
    }
};

static const stm32_rcc_periph_desc_t *get_periph_desc(emc_rcc_periph_t periph)
{
    if ((uint32_t)periph >= EMC_RCC_PERIPH_MAX) {
        return 0;
    }
    return &periph_desc[periph];
}


int stm32_rcc_enable(emc_rcc_periph_t periph)
{
    const stm32_rcc_periph_desc_t *desc = get_periph_desc(periph);
    if (!desc) {
        return -1;
    }

    *(desc->enable_reg) |= desc->mask;
    (void)*desc->enable_reg;

    return 0;
}

int stm32_rcc_disable(emc_rcc_periph_t periph)
{
    const stm32_rcc_periph_desc_t *desc = get_periph_desc(periph);
    if (!desc) {
        return -1;
    }

    *(desc->enable_reg) &= ~(desc->mask);

    return 0;
}

int stm32_rcc_reset(emc_rcc_periph_t periph)
{
    const stm32_rcc_periph_desc_t *desc = get_periph_desc(periph);
    if (!desc) {
        return -1;
    }
    *(desc->reset_reg) |= desc->mask;
    *(desc->reset_reg) &= ~(desc->mask);
    return 0;
}