#ifndef JIT_H
#define JIT_H

#include "LLVM_Util.h"

class JIT {
  private:
    std::unique_ptr<ExecutionSession> executionSession;

    DataLayout dataLayout;
    MangleAndInterner mangle;

    RTDyldObjectLinkingLayer objectLayer;
    IRCompileLayer compileLayer;

    JITDylib& mainJD;
    SymbolMap symbolMap;

  public:
    JIT(std::unique_ptr<ExecutionSession>, JITTargetMachineBuilder, DataLayout);

    ~JIT();

    static Expected<std::unique_ptr<JIT>> Create();

    const DataLayout& getDataLayout() const;

    Error addModule(ThreadSafeModule);

    Expected<JITEvaluatedSymbol> lookup(StringRef);

    JITDylib& getMainJITDylib() {
        return mainJD;
    }

    ExecutionSession& getExecutionSession() {
        return *executionSession;
    }
};

#endif // JIT_H