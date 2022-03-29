#ifndef IR_GEN_H
#define IR_GEN_H

#include "JIT.h"
#include "llvm/ADT/APInt.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/Error.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"

static llvm::ExitOnError ExitOnErr;

// extern std::unique_ptr<llvm::LLVMContext> irContext;
// extern std::unique_ptr<llvm::IRBuilder<>> irBuilder;

// extern std::unique_ptr<llvm::Module> module;
// extern std::unique_ptr<llvm::orc::JIT> cellJIT;
// extern std::map<std::string, llvm::Value*> namedValues;

// inline void initJIT(std::string id = "") {
//     cellJIT = ExitOnErr(llvm::orc::JIT::Create());

//     // open a new context and module
//     irContext = std::make_unique<llvm::LLVMContext>();

//     // create a new builder for the module
//     irBuilder = std::make_unique<llvm::IRBuilder<>>(*irContext);
//     module = std::make_unique<llvm::Module>(id + "_module", *irContext);
//     module->setDataLayout(cellJIT->getDataLayout());
// }

#endif
