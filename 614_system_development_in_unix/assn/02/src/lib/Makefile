# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Makefile for src/lib

# set the C++ compiler if unset
CXX ?= $(shell which c++)

SUBDIRS := log

.PHONY: default it install depend clean $(SUBDIRS)
default: it

# target to propagate make through all the subdirectories
$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend clean: $(SUBDIRS)
