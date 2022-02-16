# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src

CXX ?= $(shell which c++)

ROOT = $(CURDIR)
LIB = $(ROOT)/lib
BIN = $(ROOT)/bin
SUBDIRS := lib bin

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	@echo "<<< $@ >>>"
	@$(MAKE) --no-print-directory -C $@ $(MAKECMDGOALS)

# pass
it install depend: $(SUBDIRS)

# clean out temporary objects and files
clean: $(SUBDIRS)
	@rm -f *.o *.a *.out
	@rm -f depend_list
