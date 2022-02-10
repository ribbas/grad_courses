# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Main Makefile for the project

CXX ?= $(which $CXX)

.PHONY: it install depend clean

it:
	# pass

install:
	# pass

depend:
	# pass
	@echo > depend_list
	@$(CXX) -M -I ../../../include -g conv_to_cent.cpp >> depend_list


clean:
	# clean out cache and temporary files
	rm *.o
