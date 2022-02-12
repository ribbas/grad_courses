# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Main Makefile for the project

CXX ?= $(which $(CXX))
.PHONY: it install depend clean

it:
	$(CXX) -I../../../include -g -c conv_to_fahr.cpp
	$(CXX) -I../../../include -g conv_to_fahr.o -L../../../lib -lgetarg -ltemp_conv -o conv_to_fahr
	chmod 755 conv_to_fahr

install:
	$(CXX) -I../../../include -g conv_to_fahr.o -L../../../lib -lgetarg -ltemp_conv
	chmod 755 conv_to_fahr
	cp conv_to_fahr ../../../bin

depend:
	@echo > depend_list
	@$(CXX) -M -I../../../include -g conv_to_fahr.cpp >> depend_list

clean:
	# clean out temporary and library files and executable
	@find . -name "depend_list" -delete
	@find . -type f \( -name "*.o" -o -name "*.a" \) -delete
