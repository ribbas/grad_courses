# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Root Makefile for the project

CXX ?= $(shell which c++)

ROOT = $(CURDIR)
SRC = $(ROOT)/src
BIN = $(ROOT)/bin
LIB = $(ROOT)/lib
SUBDIRS := src

.PHONY: it install depend clean $(SUBDIRS)
default: it

$(SUBDIRS):
	@echo "<<< $@ >>>"
	@$(MAKE) --no-print-directory -C $@ $(MAKECMDGOALS)

# pass
it install depend: $(SUBDIRS)

# clean out library files and executables
clean: $(SUBDIRS)
	@rm -f $(LIB)/*
	@rm -f $(BIN)/*
