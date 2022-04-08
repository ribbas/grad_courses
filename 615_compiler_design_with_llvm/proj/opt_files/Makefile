#
# Makefile
# Sabbir Ahmed
#

# set the C compiler to clang
CC := $(shell which clang)
CC_FLAGS = -S -emit-llvm -O -Xclang -disable-llvm-passes

.PHONY: argpromotion simple-loop-unswitch
all: argpromotion simple-loop-unswitch

argpromotion:
	$(CC) $(CC_FLAGS) $@.c -o $@-before.ll
	opt -passes='$@,instcombine,function-attrs,verify' $@-before.ll -S -o $@-after.ll

simple-loop-unswitch:
	$(CC) $(CC_FLAGS) $@.c -o $@-before.ll
	opt -passes='loop-mssa($@,licm),verify' $@-before.ll -S -o $@-after.ll
