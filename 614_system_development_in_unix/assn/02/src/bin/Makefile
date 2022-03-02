# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Makefile for src/bin
#

# set the C++ compiler if unset
CXX ?= $(shell which c++)

SUBDIRS := test_log test_log2 lots_of_logs invalid_logfile

.PHONY: it install depend clean $(SUBDIRS)

# target to propagate make through all the subdirectories
$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend: $(SUBDIRS)

# clean out temporary objects and files
clean: $(SUBDIRS)
	rm -f *.o *.a *.out depend_list
