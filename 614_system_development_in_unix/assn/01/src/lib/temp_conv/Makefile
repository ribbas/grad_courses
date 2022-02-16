# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for libtemp_conv

CXX = /usr/bin/g++

LIB := ../../../lib
INC := ../../../include

SRC := cent_convert.cpp fahr_convert.cpp
LIB_NAME := libtemp_conv.a
OBJ = $(SRC:%.cpp=%.o)

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
	@rm -f *.o *.a
	@rm -f depend_list
