# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
# Makefile
# Makefile for libtemp_conv

CXX ?= $(shell which c++)

LIB_DIR := ../../../lib
INC := ../../../include
DEPS := $(INC)/conv_to_cent.hpp $(INC)/conv_to_fahr.hpp

SRC := cent_convert.cpp fahr_convert.cpp
LIBS := libtemp_conv.a
OBJS = $(SRC:%.cpp=%.o)

.PHONY: it install depend clean

all: it
it: $(LIBS)

$(LIBS): $(OBJS)
	ar cr $(LIBS) $^
	cp $(LIBS) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIBS)

$(OBJS): $(DEPS)
	$(CXX) -g -I$(INC) -c $(@:%.o=%.cpp) -o $@

install:
	cp $(LIBS) $(LIB_DIR)
	ranlib $(LIB_DIR)/$(LIBS)

depend:
	$(CXX) -M -g -I$(INC) $(SRC) > depend_list

# clean out temporary objects and files
clean:
	rm -f *.o *.a
	rm -f depend_list
