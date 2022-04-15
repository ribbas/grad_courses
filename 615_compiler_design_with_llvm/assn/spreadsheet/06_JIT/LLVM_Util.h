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
#include "llvm/Transforms/InstCombine/InstCombine.h"

using namespace llvm;
using namespace llvm::orc;

static ExitOnError ExitOnErr;

extern std::unique_ptr<LLVMContext> irContext;
extern std::unique_ptr<IRBuilder<>> irBuilder;

inline void initLLVMContext() {

    // open a new context and module
    irContext = std::make_unique<LLVMContext>();

    // create a new builder for the module
    irBuilder = std::make_unique<IRBuilder<>>(*irContext);
}

class JIT {
private:
    std::unique_ptr<ExecutionSession> ES;

    DataLayout DL;
    MangleAndInterner Mangle;

    RTDyldObjectLinkingLayer ObjectLayer;
    IRCompileLayer CompileLayer;

    JITDylib& MainJD;

public:
    JIT(std::unique_ptr<ExecutionSession> ES, JITTargetMachineBuilder JTMB,
        DataLayout DL)
        : ES(std::move(ES)), DL(std::move(DL)), Mangle(*this->ES, this->DL),
          ObjectLayer(
              *this->ES,
              []() { return std::make_unique<SectionMemoryManager>(); }),
          CompileLayer(*this->ES, ObjectLayer,
                       std::make_unique<ConcurrentIRCompiler>(std::move(JTMB))),
          MainJD(this->ES->createBareJITDylib("<main>")) {

        MainJD.addGenerator(
            cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(
                DL.getGlobalPrefix())));

        if (JTMB.getTargetTriple().isOSBinFormatCOFF()) {
            ObjectLayer.setOverrideObjectFlagsWithResponsibilityFlags(true);
            ObjectLayer.setAutoClaimResponsibilityForObjectSymbols(true);
        }
    }

    ~JIT() {

        if (Error Err = ES->endSession()) {
            ES->reportError(std::move(Err));
        }
    }

    static Expected<std::unique_ptr<JIT>> Create() {

        auto EPC = SelfExecutorProcessControl::Create();
        if (!EPC) {
            return EPC.takeError();
        }

        auto ES = std::make_unique<ExecutionSession>(std::move(*EPC));

        JITTargetMachineBuilder JTMB(
            ES->getExecutorProcessControl().getTargetTriple());

        auto DL = JTMB.getDefaultDataLayoutForTarget();
        if (!DL) {
            return DL.takeError();
        }

        return std::make_unique<JIT>(std::move(ES), std::move(JTMB),
                                     std::move(*DL));
    }

    const DataLayout& getDataLayout() const {
        return DL;
    }

    Error addModule(ThreadSafeModule TSM) {
        ResourceTrackerSP RT = MainJD.getDefaultResourceTracker();
        return CompileLayer.add(RT, std::move(TSM));
    }

    Expected<JITEvaluatedSymbol> lookup(StringRef Name) {
        return ES->lookup({&MainJD}, Mangle(Name.str()));
    }
};

#endif // LLVM_UTIL_H
