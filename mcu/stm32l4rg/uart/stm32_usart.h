#ifndef STM32_USART_H
#define STM32_USART_H

#include "emc_uart.h"
#include "stm32l4xx.h"

typedef struct {
    volatile uint32_t USART_CR1; 
    volatile uint32_t USART_CR2;
    volatile uint32_t USART_CR3;  
    volatile uint32_t USART_BRR;  
    volatile uint32_t USART_GTPR; 
    volatile uint32_t USART_RTOR;
    volatile uint32_t USART_RQR;  
    volatile uint32_t USART_ISR;  
    volatile uint32_t USART_ICR;  
    volatile uint32_t USART_RDR;  
    volatile uint32_t USART_TDR;  
} USART_RegDef_t;


#define USART1                  ((USART_RegDef_t *)USART1_BASE)
#define USART2                  ((USART_RegDef_t *)USART2_BASE)
#define USART3                  ((USART_RegDef_t *)USART3_BASE)
#define UART4                   ((USART_RegDef_t *)UART4_BASE)
#define UART5                   ((USART_RegDef_t *)UART5_BASE)



emc_result_t stm32_uart_init(emc_uart_t *uart);
emc_result_t stm32_uart_deinit(emc_uart_t *uart);

emc_result_t stm32_uart_transmit_byte(emc_uart_t *uart, uint8_t byte);
emc_result_t stm32_uart_receive_byte(emc_uart_t *uart, uint8_t *byte);
emc_result_t stm32_uart_transmit(emc_uart_t *uart, const uint8_t *data, uint16_t size);
emc_result_t stm32_uart_receive(emc_uart_t *uart, uint8_t *data, uint16_t size);
emc_result_t stm32_uart_transmit_string(emc_uart_t *uart, const char *str);
emc_result_t stm32_uart_set_baudrate(emc_uart_t *uart, uint32_t baudrate);
uint32_t stm32_uart_get_baudrate(emc_uart_t *uart, uint32_t *baudrate);
emc_result_t stm32_uart_enable_irq(emc_uart_t *uart, uint16_t irq_flags);
emc_result_t stm32_uart_disable_irq(emc_uart_t *uart, uint16_t irq_flags);


#endif // STM32_USART_H