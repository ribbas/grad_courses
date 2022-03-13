
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "CminusParser.h"
#include "antlr4-runtime.h"

/**
 * This interface defines an abstract listener for a parse tree produced by
 * CminusParser.
 */
class CminusListener : public antlr4::tree::ParseTreeListener {
public:
    virtual void enterProgram(CminusParser::ProgramContext* ctx) = 0;
    virtual void exitProgram(CminusParser::ProgramContext* ctx) = 0;

    virtual void
    enterDeclaration_list(CminusParser::Declaration_listContext* ctx) = 0;
    virtual void
    exitDeclaration_list(CminusParser::Declaration_listContext* ctx) = 0;

    virtual void enterDeclaration(CminusParser::DeclarationContext* ctx) = 0;
    virtual void exitDeclaration(CminusParser::DeclarationContext* ctx) = 0;

    virtual void
    enterVar_declaration(CminusParser::Var_declarationContext* ctx) = 0;
    virtual void
    exitVar_declaration(CminusParser::Var_declarationContext* ctx) = 0;

    virtual void
    enterType_specifier(CminusParser::Type_specifierContext* ctx) = 0;
    virtual void
    exitType_specifier(CminusParser::Type_specifierContext* ctx) = 0;

    virtual void
    enterFun_declaration(CminusParser::Fun_declarationContext* ctx) = 0;
    virtual void
    exitFun_declaration(CminusParser::Fun_declarationContext* ctx) = 0;

    virtual void enterParams(CminusParser::ParamsContext* ctx) = 0;
    virtual void exitParams(CminusParser::ParamsContext* ctx) = 0;

    virtual void enterParam_list(CminusParser::Param_listContext* ctx) = 0;
    virtual void exitParam_list(CminusParser::Param_listContext* ctx) = 0;

    virtual void enterParam(CminusParser::ParamContext* ctx) = 0;
    virtual void exitParam(CminusParser::ParamContext* ctx) = 0;

    virtual void
    enterCompound_statement(CminusParser::Compound_statementContext* ctx) = 0;
    virtual void
    exitCompound_statement(CminusParser::Compound_statementContext* ctx) = 0;

    virtual void
    enterLocal_declarations(CminusParser::Local_declarationsContext* ctx) = 0;
    virtual void
    exitLocal_declarations(CminusParser::Local_declarationsContext* ctx) = 0;

    virtual void
    enterStatement_list(CminusParser::Statement_listContext* ctx) = 0;
    virtual void
    exitStatement_list(CminusParser::Statement_listContext* ctx) = 0;

    virtual void enterStatement(CminusParser::StatementContext* ctx) = 0;
    virtual void exitStatement(CminusParser::StatementContext* ctx) = 0;

    virtual void enterExpression_statement(
        CminusParser::Expression_statementContext* ctx) = 0;
    virtual void exitExpression_statement(
        CminusParser::Expression_statementContext* ctx) = 0;

    virtual void
    enterSelection_statement(CminusParser::Selection_statementContext* ctx) = 0;
    virtual void
    exitSelection_statement(CminusParser::Selection_statementContext* ctx) = 0;

    virtual void
    enterIteration_statement(CminusParser::Iteration_statementContext* ctx) = 0;
    virtual void
    exitIteration_statement(CminusParser::Iteration_statementContext* ctx) = 0;

    virtual void
    enterReturn_statement(CminusParser::Return_statementContext* ctx) = 0;
    virtual void
    exitReturn_statement(CminusParser::Return_statementContext* ctx) = 0;

    virtual void enterExpression(CminusParser::ExpressionContext* ctx) = 0;
    virtual void exitExpression(CminusParser::ExpressionContext* ctx) = 0;

    virtual void enterVar(CminusParser::VarContext* ctx) = 0;
    virtual void exitVar(CminusParser::VarContext* ctx) = 0;

    virtual void
    enterSimple_expression(CminusParser::Simple_expressionContext* ctx) = 0;
    virtual void
    exitSimple_expression(CminusParser::Simple_expressionContext* ctx) = 0;

    virtual void enterRelop(CminusParser::RelopContext* ctx) = 0;
    virtual void exitRelop(CminusParser::RelopContext* ctx) = 0;

    virtual void
    enterAdditive_expression(CminusParser::Additive_expressionContext* ctx) = 0;
    virtual void
    exitAdditive_expression(CminusParser::Additive_expressionContext* ctx) = 0;

    virtual void enterAddop(CminusParser::AddopContext* ctx) = 0;
    virtual void exitAddop(CminusParser::AddopContext* ctx) = 0;

    virtual void enterTerm(CminusParser::TermContext* ctx) = 0;
    virtual void exitTerm(CminusParser::TermContext* ctx) = 0;

    virtual void enterMulop(CminusParser::MulopContext* ctx) = 0;
    virtual void exitMulop(CminusParser::MulopContext* ctx) = 0;

    virtual void enterFactor(CminusParser::FactorContext* ctx) = 0;
    virtual void exitFactor(CminusParser::FactorContext* ctx) = 0;

    virtual void enterCall(CminusParser::CallContext* ctx) = 0;
    virtual void exitCall(CminusParser::CallContext* ctx) = 0;

    virtual void enterArgs(CminusParser::ArgsContext* ctx) = 0;
    virtual void exitArgs(CminusParser::ArgsContext* ctx) = 0;

    virtual void enterArg_list(CminusParser::Arg_listContext* ctx) = 0;
    virtual void exitArg_list(CminusParser::Arg_listContext* ctx) = 0;
};
