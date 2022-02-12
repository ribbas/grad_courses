# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Root Makefile for the project

CXX ?= $(which $(CXX))

ROOT = $(CURDIR)
SRC = $(ROOT)/src
BIN = $(ROOT)/bin

SUBDIRS := $(SRC)

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
	@find $(BIN) -name "*" -delete
