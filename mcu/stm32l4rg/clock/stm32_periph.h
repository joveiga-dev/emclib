#ifndef STM32_RCC_H
#define STM32_RCC_H

/*
 * @file stm32_periph.h
 * @brief Peripheral library for STM32L4RG
 * @author JC
 */

#include "stm32l4xx.h"
#include "emc_periph.h"
#include <stdint.h>


/* System clock (sysclk) sources*/
typedef enum {
    RCC_SYSCLK_SRC_MSI = 0,
    RCC_SYSCLK_SRC_HSI16,
    RCC_SYSCLK_SRC_HSE,
    RCC_SYSCLK_SRC_PLL
} stm32_rcc_sysclk_src_t;

/* Definitions of PLLs clock source configuration */
typedef enum {
    RCC_PLL_SRC_NONE = 0,       /*!< No clock source */
    RCC_PLL_SRC_MSI,            /*!< MSI clock source */
    RCC_PLL_SRC_HSI,            /*!< HSI clock source */
    RCC_PLL_SRC_HSE             /*!< HSE clock source */
} stm32_rcc_pll_src_t;

/* Definitions of PLLs clock selection */
typedef enum {
    RCC_PLL_NONE = 0,           /*!< No PLL selected */
    RCC_PLL_MAIN,               /*!< Main PLL selected */
    RCC_PLL_SAI1,               /*!< SAI1 PLL selected */
    RCC_PLL_SAI2                /*!< SAI2 PLL selected */
} stm32_rcc_pll_sel_t;

/* Structure to hold clock frequencies */
typedef struct {
    uint32_t sysclk;
    uint32_t hclk;
    uint32_t pclk1;
    uint32_t pclk2;
} stm32_rcc_clocks_freq_t;

/* PLL configuration structure */
typedef struct {
    uint32_t plln;
    uint32_t pllr;
    uint32_t pllp;
    uint32_t pllq;
} stm32_rcc_pll_params_t;

/* Clock dividers configuration structure */
typedef struct {
    uint32_t ahb_div;
    uint32_t apb1_div;
    uint32_t apb2_div;
} stm32_rcc_clock_dividers_t;

uint32_t stm32_rcc_get_sysclock_source(void);

int stm32_rcc_pll_config(stm32_rcc_pll_params_t *cfg_pll, uint32_t pll);
bool stm32_rcc_init_system_clock(void);
void stm32_rcc_get_clocks(stm32_rcc_clocks_freq_t *clocks);

emc_result_t stm32_periph_enable(emc_periph_t periph);
emc_result_t stm32_periph_disable(emc_periph_t periph);
emc_result_t stm32_periph_reset(emc_periph_t periph);
bool stm32_periph_is_enabled(emc_periph_t periph);


#endif // STM32_RCC_H