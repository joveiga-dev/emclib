#pragma once
#include <stdint.h>
#include "emc_common.h"

#define FLASH_BASE                 (0x08000000U)
#define SRAM_BASE                  (0x20000000U)
#define FLASH_SIZE                 (512U * 1024U) // 512 KB
#define SRAM_SIZE                  (96U * 1024U)  // 96 KB
#define SRAM_END                   (SRAM_BASE + SRAM_SIZE)

#define PERIPH_BASE                (0x40000000U)
#define PERIPH_APB1_BASE           (PERIPH_BASE + 0x00000U)
#define PERIPH_APB2_BASE           (PERIPH_BASE + 0x10000U)
#define PERIPH_AHB1_BASE           (PERIPH_BASE + 0x20000U)
#define PERIPH_AHB2_BASE           (0x48000000U)

#define RCC_AHB2ENR_OFFSET         (0x4CU)
#define SCS_BASE                   (0xE000E000UL)
#define SYSTICK_BASE               (SCS_BASE + 0x0010UL)
#define RCC_BASE                   (PERIPH_AHB1_BASE + 0x1000U)
#define FLASH_REGISTER_BASE        (PERIPH_AHB1_BASE + 0x2000U)


#define LPUART1_BASE            (PERIPH_AHB1_BASE + 0x8000U)
#define USART1_BASE             (PERIPH_APB2_BASE + 0x3800U)
#define USART2_BASE             (PERIPH_APB1_BASE + 0x4400U)
#define USART3_BASE             (PERIPH_APB1_BASE + 0x4800U)
#define UART4_BASE              (PERIPH_APB1_BASE + 0x4C00U)
#define UART5_BASE              (PERIPH_APB1_BASE + 0x5000U)

/* USART Enable */
#define USART_CR1_UE BIT(0U)
/* Tx Enable */
#define USART_CR1_TE BIT(3U)
/*Rx Enable */
#define USART_CR1_RE BIT(2U)
/* USART Parity Selection (0- even, 1 - odd) */
#define USART_CR1_PS BIT(9U)
/* USART Parity Control Enable */
#define USART_CR1_PCE BIT(10U)
/* USART Word Length */
#define USART_CR1_M0_Pos (12U)
#define USART_CR1_M0_Msk (0x1UL << USART_CR1_M0_Pos)
#define USART_CR1_M0 USART_CR1_M0_Msk
#define USART_CR1_M1_Pos (28U)
#define USART_CR1_M1_Msk (0x1UL << USART_CR1_M1_Pos)
#define USART_CR1_M1 USART_CR1_M1_Msk
#define USART_CR1_OVER8 BIT(15U)

/* RX Enable Interrupt */
#define USART_CR1_RXNEIE BIT(5U)
#define USART_CR1_TXEIE BIT(7U)

/* USART baud rate register */
// #define USART_BRR_USART15_4

/* USART interrupt and status register */
/* RX enable acknowledge flag */
#define USART_ISR_REACK BIT(22)
/* Tx enable acknowledge flag */
#define USART_ISR_TEACK BIT(21)
/* Busy flag */
#define USART_ISR_BUSY BIT(16)
/* Transmit data register empty */
#define USART_ISR_TXE BIT(7)
/* Read data register not empty */
#define USART_ISR_RXNE BIT(5)

#define USART_CR2_STOP (0x3U << 12)
#define USART_CR2_STOP_0 (0x1U << 12)
#define USART_CR2_STOP_1 (0x1U << 13)

#define USART_CR3_RTSE BIT(8)
#define USART_CR3_CTSE BIT(9)

/* SPI definitions */

#define SPI1_BASE (PERIPH_APB2_BASE + 0x3000U)
#define SPI2_BASE (PERIPH_APB1_BASE + 0x3800U)
#define SPI3_BASE (PERIPH_APB1_BASE + 0x3C00U)

