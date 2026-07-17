#ifndef EMC_I2C_H
#define EMC_I2C_H

#include "emc_gpio.h"
#include "emc_common.h"

typedef enum {
    EMC_I2C1 = 0,
    EMC_I2C2,
    EMC_I2C3,

    EMC_I2C_ALL
} emc_i2c_id_t;

typedef enum {
    EMC_SPEED_SM100KHz,         /* Standard speed (100 kHz) */
    EMC_SPEED_FM400KHz,        /* Fast speed (400 kHz) */
    EMC_SPEED_FMP1MHz,        /* Fast Plus speed (1 MHz) */
    EMC_SPEED_UNKNOWN,        /* Fast Plus speed (2 MHz) */
} emc_i2c_speed_t;

typedef enum {
    EMC_I2C_MODE_MASTER = 0,            /* Master mode */
    EMC_I2C_MODE_SLAVE                  /* Slave mode */
} emc_i2c_mode_t;

typedef struct {
    uint32_t clock_speed;
    uint8_t addressing_mode;
    uint8_t no_stretch;
} emc_i2c_config_t;

typedef struct {
    emc_i2c_id_t id;
    emc_i2c_config_t config;
} emc_i2c_t;

void emc_i2c_send_start(uint32_t i2c_id);
void emc_i2c_send_stop(uint32_t i2c_id);


emc_result_t emc_i2c_init(emc_i2c_t *i2c);
emc_result_t emc_i2c_deinit(emc_i2c_t *i2c);

emc_result_t emc_i2c_write(emc_i2c_t *i2c, uint8_t slave_addr, const uint8_t *data, uint32_t nbytes_to_write);
emc_result_t emc_i2c_read(emc_i2c_t *i2c, uint8_t slave_addr, uint8_t *data, uint32_t nbytes_to_read);
emc_result_t emc_i2c_transfer(emc_i2c_t *i2c, uint8_t slave_addr, const uint8_t *tx_data,
                              uint32_t nbytes_to_write, uint8_t *rx_data, uint32_t nbytes_to_read);
#endif // EMC_I2C_H