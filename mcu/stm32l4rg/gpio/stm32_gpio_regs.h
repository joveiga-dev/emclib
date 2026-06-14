#include "stm32l4xx.h"

typedef struct {
    volatile uint32_t MODER;   
    volatile uint32_t OTYPER;  
    volatile uint32_t OSPEEDR; 
    volatile uint32_t PUPDR;   
    volatile uint32_t IDR;     
    volatile uint32_t ODR;     
    volatile uint32_t BSRR;    
    volatile uint32_t LCKR;    
    volatile uint32_t AFR[2];
} GPIO_RegDef_t;


    
#define GPIO_OFFSET (0x400U)
#define GPIOA_BASE           (PERIPH_AHB2_BASE + 0x0000U)
#define GPIOB_BASE           (GPIOA_BASE + GPIO_OFFSET)
#define GPIOC_BASE           (GPIOB_BASE + GPIO_OFFSET)
#define GPIOD_BASE           (GPIOC_BASE + GPIO_OFFSET)
#define GPIOE_BASE           (GPIOD_BASE + GPIO_OFFSET)
#define GPIOF_BASE           (GPIOE_BASE + GPIO_OFFSET)
#define GPIOG_BASE           (GPIOF_BASE + GPIO_OFFSET)
#define GPIOH_BASE           (GPIOG_BASE + GPIO_OFFSET)

#define GPIOA                      ((GPIO_RegDef_t *)GPIOA_BASE)
#define GPIOB                      ((GPIO_RegDef_t *)GPIOB_BASE)
#define GPIOC                      ((GPIO_RegDef_t *)GPIOC_BASE)
#define GPIOD                      ((GPIO_RegDef_t *)GPIOD_BASE)
#define GPIOE                      ((GPIO_RegDef_t *)GPIOE_BASE)
#define GPIOF                      ((GPIO_RegDef_t *)GPIOF_BASE)
#define GPIOG                      ((GPIO_RegDef_t *)GPIOG_BASE)
#define GPIOH                      ((GPIO_RegDef_t *)GPIOH_BASE)

