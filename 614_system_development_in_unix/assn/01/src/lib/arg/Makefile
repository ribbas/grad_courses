# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Main Makefile for the project

CXX ?= $(which $(CXX))

LIB := ../../../lib
INC := ../../../include

SRC := arg.cpp
LIB_NAME := libarg.a
OBJ = $(SRC:.cpp=.o)

.PHONY: it install depend clean

it:
	$(CXX) -g -I$(INC) -c $(SRC)
	ar cr $(LIB_NAME) $(OBJ)
	cp $(LIB_NAME) $(LIB)
	ranlib $(LIB)/$(LIB_NAME)

install:
	cp $(LIB_NAME) $(LIB)
	ranlib $(LIB)/$(LIB_NAME)

depend:
	$(CXX) -M -g -I$(INC) $(SRC) > depend_list

clean:
	# clean out temporary and library files and executable
	@find . -name "depend_list" -delete
	@find . -type f \( -name "*.o" -o -name "*.a" \) -delete
