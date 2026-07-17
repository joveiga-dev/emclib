###########################################################################
# Toolchain
#
# Defines the GNU ARM toolchain commands.
#
###########################################################################

TOOLCHAIN    ?= arm-none-eabi-

CC           := $(TOOLCHAIN)gcc
CXX          := $(TOOLCHAIN)g++
AS           := $(TOOLCHAIN)as
AR		     := $(TOOLCHAIN)ar
LD           := $(TOOLCHAIN)ld
OBJCOPY      := $(TOOLCHAIN)objcopy
OBJDUMP      := $(TOOLCHAIN)objdump
GDB          := $(TOOLCHAIN)gdb
SIZE         := $(TOOLCHAIN)size

RM		     := rm -rf

ifeq ($(OS),Windows_NT)
	RM := cmd /C rmdir /S /Q
	MKDIR := mkdir
else
	MKDIR := mkdir -p
	RM = rm -rf
endif




