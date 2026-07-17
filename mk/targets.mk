###########################################################################
# Top-level targets
###########################################################################

EXAMPLE_DIRS := $(wildcard examples/*/)
EXAMPLES := $(notdir $(patsubst %/,%,$(EXAMPLE_DIRS)))


.PHONY: all examples clean distclean size

# Default: build library and all examples
all: library examples

examples:
	@for d in $(EXAMPLE_DIRS); do \
		if [ -f $$d/Makefile ]; then \
			echo "Building example: $$d"; \
			$(MAKE) -C $$d || exit 1; \
		fi; \
	done

clean:
	@$(MAKE) library-clean || true
	@for d in $(EXAMPLE_DIRS); do \
		if [ -f $$d/Makefile ]; then \
			echo "Cleaning example: $$d"; \
			$(MAKE) -C $$d example-clean || true; \
		fi; \
	done

distclean: clean
	@echo "Removing top-level build folder: $(ROOT_BUILD)/build"; rm -rf $(ROOT_BUILD)/build

size:
	@for d in $(EXAMPLE_DIRS); do \
		if [ -f $$d/Makefile ]; then \
			$(MAKE) -C $$d size || true; \
		fi; \
	done
