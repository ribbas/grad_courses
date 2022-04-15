#ifndef LLVM_UTIL_H
#define LLVM_UTIL_H

#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

using namespace llvm;
using namespace llvm::orc;

class TableOfCells;
// open spreadsheet cell table
extern TableOfCells symTab;

static ExitOnError ExitOnErr;

extern std::unique_ptr<LLVMContext> irContext;
extern std::unique_ptr<IRBuilder<>> irBuilder;

inline void initLLVMContext() {

    // open a new context and module
    irContext = std::make_unique<LLVMContext>();

    // create a new builder for the module
    irBuilder = std::make_unique<IRBuilder<>>(*irContext);
}

#endif // LLVM_UTIL_H
