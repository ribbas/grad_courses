# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project bin


CXX ?= $(which $CXX)

ROOT = $(CURDIR)
SRC = $(ROOT)/src
LIB = $(SRC)/lib
BIN = $(SRC)/bin
INC = $(ROOT)/include
SUBDIRS := conv_to_fahr conv_to_cent
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
