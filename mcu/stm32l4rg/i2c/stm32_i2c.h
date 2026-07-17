#ifndef STM32_I2C_H
#define STM32_I2C_H

#include "emc_i2c.h"
#include "stm32l4xx.h"

typedef struct {
    volatile uint32_t I2C_CR1;
    volatile uint32_t I2C_CR2;
    volatile uint32_t I2C_OAR1;
    volatile uint32_t I2C_OAR2;
    volatile uint32_t I2C_TIMINGR;
    volatile uint32_t I2C_TIMEOUTR;
    volatile uint32_t I2C_ISR;
    volatile uint32_t I2C_ICR;
    volatile uint32_t I2C_PECR;
    volatile uint32_t I2C_RXDR;
    volatile uint32_t I2C_TXDR;
} I2C_RegDef_t;

#define I2C1 ((I2C_RegDef_t *) I2C1_BASE)
#define I2C2 ((I2C_RegDef_t *) I2C2_BASE)
#define I2C3 ((I2C_RegDef_t *) I2C3_BASE)

emc_result_t stm32_i2c_init(emc_i2c_t *i2c);
emc_result_t stm32_i2c_write(emc_i2c_t *i2c, uint8_t dev_addr, const uint8_t *data, uint32_t length);
emc_result_t stm32_i2c_read(emc_i2c_t *i2c, uint8_t dev_addr, uint8_t *data, uint32_t length);
emc_result_t stm32_i2c_transfer(emc_i2c_t *i2c, uint8_t dev_addr, const uint8_t *tx_data,
                              uint32_t tx_length, uint8_t *rx_data, uint32_t rx_length);




#endif // STM32_I2C_H