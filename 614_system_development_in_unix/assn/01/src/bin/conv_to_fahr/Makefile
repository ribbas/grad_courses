# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# 
# Makefile for conv_to_fahr

CXX ?= $(shell which c++)

LIB_DIR := ../../../lib
INC_DIR := ../../../include
BIN_DIR := ../../../bin

SRC := conv_to_fahr.cpp
OBJ = $(SRC:%.cpp=%.o)
LIBS = "$(LIB_DIR)"/*.a
DEPS := $(INC_DIR)/$(SRC:%.cpp=%.hpp)
EXE = $(SRC:%.cpp=%)

.PHONY: it install depend clean

all: it
it: $(EXE)
$(EXE): $(OBJ) $(LIBS)
	$(CXX) -I$(INC_DIR) -g $(OBJ) -L$(LIB_DIR) -larg -ltemp_conv -o $(EXE)
	chmod 755 $(EXE)

$(OBJ):
	$(CXX) -I$(INC_DIR) -g -c $(SRC)

$(LIBS):
	@cd ../../lib && $(MAKE) --no-print-directory it

install:
	cp $(EXE) $(BIN_DIR)

depend:
	echo > depend_list
	$(CXX) -M -I$(INC_DIR) -g $(SRC) >> depend_list

# clean out temporary objects and executables
clean:
	rm -f *.o *.a *.out depend_list $(EXE)
