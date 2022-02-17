# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# 
# Makefile for lib/arg

CXX ?= $(shell which c++)

LIB_DIR := ../../../lib
INC := ../../../include
DEPS := $(INC)/conv_to_cent.hpp $(INC)/conv_to_fahr.hpp

SRC := arg.cpp
LIB := libarg.a
OBJS = $(SRC:.cpp=.o)

.PHONY: it install depend clean

all: it
it: $(LIB)
$(LIB): $(OBJS)
	ar cr $(LIB) $(OBJS)
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

$(OBJS): $(DEPS)
	$(CXX) -g -I$(INC) -c $(@:%.o=%.cpp) -o $@

install:
	cp $(LIB) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIB)

depend:
	$(CXX) -M -g -I$(INC) $(SRC) > depend_list

# clean out temporary objects and files
clean:
	rm -f *.o *.a depend_list
