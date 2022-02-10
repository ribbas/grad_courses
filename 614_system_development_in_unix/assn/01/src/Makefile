# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src

CXX ?= $(which $CXX)

ROOT = $(CURDIR)
SRC = $(ROOT)/src
LIB = lib
BIN = $(SRC)/bin
INC = $(ROOT)/include

SUBDIRS := lib bin
EXE = 

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)

it:
	# pass

install:
	# pass

depend: $(SUBDIRS)
	@echo $(CURDIR)
	# pass

clean:
	# clean out cache and temporary files
	@echo $(CURDIR)
