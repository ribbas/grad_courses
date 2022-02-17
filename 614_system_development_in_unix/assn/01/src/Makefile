# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for the project src

CXX ?= $(shell which c++)

SUBDIRS := lib bin

.PHONY: it install depend clean $(SUBDIRS)

$(SUBDIRS):
	@echo "<<< $@ >>>"
	@cd $@ && $(MAKE) --no-print-directory $(MAKECMDGOALS)

# pass
it install depend: $(SUBDIRS)

# clean out temporary objects and files
clean: $(SUBDIRS)
	rm -f *.o *.a *.out
	rm -f depend_list
