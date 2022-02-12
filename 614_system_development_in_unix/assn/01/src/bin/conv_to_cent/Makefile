# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for conv_to_cent

CXX ?= $(which $CXX)
.PHONY: it install depend clean

it:
	$(CXX) -I../../../include -g -c conv_to_cent.cpp
	$(CXX) -I../../../include -g conv_to_cent.o -L../../../lib -lgetarg -ltemp_conv -o conv_to_cent
	chmod 755 conv_to_cent

install:
	$(CXX) -I../../../include -g conv_to_cent.o -L../../../lib -lgetarg -ltemp_conv
	chmod 755 conv_to_cent
	cp conv_to_cent ../../../bin

depend:
	@echo > depend_list
	@$(CXX) -M -I../../../include -g conv_to_cent.cpp >> depend_list

clean:
	# clean out temporary and library files and executable
	@find . -name "depend_list" -delete
	@find . -type f \( -name "*.o" -o -name "*.a" \) -delete
