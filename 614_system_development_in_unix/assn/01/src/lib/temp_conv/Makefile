# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for libtemp_conv

CXX ?= $(which $(CXX))
.PHONY: it install depend clean

it:
	$(CXX) -g -I../../../include -c cent_convert.cpp fahr_convert.cpp
	ar cr libtemp_conv.a cent_convert.o fahr_convert.o
	cp libtemp_conv.a ../../../lib
	ranlib ../../../lib/libtemp_conv.a

install:
	cp libtemp_conv.a ../../../lib
	ranlib ../../../lib/libtemp_conv.a

depend:
	$(CXX) -M -g -I../../../include cent_convert.cpp fahr_convert.cpp > depend_list

clean:
	# clean out temporary and library files and executable
	@find . -name "depend_list" -delete
	@find . -type f \( -name "*.o" -o -name "*.a" \) -delete
