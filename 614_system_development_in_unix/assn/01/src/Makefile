# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src

CXX ?= $(which $(CXX))

ROOT = $(CURDIR)
LIB = $(ROOT)/lib
BIN = $(ROOT)/bin
# LIB = lib
# BIN = $(SRC)/bin
# INC = $(ROOT)/include

SUBDIRS := lib bin
EXE = 

.PHONY: it install depend clean $(SUBDIRS)

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
	@find . -name "depend_list" -delete
	@find . -type f \( -name "*.o" -o -name "*.a" -o -name "*.out" \) -delete
