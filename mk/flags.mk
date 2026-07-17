##########################################################################
#
# Flags for the build
#
###########################################################################
# Target board and MCU
BOARD ?= nucleo-476rg
MCU   ?= stm32l4rg

CPU ?= cortex-m4
FPU_FLAGS ?=

MCUFLAGS := -mcpu=$(CPU) -mthumb $(FPU_FLAGS)

INC_DIRS := $(ROOT)/include \
	$(ROOT)/boards/$(BOARD) \
	$(ROOT)/src/logging \
	$(ROOT)/mcu/$(MCU) \
	$(ROOT)/mcu/$(MCU)/clock \
	$(ROOT)/mcu/$(MCU)/gpio \
	$(ROOT)/mcu/$(MCU)/time \
	$(ROOT)/mcu/$(MCU)/uart \
	$(ROOT)/mcu/$(MCU)/spi

CFLAGS := $(MCUFLAGS)
CFLAGS += \
	-std=c11 \
	-Wall \
	-Wextra \
	-O0 \
	-g3 \
	-ffreestanding \
	-ffunction-sections \
	-fdata-sections \
	-MMD \
	-MP

CFLAGS += $(addprefix -I,$(INC_DIRS))

LDFLAGS := $(MCUFLAGS)
LDFLAGS += \
	-T$(ROOT)/mcu/$(MCU)/startup/linker.ld \
	-specs=nano.specs \
	-nostartfiles \
	-Wl,--gc-sections \
	-Wl,--print-memory-usage \
	-Wl,-Map=$(BUILD_DIR)/$(TARGET).map
