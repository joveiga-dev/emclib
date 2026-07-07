
/*
 * @file emc_periph.h
 * @brief Peripheral library
 * @author JC
 */

#ifndef EMC_PERIPH_H
#define EMC_PERIPH_H

#include "emc_common.h"

/* Peripheral identifiers */
 typedef enum {
    /* GPIO */
    EMC_PERIPH_PORTA = 0,
    EMC_PERIPH_PORTB,
    EMC_PERIPH_PORTC,
    EMC_PERIPH_PORTD,
    EMC_PERIPH_PORTE,
    EMC_PERIPH_PORTF,
    EMC_PERIPH_PORTG,
    EMC_PERIPH_PORTH,
    /* USART / UART */
    EMC_PERIPH_UART1,
    EMC_PERIPH_USART2,
    EMC_PERIPH_USART3,
    EMC_PERIPH_UART4,
    EMC_PERIPH_UART5,
    /* TIMER */
    EMC_PERIPH_TIM2,
    EMC_PERIPH_TIM3,
    EMC_PERIPH_TIM4,
    EMC_PERIPH_TIM5,
    /* ADC */
    EMC_PERIPH_ADC1,
    /* SPI */
    EMC_PERIPH_SPI1,
    EMC_PERIPH_SPI2,
    EMC_PERIPH_SPI3,
    /* I2C */
    EMC_PERIPH_I2C1,
    EMC_PERIPH_I2C2,
    EMC_PERIPH_I2C3,

    EMC_PERIPH_MAX
} emc_periph_t;


emc_result_t emc_periph_enable(emc_periph_t periph);
emc_result_t emc_periph_disable(emc_periph_t periph);
emc_result_t emc_periph_reset(emc_periph_t periph);
bool emc_periph_is_enabled(emc_periph_t periph);


#endif /* EMC_PERIPH_H */