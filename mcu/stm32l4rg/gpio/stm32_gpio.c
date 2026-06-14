#ifndef STM32_GPIO_H
#define STM32_GPIO_H

//#include "gpio_ops.h"
#include "stm32_gpio_regs.h"
#include "stm32_rcc.h"
#include <stddef.h>

static GPIO_RegDef_t *_stm32_gpio_port_mapper(emc_gpio_port_t port) {
    switch (port) {
        case EMC_GPIO_PORTA:
            return GPIOA;
        case EMC_GPIO_PORTB:
            return GPIOB;
        case EMC_GPIO_PORTC:
            return GPIOC;
        case EMC_GPIO_PORTD:
            return GPIOD;
        case EMC_GPIO_PORTE:
            return GPIOE;
        case EMC_GPIO_PORTF:
            return GPIOF;
        case EMC_GPIO_PORTG:
            return GPIOG;
        case EMC_GPIO_PORTH:
            return GPIOH;
        default:
            return NULL;
    }
}

static void _stm32_gpio_set_mode(emc_gpio_port_t port, uint8_t pin, emc_gpio_mode_t mode) 
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(port);
    if (p == NULL) {
        return;
    }

    uint32_t mode_bits = pin * 2U;
    uint32_t tmp_reg = p->MODER;
    tmp_reg &= ~(0x3UL << mode_bits); 
    tmp_reg |= ((uint32_t)mode << mode_bits); 
    p->MODER = tmp_reg;
}

static void _stm32_gpio_set_otype(emc_gpio_port_t port, uint8_t pin, emc_gpio_otype_t otype_od) 
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(port);
    if (p == NULL) {
        return;
    }

    if (otype_od == EMC_GPIO_OTYPE_OD) {
        p->OTYPER |= (1U << pin);
    } else {
        p->OTYPER &= ~(1U << pin);
    }
}

static void _stm32_gpio_set_ospeed(emc_gpio_port_t port, uint8_t pin, emc_gpio_ospeed_t ospeed) 
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(port);
    if (p == NULL) {
        return;
    }

    uint32_t tmp_reg = p->OSPEEDR;
    tmp_reg &= ~(0x3UL << (2U * pin)); 
    tmp_reg |= ((uint32_t)ospeed << (2U * pin)); 
    p->OSPEEDR = tmp_reg;
}

static void _stm32_gpio_set_pupd(emc_gpio_port_t port, uint8_t pin, emc_gpio_pupd_t pupd) 
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(port);
    if (p == NULL) {
        return;
    }


    uint32_t tmp_reg = p->PUPDR;
    tmp_reg &= ~(0x3UL << (2U *pin)); 
    tmp_reg |= ((uint32_t)pupd << (2U *pin)); 
    p->PUPDR = tmp_reg;
}

static void _stm32_gpio_set_af(emc_gpio_port_t port, uint8_t pin, uint8_t af) 
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(port);
    if (p == NULL) {
        return;
    }

    uint8_t afr_index = pin / 8U;
    uint8_t shift = (pin % 8U) * 4U;

    p->AFR[afr_index] &= ~(0xFUL << shift); 
    p->AFR[afr_index] |= ((uint32_t)(af & 0xFUL) << shift); 
}

int stm32_gpio_init(emc_gpio_t *gpio, const emc_gpio_config_t *cfg)
{
    if (gpio == NULL || cfg == NULL || gpio->pin >= 16U) {
        return -1;
    }

    GPIO_RegDef_t *regs = _stm32_gpio_port_mapper(gpio->port);
    if (regs == NULL) {
        return -1;
    }

    stm32_rcc_enable_gpio_clock(gpio->port);

    _stm32_gpio_set_mode(gpio->port, gpio->pin, cfg->mode);
    _stm32_gpio_set_otype(gpio->port, gpio->pin, cfg->otype);
    _stm32_gpio_set_ospeed(gpio->port, gpio->pin, cfg->ospeed);
    _stm32_gpio_set_pupd(gpio->port, gpio->pin, cfg->pupd);

    if (cfg->mode == EMC_GPIO_MODE_AF) {
        _stm32_gpio_set_af(gpio->port, gpio->pin, cfg->alternate_function);
    }

    return 0; // Success
}

void stm32_gpio_deinit(emc_gpio_t *gpio)
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(gpio->port);
    if (p == NULL) {
        return; // Not initialized or invalid port
    }

    _stm32_gpio_set_mode(gpio->port, gpio->pin, EMC_GPIO_MODE_AN);
    _stm32_gpio_set_otype(gpio->port, gpio->pin, EMC_GPIO_OTYPE_PP);
    _stm32_gpio_set_ospeed(gpio->port, gpio->pin, EMC_GPIO_OSPEED_LOW);
    _stm32_gpio_set_pupd(gpio->port, gpio->pin, EMC_GPIO_PUPD_NONE);
    _stm32_gpio_set_af(gpio->port, gpio->pin, 0);

}

void stm32_gpio_write(const emc_gpio_t *gpio, bool state)
{
    GPIO_RegDef_t *regs = _stm32_gpio_port_mapper(gpio->port);
    if (regs == NULL) {
        return; // Not initialized or invalid port
    }

    if (state) {
        regs->BSRR = (1U << gpio->pin);
    } else {
        regs->BSRR = (1U << (gpio->pin + 16U));
    }
}

void stm32_gpio_set(const emc_gpio_t *gpio)
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(gpio->port);
    if (p == NULL) {
        return; // Not initialized or invalid port
    }

    p->BSRR = (1U << gpio->pin);
}

void stm32_gpio_clear(const emc_gpio_t *gpio)
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(gpio->port);
    if (p == NULL) {
        return; // Not initialized or invalid port
    }

    p->BSRR = (1U << (gpio->pin + 16U));
}

bool stm32_gpio_read(const emc_gpio_t *gpio)
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(gpio->port);
    if (p == NULL) {
        return false;
    }

    return (p->IDR & (1U << gpio->pin)) != 0; 
}

void stm32_gpio_toggle(const emc_gpio_t *gpio)
{
    GPIO_RegDef_t *p = _stm32_gpio_port_mapper(gpio->port);
    if (p == NULL) {
        return; // Not initialized or invalid port
    }

    if (stm32_gpio_read(gpio)) {
        stm32_gpio_clear(gpio);
    } else {
        stm32_gpio_set(gpio);
    }

}


#endif // STM32_GPIO_H