#ifndef EMC_RCC_H
#define EMC_RCC_H

/*
 * @file emc_rcc.h
 * @brief RCC library for STM32L4RG
 * RCC - Peripheral Power/Reset Control
 * @author JC
 */

 #include <stdint.h>

 typedef enum {
    EMC_RCC_PERIPH_PORTA = 0,
    EMC_RCC_PERIPH_PORTB,
    EMC_RCC_PERIPH_PORTC,
    EMC_RCC_PERIPH_PORTD,
    EMC_RCC_PERIPH_PORTE,
    EMC_RCC_PERIPH_PORTF,
    EMC_RCC_PERIPH_PORTG,
    EMC_RCC_PERIPH_PORTH,

    EMC_RCC_PERIPH_UART1,
    EMC_RCC_PERIPH_UART2,

    EMC_RCC_PERIPH_TIM2,
    EMC_RCC_PERIPH_TIM3,


    EMC_RCC_PERIPH_MAX
} emc_rcc_periph_t;

typedef struct {
    uint16_t pllm;
    uint16_t plln;
    uint16_t pllp;
    uint16_t pllq;
} emc_rcc_pll_config_t;

int emc_rcc_enable(emc_rcc_periph_t periph);
int emc_rcc_disable(emc_rcc_periph_t periph);
int emc_rcc_reset(emc_rcc_periph_t periph);
uint32_t emc_rcc_get_sysclk_freq(void);




#endif /* EMC_RCC_H */