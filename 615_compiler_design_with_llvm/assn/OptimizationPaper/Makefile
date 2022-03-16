# Makefile
# Sabbir Ahmed
#

# set the C++ compiler if unset
CXX = $(shell which clang++)

.PHONY: argpromotion simple-loop-unswitch clean

opts: argpromotion simple-loop-unswitch

# @clang++ -S -emit-llvm -O -Xclang -disable-llvm-passes $@.cpp
# @clang -emit-llvm -O0 -Xclang -disable-llvm-passes -c $@.c
# @llvm-dis $@.bc -o $@-before.ll
argpromotion:
	@clang -S -emit-llvm -O -Xclang -disable-llvm-passes $@.c -o $@-before.ll
	@opt -passes='$@,mem2reg' $@-before.ll -S -o $@-after.ll

simple-loop-unswitch:
	@clang -S -emit-llvm -O -Xclang -disable-llvm-passes $@.c -o $@-before.ll
	@opt -passes='licm,$@<nontrivial>' $@-before.ll -S -o $@-after.ll
