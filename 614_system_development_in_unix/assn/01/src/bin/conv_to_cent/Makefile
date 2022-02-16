# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for conv_to_cent

CXX = /usr/bin/g++

LIB := ../../../lib
INC := ../../../include
BIN := ../../../bin

SRC := conv_to_cent.cpp
OBJ = $(SRC:%.cpp=%.o)
EXE = $(SRC:%.cpp=%)

.PHONY: it install depend clean

it:
	$(CXX) -I$(INC) -g -c $(SRC)
	$(CXX) -I$(INC) -g $(OBJ) -L$(LIB) -larg -ltemp_conv -o $(EXE)
	chmod 755 $(EXE)

install:
	$(CXX) -I$(INC) -g $(OBJ) -L$(LIB) -larg -ltemp_conv
	chmod 755 $(EXE)
	cp $(EXE) $(BIN)

depend:
	@echo > depend_list
	@$(CXX) -M -I$(INC) -g $(SRC) >> depend_list

clean:
	# clean out temporary and library files and executable
	@rm -f *.o *.a *.out
	@rm -f depend_list $(EXE)
