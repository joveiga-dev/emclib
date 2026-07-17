#########################################################################
#
# source files
#
##########################################################################

LIB_SRCS := \
	$(ROOT)/src/logging/emc_log.c \
	$(ROOT)/src/emc_button.c \
	$(ROOT)/src/emc_clock.c \
	$(ROOT)/src/emc_gpio.c \
	$(ROOT)/src/emc_led.c \
	$(ROOT)/src/emc_periph.c \
	$(ROOT)/src/emc_spi.c \
	$(ROOT)/src/emc_time.c \
	$(ROOT)/src/emc_timer.c \
	$(ROOT)/src/emc_uart.c \
	$(ROOT)/boards/$(BOARD)/board_led.c \
	$(ROOT)/mcu/$(MCU)/clock/stm32_clock.c \
	$(ROOT)/mcu/$(MCU)/clock/stm32_periph.c \
	$(ROOT)/mcu/$(MCU)/gpio/stm32_gpio.c \
	$(ROOT)/mcu/$(MCU)/time/stm32_time.c \
	$(ROOT)/mcu/$(MCU)/uart/stm32_usart.c \
	$(ROOT)/mcu/$(MCU)/spi/stm32_spi.c \
	$(ROOT)/mcu/$(MCU)/startup/stm32l4rg_boot.c \
	$(ROOT)/mcu/$(MCU)/startup/syscalls.c