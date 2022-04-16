#include "JIT.h"

JIT::JIT(std::unique_ptr<ExecutionSession> executionSession,
         JITTargetMachineBuilder JTMB, DataLayout dataLayout)
    : executionSession(std::move(executionSession)),
      dataLayout(std::move(dataLayout)),
      mangle(*this->executionSession, this->dataLayout),
      objectLayer(*this->executionSession,
                  []() { return std::make_unique<SectionMemoryManager>(); }),
      compileLayer(*this->executionSession, objectLayer,
                   std::make_unique<ConcurrentIRCompiler>(std::move(JTMB))),
      mainJD(this->executionSession->createBareJITDylib("<main>")) {

    mainJD.addGenerator(
        cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(
            dataLayout.getGlobalPrefix())));

    if (JTMB.getTargetTriple().isOSBinFormatCOFF()) {
        objectLayer.setOverrideObjectFlagsWithResponsibilityFlags(true);
        objectLayer.setAutoClaimResponsibilityForObjectSymbols(true);
    }
}

JIT::~JIT() {

    if (Error Err = executionSession->endSession()) {
        executionSession->reportError(std::move(Err));
    }
}

Expected<std::unique_ptr<JIT>> JIT::Create() {

    auto EPC = SelfExecutorProcessControl::Create();
    if (!EPC) {
        return EPC.takeError();
    }

    auto executionSession = std::make_unique<ExecutionSession>(std::move(*EPC));

    JITTargetMachineBuilder JTMB(
        executionSession->getExecutorProcessControl().getTargetTriple());

    auto dataLayout = JTMB.getDefaultDataLayoutForTarget();
    if (!dataLayout) {
        return dataLayout.takeError();
    }

    return std::make_unique<JIT>(std::move(executionSession), std::move(JTMB),
                                 std::move(*dataLayout));
}

const DataLayout& JIT::getDataLayout() const {
    return dataLayout;
}

Error JIT::addModule(ThreadSafeModule TSM) {
    ResourceTrackerSP RT = mainJD.getDefaultResourceTracker();
    return compileLayer.add(RT, std::move(TSM));
}

Expected<JITEvaluatedSymbol> JIT::lookup(StringRef Name) {
    return executionSession->lookup({&mainJD}, mangle(Name.str()));
}

JITDylib& JIT::getMainJITDylib() {
    return mainJD;
}

ExecutionSession& JIT::getExecutionSession() {
    return *executionSession;
}
