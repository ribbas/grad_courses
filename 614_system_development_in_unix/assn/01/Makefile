# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Root Makefile for the project

CXX ?= $(which $CXX)

ROOT = $(CURDIR)
SRC = $(ROOT)/src
LIB = $(SRC)/lib
BIN = $(SRC)/bin
INC = $(ROOT)/include

SUBDIRS := src
EXE = 

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

it:
	# pass

install:
	# pass

depend: $(SUBDIRS)
	# pass
	@echo $(CURDIR)

clean: $(SUBDIRS)
	# clean out cache and temporary files
	@find . -name "depend_list" -delete
