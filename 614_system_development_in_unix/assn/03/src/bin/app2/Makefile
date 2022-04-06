# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Makefile for test_log
#

# set the C++ compiler if unset
CXX ?= $(shell which c++)

# root directory paths
LIB_DIR := ../../../lib
INC_DIR := ../../../include
BIN_DIR := ../../../bin

# source file for executable
SRC = $(shell basename $(CURDIR)).cpp

# required libraries for executable
LIBS = log_mgr thread_mgr
# construct library paths
LIB_ARS = $(LIBS:%=$(LIB_DIR)/lib%.a)
# construct library flags
LD_FLAGS = -lpthread -lrt -L$(LIB_DIR) $(LIBS:%=-l%)
# declare include headers and libraries as dependencies for the executable
DEP := $(LIBS:%=$(INC_DIR)/%.hpp) $(LIB_ARS)

# construct objects
OBJ := $(SRC:%.cpp=%.o)
# construct executables
EXE := $(SRC:%.cpp=%)

.PHONY: it install depend clean

it: $(EXE)
$(EXE): $(OBJ) $(DEP) depend
	$(CXX) -std=c++11 -I$(INC_DIR) -g $(OBJ) $(LD_FLAGS) -o $(EXE)
	chmod 755 $(EXE)

$(OBJ):
	$(CXX) -std=c++11 -I$(INC_DIR) -g -c $(SRC)

$(LIBA):
	@cd ../../lib && $(MAKE) --no-print-directory it

install: it
	cp $(EXE) $(BIN_DIR)

depend:
	echo > depend_list
	$(CXX) -M -std=c++11 -I$(INC_DIR) -g $(SRC) >> depend_list

# clean out temporary objects and executables
clean:
	rm -f *.o *.a *.out depend_list $(EXE)
