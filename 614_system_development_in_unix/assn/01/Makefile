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
SUBDIRS := $(SRC) $(BIN) $(LIB)
EXE = 

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

it:
	# pass

install:
	# pass

depend:
	# pass

clean: $(SUBDIRS)
	# clean out cache and temporary files
	@echo $(CURDIR)
