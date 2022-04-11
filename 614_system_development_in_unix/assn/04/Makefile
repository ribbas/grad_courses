# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Root Makefile for the project
#

# set the C++ compiler if unset
CXX ?= $(shell which c++)

SUBDIRS := src

.PHONY: default it install depend clean
default: it

# propagate make through all the subdirectories
depend it install:
	@for i in $(SUBDIRS); do \
		echo "<< $$i >>"; \
		cd $$i; \
		$(MAKE) --no-print-directory $@; \
	done

clean:
	@rm -f lib/* bin/*
	@for i in $(SUBDIRS); do \
		echo "<< $$i >>"; \
		cd $$i; \
		$(MAKE) --no-print-directory $@; \
	done
	rm -f *.log
