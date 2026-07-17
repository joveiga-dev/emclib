###################################################################
#
# Build rules
#
######################################################################

$(LIB_BUILD):
	@$(MKDIR) $(LIB_BUILD)

$(LIB_BUILD)/%.o: %.c
	@$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(LIB_BUILD)/$(LIB_NAME): $(LIB_OBJS)
	$(AR) rcs $@ $^

library: $(LIB_BUILD)/$(LIB_NAME)

# Clean library build artifacts
.PHONY: library-clean
library-clean:
	@echo "Removing library build: $(LIB_BUILD)"; $(RM) $(LIB_BUILD)

.PHONY: library