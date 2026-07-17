###########################################################################
# Example/application build rules
###########################################################################

# Expect the example Makefile to set `TARGET` and `APP_SRCS` and `ROOT`.

APP_OBJS := $(addprefix $(BUILD_DIR)/,$(patsubst %.c,%.o,$(APP_SRCS)))

STM32_PROG ?= STM32_Programmer_CLI.exe
STM32_PROG_PORT ?= SWD
FLASH_ADDR ?= 0x08000000
FLASH_EXTRA ?=

$(BUILD_DIR):
	@$(MKDIR) $(BUILD_DIR)

$(BUILD_DIR)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


$(BUILD_DIR)/$(TARGET).elf: $(APP_OBJS) $(LIB_BUILD)/$(LIB_NAME)
	@$(MKDIR) $(dir $@)
	$(CC) $(MCUFLAGS) $(LDFLAGS) -o $@ $(APP_OBJS) -Wl,--whole-archive $(LIB_BUILD)/$(LIB_NAME) -Wl,--no-whole-archive
	$(OBJCOPY) -O binary $@ $(BUILD_DIR)/$(TARGET).bin
	$(OBJCOPY) -O ihex $@ $(BUILD_DIR)/$(TARGET).hex
	$(SIZE) $@

.PHONY: elf bin hex size flash

elf: $(BUILD_DIR)/$(TARGET).elf

bin: $(BUILD_DIR)/$(TARGET).bin

hex: $(BUILD_DIR)/$(TARGET).hex

size: elf

flash: elf
	@$(MAKE) flash-stm32prog

.PHONY: flash-stm32prog

flash-stm32prog: elf
	@echo "Flashing $(TARGET) to device using $(STM32_PROG) (port=$(STM32_PROG_PORT))"
	@$(STM32_PROG) -c port=$(STM32_PROG_PORT) -w $(BUILD_DIR)/$(TARGET).bin \
	$(FLASH_ADDR) -v -rst


.PHONY: example-clean
example-clean:
	@echo "Cleaning $(BUILD_DIR)"; $(RM) $(BUILD_DIR)
