###########################################################################
# Project-wide variables
###########################################################################

# Repository root. Examples set `ROOT := ../..` before including the top-level
# Makefile; if not provided, default to current directory.
ROOT ?= .

# Base path used by library build rules. Keep it separate so library.mk can
# refer to `$(ROOT_BUILD)` if needed.
ROOT_BUILD ?= $(ROOT)

# Per-target build directory. Examples should provide `TARGET`, so this will
# default to `build/<target>` under the repository root.
BUILD_DIR ?= $(ROOT_BUILD)/build/$(TARGET)

.PHONY: show-vars
show-vars:
	@echo ROOT = $(ROOT)
	@echo ROOT_BUILD = $(ROOT_BUILD)
	@echo BUILD_DIR = $(BUILD_DIR)
