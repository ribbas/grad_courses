# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src/lib

CXX ?= $(shell which c++)

SUBDIRS := arg temp_conv

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend clean: $(SUBDIRS)
