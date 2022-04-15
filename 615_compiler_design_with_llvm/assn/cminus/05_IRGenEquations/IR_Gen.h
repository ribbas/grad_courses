#ifndef IR_GEN_HPP
#define IR_GEN_HPP

#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"

extern std::unique_ptr<llvm::LLVMContext> irContext;
extern std::unique_ptr<llvm::IRBuilder<>> irBuilder;

#endif
