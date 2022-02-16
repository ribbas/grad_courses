# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Root Makefile for the project

CXX = /usr/bin/g++

ROOT = $(CURDIR)
SRC = $(ROOT)/src
BIN = $(ROOT)/bin
LIB = $(ROOT)/lib

SUBDIRS := $(SRC)

.PHONY: it install depend clean $(SUBDIRS)
default: it

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

it: $(SUBDIRS)
	# pass

install: $(SUBDIRS)
	# pass

depend: $(SUBDIRS)
	# pass

clean: $(SUBDIRS)
	# clean out temporary and library files and executable
	@rm $(LIB)/*
	@rm $(BIN)/*
