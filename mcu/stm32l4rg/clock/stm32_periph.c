#include "stm32_periph.h"
#include "stm32_rcc_config.h"
#include "emc_common.h"

typedef struct {
    volatile uint32_t *en_reg;
    volatile uint32_t *rst_reg;
    uint32_t en_mask;
    uint32_t rst_mask;
} stm32_periph_desc_t;


static const stm32_periph_desc_t periph_desc[EMC_PERIPH_MAX] = {
    [EMC_PERIPH_PORTA] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIOAEN,
        .rst_mask = RCC_AHB2RSTR_GPIOARST
    },

    [EMC_PERIPH_PORTB] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIOBEN,
        .rst_mask = RCC_AHB2RSTR_GPIOBRST
    },
    [EMC_PERIPH_PORTC] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIOCEN,
        .rst_mask = RCC_AHB2RSTR_GPIOCRST
    },
    [EMC_PERIPH_PORTD] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIODEN,
        .rst_mask = RCC_AHB2RSTR_GPIODRST
    },
    [EMC_PERIPH_PORTE] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIOEEN,
        .rst_mask = RCC_AHB2RSTR_GPIOERST
    },
    [EMC_PERIPH_PORTF] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIOFEN,
        .rst_mask = RCC_AHB2RSTR_GPIOFRST
    },
    [EMC_PERIPH_PORTG] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIOGEN,
        .rst_mask = RCC_AHB2RSTR_GPIOGRST
    },
    [EMC_PERIPH_PORTH] = {
        .en_reg = &RCC->RCC_AHB2ENR,
        .rst_reg = &RCC->RCC_AHB2RSTR,
        .en_mask = RCC_AHB2ENR_GPIOHEN,
        .rst_mask = RCC_AHB2RSTR_GPIOHRST
    },
    [EMC_PERIPH_UART1] = {
        .en_reg = &RCC->RCC_APB2ENR,
        .rst_reg = &RCC->RCC_APB2RSTR,
        .en_mask = RCC_APB2ENR_USART1EN,
        .rst_mask = RCC_APB2RSTR_USART1RST
    },
    [EMC_PERIPH_USART2] = {
        .en_reg = &RCC->RCC_APB1ENR1,
        .rst_reg = &RCC->RCC_APB1RSTR1,
        .en_mask = RCC_APB1ENR1_USART2EN,
        .rst_mask = RCC_APB1RSTR1_USART2RST
    },

    [EMC_PERIPH_SPI1] = {
        .en_reg = &RCC->RCC_APB2ENR,
        .rst_reg = &RCC->RCC_APB2RSTR,
        .en_mask = RCC_APB2ENR_SPI1EN,
        .rst_mask = RCC_APB2RSTR_SPI1RST
    },

};

static const stm32_periph_desc_t *get_periph_desc(emc_periph_t periph)
{
    if ((uint32_t)periph >= EMC_PERIPH_MAX) {
        return 0;
    }
    return &periph_desc[periph];
}




emc_result_t stm32_periph_enable(emc_periph_t periph)
{
    const stm32_periph_desc_t *desc = get_periph_desc(periph);
    if (!desc || !desc->en_reg || (desc->en_mask == 0U)) {
        return EMC_STATUS_ERR;
    }

    SET_BIT(*(desc->en_reg), desc->en_mask);
    //*(desc->enable_reg) |= desc->mask;
    // read back to ensure the write has taken effect
    (void)*desc->en_reg;

    return EMC_STATUS_OK;
}

emc_result_t stm32_periph_disable(emc_periph_t periph)
{
    const stm32_periph_desc_t *desc = get_periph_desc(periph);
    if (!desc || !desc->en_reg || (desc->en_mask == 0U)) {
        return EMC_STATUS_ERR;
    }

    CLEAR_BIT(*(desc->en_reg), desc->en_mask);

    return EMC_STATUS_OK;
}

emc_result_t stm32_periph_reset(emc_periph_t periph)
{
    const stm32_periph_desc_t *desc = get_periph_desc(periph);
    if (!desc || !desc->rst_reg || (desc->rst_mask == 0U)) {
        return EMC_STATUS_ERR;
    }
    
    SET_BIT(*(desc->rst_reg), desc->rst_mask);
    (void)(*desc->rst_reg);
    CLEAR_BIT(*(desc->rst_reg), desc->rst_mask);

    return EMC_STATUS_OK;
}

bool stm32_periph_is_enabled(emc_periph_t periph)
{
    const stm32_periph_desc_t *desc = get_periph_desc(periph);
    if (!desc || !desc->en_reg || (desc->en_mask == 0U)) {
        return false;
    }

    return (READ_BIT(*(desc->en_reg), desc->en_mask) != 0U);
    //return (*(desc->enable_reg) & desc->mask) != 0;
}
