# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Makefile for src

# set the C++ compiler if unset
CXX ?= $(shell which c++)

SUBDIRS := lib bin

.PHONY: default it install depend clean $(SUBDIRS)
default: it

# target to propagate make through all the subdirectories
$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend: $(SUBDIRS)

# clean out temporary objects and files
clean: $(SUBDIRS)
	rm -f *.o *.a *.out depend_list
