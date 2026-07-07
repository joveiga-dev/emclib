################################################################################
# Target
################################################################################

TARGET := button_polling

################################################################################
# Toolchain
################################################################################

CC      := arm-none-eabi-gcc
OBJCOPY := arm-none-eabi-objcopy
SIZE    := arm-none-eabi-size

################################################################################
# MCU
################################################################################

MCUFLAGS := \
	-mcpu=cortex-m4 \
	-mthumb

################################################################################
# Build
################################################################################

BUILD_DIR := build

################################################################################
# Includes
################################################################################

INCLUDES := \
	-Iinclude \
	-Icore/logging \
	-Imcu/stm32l4rg \
	-Imcu/stm32l4rg/gpio \
	-Imcu/stm32l4rg/clock \
	-Imcu/stm32l4rg/time \
	-Imcu/stm32l4rg/uart \
	-Imcu/stm32l4rg/spi \

################################################################################
# Compiler
################################################################################

CFLAGS := \
	$(MCUFLAGS) \
	-std=c11 \
	-Wall \
	-Wextra \
	-Wpedantic \
	-O0 \
	-g3 \
	-ffreestanding \
	-fdata-sections \
	-ffunction-sections \
	$(INCLUDES)

################################################################################
# Linker
################################################################################

LDFLAGS := \
	$(MCUFLAGS) \
	-Tmcu/stm32l4rg/startup/linker.ld \
	-Wl,-Map=$(BUILD_DIR)/$(TARGET).map \
	-Wl,--gc-sections \
	-Wl,--print-memory-usage \
	-specs=nano.specs \
	-nostartfiles \



################################################################################
# Sources
################################################################################

SRCS := \
	examples/button/button_polling/main.c \
	core/emc_gpio.c \
	core/emc_periph.c \
	core/emc_clock.c \
	core/emc_time.c \
	core/emc_timer.c \
	core/emc_uart.c \
	core/emc_spi.c \
	core/emc_button.c \
	core/logging/emc_log.c \
	mcu/stm32l4rg/gpio/stm32_gpio.c \
	mcu/stm32l4rg/clock/stm32_clock.c \
	mcu/stm32l4rg/clock/stm32_periph.c \
	mcu/stm32l4rg/time/stm32_time.c \
	mcu/stm32l4rg/uart/stm32_usart.c \
	mcu/stm32l4rg/spi/stm32_spi.c \
	mcu/stm32l4rg/startup/syscalls.c \
	mcu/stm32l4rg/startup/stm32l4rg_boot.c \

################################################################################
# Objects
################################################################################

OBJS := $(patsubst %.c,$(BUILD_DIR)/%.o,$(SRCS))

################################################################################
# Build
################################################################################

all: $(BUILD_DIR)/$(TARGET).elf

$(BUILD_DIR)/$(TARGET).elf: $(OBJS)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(OBJS) $(LDFLAGS) -o $@
	$(SIZE) $@

$(BUILD_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

################################################################################
# Binary
################################################################################

bin: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O binary $< $(BUILD_DIR)/$(TARGET).bin

################################################################################
# Hex
################################################################################

hex: $(BUILD_DIR)/$(TARGET).elf
	$(OBJCOPY) -O ihex $< $(BUILD_DIR)/$(TARGET).hex

################################################################################
# Flash
################################################################################

flash: bin
	STM32_Programmer_CLI.exe \
	-c port=SWD mode=UR \
	-w $(BUILD_DIR)/$(TARGET).bin 0x08000000 \
	-v -rst

################################################################################
# Clean
################################################################################

clean:
	rm -rf $(BUILD_DIR)

.PHONY: all clean flash bin hex