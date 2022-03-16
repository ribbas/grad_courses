# Makefile
# Sabbir Ahmed
# System Development in the Unix Environment (605.614)
#
# Root Makefile for the project
#

# set the C++ compiler if unset
CXX = $(shell which clang++)

.PHONY: argpromotion loop-unswitch clean

all: argpromotion loop-unswitch

argpromotion:
	@clang++ -O0 -emit-llvm -S -c $@.cpp
	@opt -$@ $@.ll -S -o $@-before.ll

loop-unswitch:
	@clang -O0 -emit-llvm -S -c $@.c
	@opt -enable-new-pm=0 -$@ $@.ll -S -o $@-before.ll

clean:
	@rm *.ll *.bc