
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
