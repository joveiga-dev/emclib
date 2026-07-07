/**
 * @file emc_uart.h
 *  UART communication module
 * @author JC
 */

#ifndef EMC_UART_H
#define EMC_UART_H

#include "emc_common.h"

typedef enum {
    EMC_UART1 = 0,
    EMC_USART2,
    EMC_UART3,
    EMC_UART4,

    EMC_UART_ALL
} emc_uart_id_t;

typedef enum {
    EMC_UART_MODE_TX = 0x01,   /*!< Transmit mode */
    EMC_UART_MODE_RX = 0x02,   /*!< Receive mode */
    EMC_UART_MODE_TX_RX = 0x03 /*!< Transmit and receive mode */
} emc_uart_mode_t;

typedef enum {
    EMC_UART_PARITY_NONE = 0x00, /*!< No parity */
    EMC_UART_PARITY_EVEN = 0x01, /*!< Even parity */
    EMC_UART_PARITY_ODD = 0x02   /*!< Odd parity */
} emc_uart_parity_t;

typedef enum {
    EMC_UART_WORD_LENGTH_8B = 0x00, /*!< 8 data bits */
    EMC_UART_WORD_LENGTH_9B = 0x01, /*!< 9 data bits */
    EMC_UART_WORD_LENGTH_7B = 0x02  /*!< 7 data bits */
} emc_uart_wordlen_t;

typedef enum {
    EMC_UART_STOPBITS_1 = 0x00,   /*!< 1 stop bit */
    EMC_UART_STOPBITS_0_5 = 0x01, /*!< 0.5 stop bits */
    EMC_UART_STOPBITS_2 = 0x02,   /*!< 2 stop bits */
    EMC_UART_STOPBITS_1_5 = 0x03  /*!< 1.5 stop bits */
} emc_uart_stopbits_t;

typedef enum {
    EMC_UART_HW_FLOW_CTRL_NONE = 0x00, /*!< No hardware flow control */
    EMC_UART_HW_FLOW_CTRL_RTS = 0x01,  /*!< RTS hardware flow control */
    EMC_UART_HW_FLOW_CTRL_CTS = 0x02,  /*!< CTS hardware flow control */
    EMC_UART_HW_FLOW_CTRL_RTS_CTS = 0x03 /*!< RTS and CTS hardware flow control */
} emc_uart_hwflowctrl_t;

typedef enum {
    EMC_UART_OVERSAMPLING_16 = 0x00, /*!< Oversampling by 16 */
    EMC_UART_OVERSAMPLING_8 = 0x01   /*!< Oversampling by 8 */
} emc_uart_oversampling_t;

typedef struct {
    emc_uart_mode_t mode;
    uint32_t baudrate;
    emc_uart_wordlen_t word_length;
    emc_uart_stopbits_t stop_bits;
    emc_uart_parity_t parity;
    emc_uart_hwflowctrl_t hw_flow_control;
    emc_uart_oversampling_t oversampling;
} emc_uart_config_t;

// Handle structure for UART instance
typedef struct {
    emc_uart_id_t uart_id;             /*< UART instance identifier */
    emc_uart_config_t config;          /*< UART configuration parameters */
} emc_uart_t;

/* API functions */
// Init and deinitialize UART peripheral
emc_result_t emc_uart_init(emc_uart_t *uart);
emc_result_t emc_uart_deinit(emc_uart_t *uart);

void emc_uart_dft_config(emc_uart_config_t *cfg);

// Transmit and receive data
emc_result_t emc_uart_transmit(emc_uart_t *uart, const uint8_t *data, uint16_t size);
emc_result_t emc_uart_receive(emc_uart_t *uart, uint8_t *data, uint16_t size);
emc_result_t emc_uart_transmit_byte(emc_uart_t *uart, uint8_t byte);
emc_result_t emc_uart_receive_byte(emc_uart_t *uart, uint8_t *byte);

emc_result_t emc_uart_transmit_string(emc_uart_t *uart, const char *str);

// IRQ configurationa and ISR
void emc_uart_irq_interrupt_config(uint8_t irq_number, uint8_t enable);
void emc_uart_irq_priority_config(uint8_t irq_number, uint32_t priority);
void emc_uart_irq_handler(emc_uart_t *uart);

void emc_uart_set_baudrate(emc_uart_t *uart, uint32_t baudrate);
//void emc_uart_evt_cbk(emc_uart_t *uart, uint8_t event);

#endif // EMC_UART_H