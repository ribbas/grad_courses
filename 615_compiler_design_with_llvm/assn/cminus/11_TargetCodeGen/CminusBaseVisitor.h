
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/07_CPIRGenWhile/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "CminusVisitor.h"
#include "LLVM_Util.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of CminusVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the
 * available methods.
 */
class CminusBaseVisitor : public CminusVisitor {

private:
    std::string assignmentVar;
    std::vector<llvm::Value*> expStack;
    bool errorFound;

    bool condInst;
    llvm::Value* condV;

    bool iterInst;
    llvm::Value* iterV;
    llvm::PHINode* iterPN;

    std::map<std::string, llvm::Value*> namedAllocas;
    std::unique_ptr<llvm::Module> module;

    std::unique_ptr<llvm::PassBuilder> PB;

public:
    CminusBaseVisitor(std::string fileName);

    void printModule(std::ofstream& fd);

    void optimize();

    void generateObject() {

        // Initialize the target registry etc.
        llvm::InitializeAllTargetInfos();
        llvm::InitializeAllTargets();
        llvm::InitializeAllTargetMCs();
        llvm::InitializeAllAsmParsers();
        llvm::InitializeAllAsmPrinters();

        std::string TargetTriple = llvm::sys::getDefaultTargetTriple();
        module->setTargetTriple(TargetTriple);

        std::string Error;
        const llvm::Target* Target =
            llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

        // Print an error and exit if we couldn't find the requested target.
        // This generally occurs if we've forgotten to initialise the
        // TargetRegistry or we have a bogus target triple.
        if (!Target) {
            llvm::errs() << Error;
            std::cout << "ERR\n";
            return;
        }

        std::string CPU = "generic";
        std::string Features = "";

        llvm::TargetOptions opt;
        llvm::Optional<llvm::Reloc::Model> RM =
            llvm::Optional<llvm::Reloc::Model>();
        llvm::TargetMachine* TheTargetMachine =
            Target->createTargetMachine(TargetTriple, CPU, Features, opt, RM);

        module->setDataLayout(TheTargetMachine->createDataLayout());

        std::string objName = "output.o";
        std::error_code errorCode;
        llvm::raw_fd_ostream dest(objName, errorCode);

        if (errorCode) {
            llvm::errs() << "Could not open file: " << errorCode.message();
            std::cout << "ERR\n";
            return;
        }

        llvm::legacy::PassManager pass;
        auto FileType = llvm::CGFT_ObjectFile;

        if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr,
                                                  FileType)) {
            llvm::errs() << "TheTargetMachine can't emit a file of this type";
            std::cout << "ERR\n";
            return;
        }

        module->print(llvm::outs(), nullptr);

        pass.run(*module);

        dest.flush();

        llvm::outs() << "Wrote " << objName << "\n";
    }

    virtual antlrcpp::Any
    visitProgram(CminusParser::ProgramContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitVar_declaration(CminusParser::Var_declarationContext* ctx) override;

    virtual antlrcpp::Any
    visitFun_declaration(CminusParser::Fun_declarationContext* ctx) override;

    virtual antlrcpp::Any visitFun_type_specifier(
        CminusParser::Fun_type_specifierContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParam(CminusParser::ParamContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitCompound_stmt(CminusParser::Compound_stmtContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitStatement(CminusParser::StatementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitSelection_stmt(CminusParser::Selection_stmtContext* ctx) override;

    virtual antlrcpp::Any
    visitRelational_exp(CminusParser::Relational_expContext* ctx) override;

    virtual antlrcpp::Any
    visitIteration_stmt(CminusParser::Iteration_stmtContext* ctx) override;

    virtual antlrcpp::Any
    visitAssignment_stmt(CminusParser::Assignment_stmtContext* ctx) override;

    virtual antlrcpp::Any
    visitReturn_stmt(CminusParser::Return_stmtContext* ctx) override;

    virtual antlrcpp::Any
    visitAdd_exp(CminusParser::Add_expContext* ctx) override;

    virtual antlrcpp::Any
    visitMult_exp(CminusParser::Mult_expContext* ctx) override;

    virtual antlrcpp::Any
    visitParen_exp(CminusParser::Paren_expContext* ctx) override {

        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitVal_exp(CminusParser::Val_expContext* ctx) override;

    virtual antlrcpp::Any
    visitNum_exp(CminusParser::Num_expContext* ctx) override;

    virtual antlrcpp::Any
    visitCall_exp(CminusParser::Call_expContext* ctx) override;

    virtual antlrcpp::Any visitAddop(CminusParser::AddopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitMultop(CminusParser::MultopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitRelop(CminusParser::RelopContext* ctx) override {
        return visitChildren(ctx);
    }
};
