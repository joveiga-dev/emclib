##########################################################################
# emclib build system
##########################################################################

#BOARD  ?= nucleo-476rg
#MCU    ?= stm32l4rg

ROOT ?= .

# Ensure `make` builds library+examples by default even when included from examples
.DEFAULT_GOAL := all

include $(ROOT)/mk/project.mk
include $(ROOT)/mk/toolchain.mk
include $(ROOT)/mk/flags.mk
include $(ROOT)/mk/sources.mk
include $(ROOT)/mk/library.mk
include $(ROOT)/mk/rules.mk
include $(ROOT)/mk/targets.mk

# load the example build rules to build the application.
ifneq ($(strip $(TARGET)),)
	include $(ROOT)/mk/example.mk
endif

ifneq ($(strip $(TARGET)),)
all: $(BUILD_DIR)/$(TARGET).elf
.PHONY: all
endif