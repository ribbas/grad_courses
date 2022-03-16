# Makefile
# Sabbir Ahmed
#

# set the C++ compiler if unset
CXX = $(shell which clang++)

.PHONY: argpromotion simple-loop-unswitch clean

opts: argpromotion simple-loop-unswitch

argpromotion:
	@clang++ -S -emit-llvm -O -Xclang -disable-llvm-passes $@.cpp
	@opt -passes='mem2reg' $@.ll -S -o $@-after.ll

simple-loop-unswitch:
	@clang -S -emit-llvm -O -Xclang -disable-llvm-passes $@.c
	@opt -passes='licm,$@<nontrivial>' $@.ll -S -o $@-after.ll

clean:
	@rm *.ll *.bc
