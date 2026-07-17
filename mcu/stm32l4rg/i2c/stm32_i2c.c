#include "stm32_i2c.h"
#include "emc_gpio.h"
#include "emc_periph.h"

typedef struct {
    I2C_RegDef_t *instance;          /**< I2C peripheral base address */
    emc_gpio_t scl_pin;              /**< SCL pin */
    emc_gpio_t sda_pin;              /**< SDA pin */
    uint8_t af;                      /**< Alternate function */
    emc_periph_t periph;            /**< Peripheral */
} stm32_i2c_hw_t;


static const stm32_i2c_hw_t i2c_desc[] = {
    [EMC_I2C1] = {
        .instance = I2C1,
        // SCL pin: PB6
        .scl_pin.port = EMC_GPIO_PORTB,
        .scl_pin.pin = 6,
        // SDA pin: PB7
        .sda_pin.port = EMC_GPIO_PORTB,
        .sda_pin.pin = 7,
        .af = 4,
        .periph = EMC_PERIPH_I2C1
    },

    [EMC_I2C2] = {
        .instance = I2C2,
        // SCL pin: PB10
        .scl_pin.port = EMC_GPIO_PORTB,
        .scl_pin.pin = 10,
        // SDA pin: PB11
        .sda_pin.port = EMC_GPIO_PORTB,
        .sda_pin.pin = 11,
        .af = 4,
        .periph = EMC_PERIPH_I2C2
    },

    [EMC_I2C3] = {
        .instance = I2C3,
        // SCL pin: PA8
        .scl_pin.port = EMC_GPIO_PORTA,
        .scl_pin.pin = 8,
        // SDA pin: PC9
        .sda_pin.port = EMC_GPIO_PORTC,
        .sda_pin.pin = 9,
        .af = 4,
        .periph = EMC_PERIPH_I2C3
    }
};

static const stm32_i2c_hw_t *stm32_get_i2c_desc(emc_i2c_id_t i2c_id)
{
    if (i2c_id >= EMC_I2C_ALL) {
        return NULL;
    }
    return &i2c_desc[i2c_id];

}

static void stm32_i2c_gpio_init(emc_i2c_id_t i2c_id)
{
    emc_gpio_config_t cfg;

    const stm32_i2c_hw_t *desc = stm32_get_i2c_desc(i2c_id);
    cfg.mode = EMC_GPIO_MODE_AF;
    cfg.otype = EMC_GPIO_OTYPE_OD;
    cfg.ospeed = EMC_GPIO_OSPEED_HIGH;
    cfg.pupd = EMC_GPIO_PUPD_NONE;
    cfg.alternate_function = desc->af;

    emc_gpio_init((emc_gpio_t *)&desc->scl_pin, &cfg);
    emc_gpio_init((emc_gpio_t *)&desc->sda_pin, &cfg);
}


emc_result_t emc_i2c_init(emc_i2c_t *i2c)
{
    if(i2c == NULL || i2c->id >= EMC_I2C_ALL) {
        return EMC_STATUS_ERR;
    }

    const stm32_i2c_hw_t *desc = stm32_get_i2c_desc(i2c->id);
    I2C_RegDef_t *i2c_instance = desc->instance;

    if(i2c_instance == NULL) {
        return EMC_STATUS_ERR;
    }

    emc_periph_enable(desc->periph);



    stm32_i2c_gpio_init(i2c->id);
}
