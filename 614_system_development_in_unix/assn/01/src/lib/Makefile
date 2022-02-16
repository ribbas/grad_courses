# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src/lib

CXX ?= $(shell which c++)

ROOT = $(CURDIR)
SUBDIRS := arg temp_conv

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	@echo "<<< $@ >>>"
	@$(MAKE) --no-print-directory -C $@ $(MAKECMDGOALS)

# pass
it install depend clean: $(SUBDIRS)
