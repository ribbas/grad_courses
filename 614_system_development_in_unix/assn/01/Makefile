# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Root Makefile for the project

CXX ?= $(shell which c++)
SUBDIRS := src

.PHONY: it install depend clean $(SUBDIRS)
default: it

$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend: $(SUBDIRS)

# clean out library files and executables
clean: $(SUBDIRS)
	rm -f lib/*
	rm -f bin/*
