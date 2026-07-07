#include "stm32l4xx.h"
#include "emc_periph.h"
#include "emc_common.h"

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

/* Clock Control register */
#define RCC_CR_PLLON             BIT(24)
#define RCC_CR_HSEON             BIT(16)
#define RCC_CR_HSIRDY            BIT(10)
#define RCC_CR_HSION             BIT(8)
/* Range of MSI clock */
#define RCC_CR_MSIRANGE_Pos      4
#define RCC_CR_MSIRANGE_Msk      (0xf << RCC_CR_MSIRANGE_Pos)
#define RCC_CR_MSIRANGE_100KHZ   0
#define RCC_CR_MSIRANGE_200KHZ   1
#define RCC_CR_MSIRANGE_400KHZ   2
#define RCC_CR_MSIRANGE_800KHZ   3
#define RCC_CR_MSIRANGE_1MHZ     4
#define RCC_CR_MSIRANGE_2MHZ     5
#define RCC_CR_MSIRANGE_4MHZ     6
#define RCC_CR_MSIRANGE_8MHZ     7
#define RCC_CR_MSIRANGE_16MHZ    8
#define RCC_CR_MSIRANGE_24MHZ    9
#define RCC_CR_MSIRANGE_32MHZ    10
#define RCC_CR_MSIRANGE_48MHZ    11
#define RCC_CR_MSIRANGE(r)       (((r) << RCC_CR_MSIRANGE_Pos) & RCC_CR_MSIRANGE_Msk)
#define RCC_CR_MSIRGSEL          BIT(3)
#define RCC_CR_MSIPLLEN          BIT(2)
#define RCC_CR_MSIRDY            BIT(1)
#define RCC_CR_MSION             BIT(0)

/* Clock configuration register */
#define RCC_CFGR_MCOSEL_Pos      24
#define RCC_CFGR_MCOSEL_Msk      (0xf << RCC_CFGR_MCOSEL_Pos)
#define RCC_CFGR_MCOSEL_NOCLOCK  0
#define RCC_CFGR_MCOSEL_SYSCLK   1
#define RCC_CFGR_MCOSEL_MSI      2
#define RCC_CFGR_MCOSEL_HSI16    3
#define RCC_CFGR_MCOSEL_HSE      4
#define RCC_CFGR_MCOSEL_PLL      5
#define RCC_CFGR_MCOSEL_LSI      6
#define RCC_CFGR_MCOSEL_LSE      7
#define RCC_CFGR_MCOSEL(r)       (((r) << RCC_CFGR_MCOSEL_Pos) & RCC_CFGR_MCOSEL_Msk)

#define RCC_CFGR_PPRE2_Pos        11
#define RCC_CFGR_PPRE2_Msk        (0x7 << RCC_CFGR_PPRE2_Pos)
#define RCC_CFGR_PPRE1_Pos        8
#define RCC_CFGR_PPRE1_Msk        (0x7 << RCC_CFGR_PPRE1_Pos)
#define RCC_CFGR_PPRE_DIV1        0x0
#define RCC_CFGR_PPRE_DIV2        0x4
#define RCC_CFGR_PPRE_DIV4        0x5
#define RCC_CFGR_PPRE_DIV8        0x6
#define RCC_CFGR_PPRE_DIV16       0x7

#define RCC_CFGR_HPRE_Pos         4
#define RCC_CFGR_HPRE_Msk         (0xf << RCC_CFGR_HPRE_Pos)
#define RCC_CFGR_HPRE_DIV1        0x0
#define RCC_CFGR_HPRE_DIV2        0x8
#define RCC_CFGR_HPRE_DIV4        0x9
#define RCC_CFGR_HPRE_DIV8        0xa
#define RCC_CFGR_HPRE_DIV16       0xb
#define RCC_CFGR_HPRE_DIV64       0xc
#define RCC_CFGR_HPRE_DIV128      0xd
#define RCC_CFGR_HPRE_DIV256      0xe
#define RCC_CFGR_HPRE_DIV512      0xf
/* System clock switch status */
#define RCC_CFGR_SWS_Pos          2
#define RCC_CFGR_SWS_Msk          (0x3 << RCC_CFGR_SWS_Pos)
#define RCC_CFGR_SWS(r)           (((r) << RCC_CFGR_SWS_Pos) & RCC_CFGR_SWS_Msk)
/* System clock switch */
#define RCC_CFGR_SW_Pos           0
#define RCC_CFGR_SW_Msk           (0x3 << RCC_CFGR_SW_Pos)
#define RCC_CFGR_MSI              0x0
#define RCC_CFGR_HSI16            0x1
#define RCC_CFGR_HSE              0x2
#define RCC_CFGR_PLL              0x3
#define RCC_CFGR_SW(r)            (((r) << RCC_CFGR_SW_Pos) & RCC_CFGR_SW_Msk)

