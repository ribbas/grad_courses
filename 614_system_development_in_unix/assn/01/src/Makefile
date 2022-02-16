# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src

CXX = /usr/bin/g++

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

# pass
it: $(SUBDIRS)

# pass
install: $(SUBDIRS)

# pass
depend: $(SUBDIRS)

clean: $(SUBDIRS)
	# clean out temporary and library files and executable
	@rm -f *.o *.a *.out
	@rm -f depend_list
