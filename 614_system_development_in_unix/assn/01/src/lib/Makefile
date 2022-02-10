# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Main Makefile for the project

CXX ?= $(which $CXX)

ROOT = $(CURDIR)
SRC = $(ROOT)/src
LIB = $(SRC)/lib
BIN = $(SRC)/bin
INC = $(ROOT)/include
SUBDIRS := arg temp_conv
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

clean:
	# clean out cache and temporary files
	@echo $(CURDIR)