/* SPI_CR1 Control Register 1 */
#define SPI_CR1_CPHA   (0x1U << 0)  // Clock phase
#define SPI_CR1_CPOL   (0x1U << 1)  // Clock polarity  0: CK to 0 when idle, 1: CK to 1 when idle
#define SPI_CR1_MSTR   (0x1U << 2)  // Master selection -> 0: Slave, 1: Master
#define SPI_CR1_BR_Pos (3U)         // Baud rate control
#define SPI_CR1_BR_Msk (0x7U << SPI_CR1_BR_Pos)
#define SPI_CR1_BR     SPI_CR1_BR_Msk
#define SPI_CR1_SPE    (0x1U << 6)  // SPI enable -> 0: Disabled, 1: Enabled
#define SPI_CR1_LSBFIRST (0x1U << 7) // Frame format -> 0: MSB first, 1: LSB first
#define SPI_CR1_SSI    (0x1U << 8)  // Internal slave select
#define SPI_CR1_SSM    (0x1U << 9)  // Software slave management
#define SPI_CR1_RXONLY (0x1U << 10) // Receive only -> 0: Full duplex, 1: Receive only
#define SPI_CR1_BIDIOE  (0x1U << 14) // Bidirectional data mode enable -> 0: 2-line unidirectional, 1: 1-line bidirectional
#define SPI_CR1_BIDIMODE (0x1U << 15) // Bidirectional data mode enable -> 0: 2-line unidirectional, 1: 1-line bidirectional


/* SPI_CR2 Control Register 2 */
#define SPI_CR2_RXDMAEN (0x1U << 0)  // Rx buffer DMA enable -> 0: Disabled, 1: Enabled
#define SPI_CR2_TXDMAEN (0x1U << 1)  // Tx buffer DMA enable -> 0: Disabled, 1: Enabled
#define SPI_CR2_SSOE    (0x1U << 2)  // SS output enable -> 0: Disabled, 1: Enabled
#define SPI_CR2_RXNEIE   (0x1U << 6)  // RX buffer not empty interrupt enable -> 0: Disabled, 1: Enabled
#define SPI_CR2_TXEIE    (0x1U << 7)  // TX buffer empty interrupt enable -> 0: Disabled, 1: Enabled
#define SPI_CR2_DS_Pos (8U)          // Data size
#define SPI_CR2_DS_Msk (0xFU << SPI_CR2_DS_Pos)
#define SPI_CR2_DS     SPI_CR2_DS_Msk
#define SPI_CR2_FRXTH  (0x1U << 12) // FIFO reception threshold -> 0: 8-bit, 1: 16-bit

/* SPI status Register SpI_SR*/
#define SPI_SR_RXNE (0x1U << 0)  // Receive buffer not empty -> 0: RX buffer empty, 1: RX buffer not empty
#define SPI_SR_TXE  (0x1U << 1)  // Transmit buffer empty -> 0: TX buffer not empty, 1: TX buffer empty
#define SPI_SR_BSY  (0x1U << 7)  // Busy flag -> 0: SPI not busy, 1: SPI busy

/* SPI data register SPI_DR*/
#define SPI_DR_MASK (0xFFFFU) // Data register mask for 16-bit data
#define SPI_DR_DATA_Pos (0U) // Data register position for 16-bit data
#define SPI_DR_DATA_Msk (0xFFFFU << SPI_DR_DATA_Pos) // Data register mask for 16-bit data
#define SPI_DR_DATA SPI_DR_DATA_Msk // Data register for 16-bit data

/* Systick (system timer) Definitions */

#define SYSTICK_CSR_ENABLE (BIT(0U))     /* Enables the counter: 0-> counter disabled, 1 counter enabled.*/
#define SYSTICK_CSR_CLKSOURCE (BIT(2U))  /* Indicates the clock source: 0 external and 1 processor clock */
#define SYSTICK_CSR_COUNTFLAG (BIT(16U)) /* Returns 1 if timer counted to 0 since last time this was read.*/
#define SYSTICK_CSR_TICKINT (BIT(1U))    /* Enables SysTick exception request*/

/* Reload and Value Register definitions */
#define SYSTICK_RVR_RELOAD_Msk (0XFFFFFFUL)
#define SYSTICK_RVR_RELOAD (SYSTICK_RVR_RELOAD_Msk) // Value to load into the CVR register when the counter is enabled and when it reaches 0

