# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Main Makefile for the project

CXX ?= $(shell which c++)

LIB_DIR := ../../../lib
INC := ../../../include
DEPS := $(INC)/conv_to_cent.hpp $(INC)/conv_to_fahr.hpp

SRC := arg.cpp
LIB_NAME := libarg.a
OBJS = $(SRC:.cpp=.o)

.PHONY: it install depend clean

all: it
it: $(LIB_NAME)

$(LIB_NAME): $(OBJS)
	ar cr $(LIB_NAME) $(OBJS)
	cp $(LIB_NAME) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB_NAME)

$(OBJS): $(DEPS)
	$(CXX) -g -I$(INC) -c $(@:%.o=%.cpp) -o $@

install:
	cp $(LIB_NAME) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB_NAME)

depend:
	$(CXX) -M -g -I$(INC) $(SRC) > depend_list

# clean out temporary objects and files
clean:
	rm -f *.o *.a
	rm -f depend_list
