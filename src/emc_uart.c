#include "emc_uart.h"
#include "stm32_usart.h"

/**
 * @brief  Initialize UART configuration structure with default values
 * @param  cfg: Pointer to UART configuration structure to be initialized
 * Need to be moved to mcu specific implementation
 */
void emc_uart_dft_config(emc_uart_config_t *cfg)
{
    cfg->mode = EMC_UART_MODE_TX_RX;
    cfg->baudrate = 9600;
    cfg->word_length = EMC_UART_WORD_LENGTH_8B;
    cfg->stop_bits = EMC_UART_STOPBITS_1;
    cfg->parity = EMC_UART_PARITY_NONE;
    cfg->hw_flow_control = EMC_UART_HW_FLOW_CTRL_NONE;
    cfg->oversampling = EMC_UART_OVERSAMPLING_16;
}

emc_result_t emc_uart_init(emc_uart_t *uart)
{
    return stm32_uart_init(uart);
}

emc_result_t emc_uart_deinit(emc_uart_t *uart)
{
    return stm32_uart_deinit(uart);
}

emc_result_t emc_uart_transmit_byte(emc_uart_t *uart, uint8_t byte)
{
    return stm32_uart_transmit_byte(uart, byte);
}

emc_result_t emc_uart_transmit(emc_uart_t *uart, const uint8_t *data, uint16_t size)
{
    return stm32_uart_transmit(uart, data, size);
}

emc_result_t emc_uart_receive_byte(emc_uart_t *uart, uint8_t *byte)
{
    return stm32_uart_receive_byte(uart, byte);
}

emc_result_t emc_uart_receive(emc_uart_t *uart, uint8_t *data, uint16_t size)
{
    return stm32_uart_receive(uart, data, size);
}