/* Current Value Register definitions */
#define SYSTICK_CVR_CURRENT (SYSTICK_RVR_RELOAD_Msk) /* Returns the current value of the systick counter CURRENT[23:0] */

/* SysTick Calibration Value Register*/
#define SYSTICK_CALIB_NOREF BIT(31U) /* indicates if the device provides a reference clock to the processor. 0 yes and 1 not*/
#define SYSTICK_CALIB_SKEW BIT(30U)
#define SYSTICK_CALIB_TENMS (SYSTICK_RVR_RELOAD_Msk)

/**
 * System Control Block (SCB)
 */

#define SCB_BASE (0xE000ED00UL)

#define SCB_CPUID MMIO32(SCB_BASE + 0x00U)
/* ICSR: Interrupt Control State Register */
#define SCB_ICSR MMIO32(SCB_BASE + 0x04U)
/* VTOR:  Vector Table Offset Register */
#define SCB_VTOR MMIO32(SCB_BASE + 0x08U)
/* AIRCR: Âpplication Interrupt and Reset Control Register */
#define SCB_AIRCR MMIO32(SCB_BASE + 0x0CU)
/* SCR: System Control Register */
#define SCB_SCR MMIO32(SCB_BASE + 0x10U)
/* CCR: Configuration Control Register */
#define SCB_CCR MMIO32(SCB_BASE + 0x14U)

// Write to SCB_AIRCR register
//  VECTKEY write
#define SCB_AIRCR_VECTKEY          (0x5FA << 16)
#define SCB_AIRCR_VECTKEYSTAT      (0xFFFF << 16)
#define SCB_AIRCR_ENDIANESS_LE     (1 << 15)    
/* System reset request */ 
#define SCB_AIRCR_SYSRESETREQ      (1 << 2)     
/* Local system reset */
#define SCB_AIRCR_VECTRESET        (1 << 0) 

/* NVIC */
#define NVIC_ADDR_OFFSET(X) ((0X100) + (0X04) * (x))

#define NVIC_BASE (0xE000E100UL)
/* Flash key register */
#define FLASH_KEYR_KEY1 ((uint32_t)0x45670123)
#define FLASH_KEYR_KEY2 ((uint32_t)0xCDEF89AB)
/* Flash option key register */
#define FLASH_OPTKEYR_OPTKEY1 ((uint32_t)0x08192A3B)
#define FLASH_OPTKEYR_OPTKEY2 ((uint32_t)0x4C5D6E7F)
/* Flash status register */
#define FLASH_SR_BSY (1U << 16)     // Status -- Flash is busy operation ongoing
#define FLASH_SR_OPTVERR (1U << 15) // Error --  option byte validity error
#define FLASH_SR_RDERR (1U << 14)   // Error -- Read Protection error
#define FLASH_SR_FASTERR (1U << 9)  // Error -- Fast programming error
#define FLASH_SR_MISERR (1U << 8)   // Error -- Fast programming data miss
#define FLASH_SR_PGSERR (1U << 7)   // Error -- Programming sequence error
#define FLASH_SR_SIZERR (1U << 6)   // Error -- Size error
#define FLASH_SR_PGAERR (1U << 5)   // Error -- Pogramming alignment error
#define FLASH_SR_WRPERR (1U << 4)   // Eroor -- Write protection error
#define FLASH_SR_PROGERR (1U << 3)  // Error -- Write protection error
#define FLASH_SR_OPERR (1U << 1)    // Error - Operation erorr
#define FLASH_SR_EOP (1U << 0)      // Status -- End of operation

/* Flash control register */
#define FLASH_CR_LOCK (1U << 31)
#define FLASH_CR_OPTLOCK (1U << 30)
#define FLASH_CR_STRT (1U << 16)
#define FLASH_CR_MER2 (1U << 15) // Bank 2 mass erase
#define FLASH_CR_BKER (1U << 11) // Page number (bank selection)
#define FLASH_CR_PNB_Pos (3U)
#define FLASH_CR_PNB (0xFFU << FLASH_CR_PNB_Pos)
#define FLASH_CR_MER1 (1U << 2) // Bank 1 mass erase
#define FLASH_CR_PER (1U << 1)  // Page erase
#define FLASH_CR_PG (1U << 0)   // Programming



