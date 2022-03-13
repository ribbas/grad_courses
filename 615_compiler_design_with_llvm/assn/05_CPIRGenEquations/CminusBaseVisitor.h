
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "CminusVisitor.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of CminusVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the
 * available methods.
 */
class CminusBaseVisitor : public CminusVisitor {
public:
    virtual antlrcpp::Any
    visitProgram(CminusParser::ProgramContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitDeclaration_list(CminusParser::Declaration_listContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitDeclaration(CminusParser::DeclarationContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitVar_declaration(CminusParser::Var_declarationContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitType_specifier(CminusParser::Type_specifierContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitFun_declaration(CminusParser::Fun_declarationContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitParams(CminusParser::ParamsContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitParam_list(CminusParser::Param_listContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitParam(CminusParser::ParamContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCompound_statement(
        CminusParser::Compound_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitLocal_declarations(
        CminusParser::Local_declarationsContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitStatement_list(CminusParser::Statement_listContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitStatement(CminusParser::StatementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitExpression_statement(
        CminusParser::Expression_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSelection_statement(
        CminusParser::Selection_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitIteration_statement(
        CminusParser::Iteration_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitReturn_statement(CminusParser::Return_statementContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitExpression(CminusParser::ExpressionContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitVar(CminusParser::VarContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitSimple_expression(
        CminusParser::Simple_expressionContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitRelop(CminusParser::RelopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAdditive_expression(
        CminusParser::Additive_expressionContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitAddop(CminusParser::AddopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitTerm(CminusParser::TermContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitMulop(CminusParser::MulopContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitFactor(CminusParser::FactorContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitCall(CminusParser::CallContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any visitArgs(CminusParser::ArgsContext* ctx) override {
        return visitChildren(ctx);
    }

    virtual antlrcpp::Any
    visitArg_list(CminusParser::Arg_listContext* ctx) override {
        return visitChildren(ctx);
    }
};