/* PLL configuration */
#define RCC_PLLCFGR_PLLR_Pos      25
#define RCC_PLLCFGR_PLLR_Msk      (0x3 << RCC_PLLCFGR_PLLR_Pos)
#define RCC_PLLCFGR_PLLR_DIV2     0x0
#define RCC_PLLCFGR_PLLR_DIV4     0x1
#define RCC_PLLCFGR_PLLR_DIV6     0x2
#define RCC_PLLCFGR_PLLR_DIV8     0x3
#define RCC_PLLCFGR_PLLREN        BIT(24)
#define RCC_PLLCFGR_PLLQ_Pos      21
#define RCC_PLLCFGR_PLLQ_Msk      (0x3 << RCC_PLLCFGR_PLLQ_Pos)
#define RCC_PLLCFGR_PLLQ_DIV2     0x0
#define RCC_PLLCFGR_PLLQ_DIV4     0x1
#define RCC_PLLCFGR_PLLQ_DIV6     0x2
#define RCC_PLLCFGR_PLLQ_DIV8     0x3
#define RCC_PLLCFGR_PLLQEN        BIT(20)
/* 0 == 7, 1 == 17*/
#define RCC_PLLCFGR_PLLP          BIT(17)
#define RCC_PLLCFGR_PLLP_DIV7     0x0
#define RCC_PLLCFGR_PLLP_DIV17    RCC_PLLCFGR_PLLP
#define RCC_PLLCFGR_PLLPEN        BIT(16)
#define RCC_PLLCFGR_PLLN_Pos      8
#define RCC_PLLCFGR_PLLN_Msk      (0x7f << RCC_PLLCFGR_PLLN_Pos)
#define RCC_PLLCFGR_PLLN(r)       (((r) << RCC_PLLCFGR_PLLN_Pos) & RCC_PLLCFGR_PLLN_Msk)
#define RCC_PLLCFGR_PLLM_Pos      4
#define RCC_PLLCFGR_PLLM_Msk      (0x7 << RCC_PLLCFGR_PLLM_Pos)
#define RCC_PLLCFGR_PLLM(r)       (((r) << RCC_PLLCFGR_PLLM_Pos) & RCC_PLLCFGR_PLLM_Msk)
#define RCC_PLLCFGR_PLLSRC_Pos   0
#define RCC_PLLCFGR_PLLSRC_Msk   (0x3 << RCC_PLLCFGR_PLLSRC_Pos)
#define RCC_PLLCFGR_PLLSRC_NONE  0x0
#define RCC_PLLCFGR_PLLSRC_MSI   0x1
#define RCC_PLLCFGR_PLLSRC_HSI16 0x2
#define RCC_PLLCFGR_PLLSRC_HSE   0x3

/* AHB1 peripheral clock enable register */
#define RCC_AHB1ENR_DMA2DEN      BIT(17)
#define RCC_AHB1ENR_TSCEN        BIT(16)
#define RCC_AHB1ENR_CRCEN        BIT(12)
#define RCC_AHB1ENR_FLASHEN      BIT(8)
#define RCC_AHB1ENR_DMA2EN       BIT(1)
#define RCC_AHB1ENR_DMA1EN       BIT(0)
/* AHB2 peripheral clock enable register */
#define RCC_AHB2ENR_RNGEN        BIT(18)
#define RCC_AHB2ENR_HASHEN       BIT(17)
#define RCC_AHB2ENR_AESEN        BIT(16)
#define RCC_AHB2ENR_ADCEN        BIT(13)
#define RCC_AHB2ENR_GPIOIEN      BIT(8)
#define RCC_AHB2ENR_GPIOHEN      BIT(7)
#define RCC_AHB2ENR_GPIOGEN      BIT(6)
#define RCC_AHB2ENR_GPIOFEN      BIT(5)
#define RCC_AHB2ENR_GPIOEEN      BIT(4)
#define RCC_AHB2ENR_GPIODEN      BIT(3)
#define RCC_AHB2ENR_GPIOCEN      BIT(2)
#define RCC_AHB2ENR_GPIOBEN      BIT(1)
#define RCC_AHB2ENR_GPIOAEN      BIT(0)

