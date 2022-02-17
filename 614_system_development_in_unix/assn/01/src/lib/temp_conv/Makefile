# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Makefile for lib/temp_conv

# set the C++ compiler if unset
CXX ?= $(shell which c++)

# root directory paths
LIB_DIR := ../../../lib
INC_DIR := ../../../include

# source files for library file
SRC := cent_convert.cpp fahr_convert.cpp

# declare include headers as dependencies for the executable
DEPS := $(INC_DIR)/conv_to_cent.hpp $(INC_DIR)/conv_to_fahr.hpp
# declare library paths
LIB := libtemp_conv.a
# construct objects
OBJ = $(SRC:%.cpp=%.o)

.PHONY: it install depend clean

it: $(LIB)
$(LIB): $(OBJ)
	ar cr $(LIB) $^
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

$(OBJ): $(DEPS)
	$(CXX) -g -I$(INC_DIR) -c $(@:%.o=%.cpp) -o $@

install:
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

depend:
	$(CXX) -M -g -I$(INC_DIR) $(SRC) > depend_list

# clean out temporary objects and files
clean:
	rm -f *.o *.a depend_list
