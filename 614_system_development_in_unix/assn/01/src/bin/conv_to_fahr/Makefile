# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Main Makefile for the project

CXX ?= $(shell which c++)

LIB_DIR := ../../../lib
INC := ../../../include
BIN := ../../../bin

SRC := conv_to_fahr.cpp
OBJ = $(SRC:%.cpp=%.o)
DEPS := $(INC)/$(SRC:%.cpp=%.hpp)
EXE = $(SRC:%.cpp=%)

.PHONY: it install depend clean
all: it
it: $(EXE)

$(EXE): $(OBJ)
	$(CXX) -I$(INC) -g $(OBJ) -L$(LIB_DIR) -larg -ltemp_conv -o $(EXE)
	chmod 755 $(EXE)

$(OBJ): $(INC)/$(SRC:%.cpp=%.hpp) $(LIB_DIR)/libarg.a $(LIB_DIR)/libtemp_conv.a
	$(CXX) -I$(INC) -g -c $(SRC)

$(LIB_DIR)/libarg.a $(LIB_DIR)/libtemp_conv.a:
	@cd ../../lib && $(MAKE) --no-print-directory it

install:
	cp $(EXE) $(BIN)

depend:
	@echo > depend_list
	@$(CXX) -M -I$(INC) -g $(SRC) >> depend_list

# clean out temporary objects and executables
clean:
	rm -f *.o *.a *.out
	rm -f depend_list $(EXE)