/* AHB2 peripheral clock reset register */
#define RCC_AHB2RSTR_GPIOIRST    BIT(8)
#define RCC_AHB2RSTR_GPIOHRST    BIT(7)
#define RCC_AHB2RSTR_GPIOGRST    BIT(6)
#define RCC_AHB2RSTR_GPIOFRST    BIT(5)
#define RCC_AHB2RSTR_GPIOERST    BIT(4)
#define RCC_AHB2RSTR_GPIODRST    BIT(3)
#define RCC_AHB2RSTR_GPIOCRST    BIT(2)
#define RCC_AHB2RSTR_GPIOBRST    BIT(1)
#define RCC_AHB2RSTR_GPIOARST    BIT(0)
/* AHB3 peripheral clock enable register */
#define RCC_AHB3ENR_QSPIEN       BIT(8)
#define RCC_AHB3ENR_FMCEN        BIT(0)
/* APB1 peripheral clock enable register */
#define RCC_APB1ENR1_LPTIM1EN    BIT(31)
#define RCC_APB1ENR1_OPAMPEN     BIT(30)
#define RCC_APB1ENR1_DAC1EN      BIT(29)
#define RCC_APB1ENR1_PWREN       BIT(28)
#define RCC_APB1ENR1_CAN2EN      BIT(26)
#define RCC_APB1ENR1_CAN1EN      BIT(25)
#define RCC_APB1ENR1_CRSEN       BIT(24)
#define RCC_APB1ENR1_I2C3EN      BIT(23)
#define RCC_APB1ENR1_I2C2EN      BIT(22)
#define RCC_APB1ENR1_I2C1EN      BIT(21)
#define RCC_APB1ENR1_UART5EN     BIT(20)
#define RCC_APB1ENR1_UART4EN     BIT(19)
#define RCC_APB1ENR1_USART3EN    BIT(18)
#define RCC_APB1ENR1_USART2EN    BIT(17)
#define RCC_APB1ENR1_SPI3EN      BIT(15)
#define RCC_APB1ENR1_SPI2EN      BIT(14)
#define RCC_APB1ENR1_LCDEN       BIT(9)
#define RCC_APB2ENR1_TIM7EN       BIT(5)
#define RCC_APB2ENR1_TIM6EN       BIT(4)
#define RCC_APB2ENR1_TIM5EN       BIT(3)
#define RCC_APB2ENR1_TIM4EN       BIT(2)
#define RCC_APB2ENR1_TIM3EN       BIT(1)
#define RCC_APB2ENR1_TIM2EN       BIT(0)
/* APB1 peripheral clock reset register */
#define RCC_APB1RSTR1_USART2RST   BIT(17)
#define RCC_APB1RSTR1_SPI3RST     BIT(15)
#define RCC_APB1RSTR1_SPI2RST     BIT(14)

/* APB1 peripheral clock enable register 2*/
#define RCC_APB1ENR2_LPTIM2EN   BIT(5)
#define RCC_APB1ENR2_SWPMI1EN   BIT(2)
#define RCC_APB1ENR2_I2C4EN     BIT(1)
#define RCC_APB1ENR2_LPUART1EN  BIT(0)
/* APB2 peripheral clock enable register */
#define RCC_APB2ENR_TIM17EN     BIT(18)
#define RCC_APB2ENR_TIM16EN     BIT(17)
#define RCC_APB2ENR_TIM15EN     BIT(16)
#define RCC_APB2ENR_USART1EN    BIT(14)
#define RCC_APB2ENR_SPI1EN      BIT(12)
#define RCC_APB2ENR_TIM1EN      BIT(11)
#define RCC_APB2ENR_SDMMC1EN    BIT(10)
/* APB2 peripheral clock reset register */
#define RCC_APB2RSTR_TIM17RST     BIT(18)
#define RCC_APB2RSTR_TIM16RST     BIT(17)
#define RCC_APB2RSTR_TIM15RST     BIT(16)
#define RCC_APB2RSTR_USART1RST    BIT(14)
#define RCC_APB2RSTR_SPI1RST      BIT(12)
#define RCC_APB2RSTR_TIM1RST      BIT(11)

#define SYSCLOCK_MAX_FREQ       80000000U