# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src/lib

CXX = /usr/bin/g++

ROOT = $(CURDIR)
# SRC = $(ROOT)/src
# LIB = $(SRC)/lib
# BIN = $(SRC)/bin
# INC = $(ROOT)/include
SUBDIRS := arg temp_conv
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

# pass
clean: $(SUBDIRS)
