# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Root Makefile for the project

# set the C++ compiler if unset
CXX ?= $(shell which c++)

SUBDIRS := src

.PHONY: default it install depend clean $(SUBDIRS)
default: it

# target to propagate make through all the subdirectories
$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend: $(SUBDIRS)

# clean out library files and executables
clean: $(SUBDIRS)
	rm -f lib/* bin/* LOGnewlog LOGwarnlog
