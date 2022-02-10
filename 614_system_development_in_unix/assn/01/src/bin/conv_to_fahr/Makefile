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
	@$(CXX) -M -I ../../../include -g conv_to_fahr.cpp >> depend_list

clean:
	# clean out cache and temporary files
	rm *.o
