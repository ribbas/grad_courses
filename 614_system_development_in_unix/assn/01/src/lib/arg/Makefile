# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Main Makefile for the project

CXX ?= $(which $(CXX))
.PHONY: it install depend clean

it:
	$(CXX) -g -I../../../include -c getarg.cpp
	ar cr libgetarg.a getarg.o
	cp libgetarg.a ../../../lib
	ranlib ../../../lib/libgetarg.a

install:
	cp libgetarg.a ../../../lib
	ranlib ../../../lib/libgetarg.a

depend:
	$(CXX) -M -g -I../../../include getarg.cpp > depend_list

clean:
	# clean out temporary and library files and executable
	@find . -name "depend_list" -delete
	@find . -type f \( -name "*.o" -o -name "*.a" \) -delete
