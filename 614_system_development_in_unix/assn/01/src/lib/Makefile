# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Makefile for src/lib

CXX ?= $(shell which c++)
SUBDIRS := arg temp_conv

.PHONY: it install depend clean $(SUBDIRS)

# target to propagate make through all the subdirectories
$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend clean: $(SUBDIRS)
