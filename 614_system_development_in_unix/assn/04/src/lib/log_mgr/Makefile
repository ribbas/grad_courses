# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Makefile for lib/log_mgr
#

# set the C++ compiler if unset
CXX ?= $(shell which c++)

# root directory paths
PROJ_DIR = ../../..
LIB_DIR := $(PROJ_DIR)/lib
INC_DIR := $(PROJ_DIR)/include

# source file for library file
SRC := log_mgr.cpp

# declare include headers as dependencies for the executable
DEPS := $(INC_DIR)/$(SRC:%.cpp=%.hpp)
# construct library paths
LIB = $(SRC:%.cpp=lib%.a)
# construct objects
OBJ = $(SRC:.cpp=.o)

.PHONY: default it install depend clean
default: it

it: $(LIB)
$(LIB): $(OBJ)
	ar cr $(LIB) $(OBJ)
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

$(OBJ): $(DEPS)
	$(CXX) -g -std=c++11 -I$(INC_DIR) -c $(@:%.o=%.cpp) -o $@

install: it
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

depend:
	$(CXX) -M -g -std=c++11 -I$(INC_DIR) $(SRC) > depend_list

# clean out temporary objects and files
clean:
	rm -f *.o *.a depend_list

-include depend_list
