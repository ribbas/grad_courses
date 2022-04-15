#ifndef LLVM_UTIL_HPP
#define LLVM_UTIL_HPP

#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

extern std::unique_ptr<llvm::LLVMContext> irContext;
extern std::unique_ptr<llvm::IRBuilder<>> irBuilder;

#endif // LLVM_UTIL_HPP
