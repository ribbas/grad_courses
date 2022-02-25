# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# 
# Makefile for lib/arg

# set the C++ compiler if unset
CXX ?= $(shell which c++)

# root directory paths
LIB_DIR := ../../../lib
INC_DIR := ../../../include

# source file for library file
SRC := log_mgr.cpp

# declare include headers as dependencies for the executable
DEPS := $(INC_DIR)/$(SRC:%.cpp=%.hpp) depend_list
# construct library paths
LIB = $(SRC:%.cpp=lib%.a)
# construct objects
OBJ = $(SRC:.cpp=.o)

.PHONY: it install depend clean

it: $(LIB)
$(LIB): $(OBJ)
	ar cr $(LIB) $(OBJ)
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

$(OBJ): $(DEPS)
	$(CXX) -g -I$(INC_DIR) -c $(@:%.o=%.cpp) -o $@

install: it
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

depend:
	$(CXX) -M -g -I$(INC_DIR) $(SRC) > depend_list

# clean out temporary objects and files
clean:
	rm -f *.o *.a depend_list
