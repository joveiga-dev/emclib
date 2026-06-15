#ifndef STM32_RCC_H
#define STM32_RCC_H

/*
 * @file stm32_rcc.h
 * @brief RCC library for STM32L4RG
 * @author JC
 */

#include "stm32l4xx.h"
#include "emc_rcc.h"
#include <stdint.h>

typedef struct {
    volatile uint32_t RCC_CR; 
    volatile uint32_t RCC_ICSCR;
    volatile uint32_t RCC_CFGR;
    volatile uint32_t RCC_PLLCFGR;
    volatile uint32_t RCC_PLLSAI1CFGR;
    volatile uint32_t RCC_PLLSAI2CFGR;
    volatile uint32_t RCC_CIER;
    volatile uint32_t RCC_CIFR;
    volatile uint32_t RCC_CICR;
    uint32_t RESERVED0;
    volatile uint32_t RCC_AHB1RSTR;
    volatile uint32_t RCC_AHB2RSTR;
    volatile uint32_t RCC_AHB3RSTR;
    uint32_t RESERVED1;
    volatile uint32_t RCC_APB1RSTR1;
    volatile uint32_t RCC_APB1RSTR2;
    volatile uint32_t RCC_APB2RSTR;
    uint32_t RESERVED2;
    volatile uint32_t RCC_AHB1ENR;
    volatile uint32_t RCC_AHB2ENR;
    volatile uint32_t RCC_AHB3ENR;
    uint32_t RESERVED3;
    volatile uint32_t RCC_APB1ENR1;
    volatile uint32_t RCC_APB1ENR2;
    volatile uint32_t RCC_APB2ENR; 
    uint32_t RESERVED4;
    volatile uint32_t RCC_AHB1SMENR;
    volatile uint32_t RCC_AHB2SMENR;
    volatile uint32_t RCC_AHB3SMENR;
    uint32_t RESERVED5;
    volatile uint32_t RCC_APB1SMENR1; 
    volatile uint32_t RCC_APB1SMENR2;
} RCC_RegDef_t;

#define RCC ((RCC_RegDef_t *)RCC_BASE)
#define RCC_AHB2ENR_GPIOHEN       (1U << 7)
#define RCC_AHB2ENR_GPIOGEN       (1U << 6)
#define RCC_AHB2ENR_GPIOFEN       (1U << 5)
#define RCC_AHB2ENR_GPIOEEN       (1U << 4)
#define RCC_AHB2ENR_GPIODEN       (1U << 3)
#define RCC_AHB2ENR_GPIOCEN       (1U << 2)
#define RCC_AHB2ENR_GPIOBEN       (1U << 1)
#define RCC_AHB2ENR_GPIOAEN       (1U << 0)

#define RCC_APB1ENR1_UART5EN    (1U << 20)
#define RCC_APB1ENR1_UART4EN    (1U << 19)
#define RCC_APB1ENR1_USART3EN   (1U << 18)
#define RCC_APB1ENR1_USART2EN   (1U << 17)
#define RCC_APB1ENR2_LPUART1EN  (1U << 0) // Low power uart 1
#define RCC_APB2ENR_USART1EN    (1U << 14) 



// Function prototypes
int stm32_rcc_enable(emc_rcc_periph_t periph);
int stm32_rcc_disable(emc_rcc_periph_t periph);
int stm32_rcc_reset(emc_rcc_periph_t periph);
uint32_t stm32_rcc_get_sysclk_freq(void);


#endif // STM32_RCC_H