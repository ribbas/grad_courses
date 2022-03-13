
// Generated from /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4 by ANTLR 4.9

#pragma once


#include "SemPred.hpp"
#include "IR_Gen.hpp"


#include "antlr4-runtime.h"
#include "CminusParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by CminusParser.
 */
class  CminusVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by CminusParser.
   */
    virtual antlrcpp::Any visitProgram(CminusParser::ProgramContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration_list(CminusParser::Declaration_listContext *context) = 0;

    virtual antlrcpp::Any visitDeclaration(CminusParser::DeclarationContext *context) = 0;

    virtual antlrcpp::Any visitVar_declaration(CminusParser::Var_declarationContext *context) = 0;

    virtual antlrcpp::Any visitType_specifier(CminusParser::Type_specifierContext *context) = 0;

    virtual antlrcpp::Any visitFun_declaration(CminusParser::Fun_declarationContext *context) = 0;

    virtual antlrcpp::Any visitParams(CminusParser::ParamsContext *context) = 0;

    virtual antlrcpp::Any visitParam_list(CminusParser::Param_listContext *context) = 0;

    virtual antlrcpp::Any visitParam(CminusParser::ParamContext *context) = 0;

    virtual antlrcpp::Any visitCompound_statement(CminusParser::Compound_statementContext *context) = 0;

    virtual antlrcpp::Any visitLocal_declarations(CminusParser::Local_declarationsContext *context) = 0;

    virtual antlrcpp::Any visitStatement_list(CminusParser::Statement_listContext *context) = 0;

    virtual antlrcpp::Any visitStatement(CminusParser::StatementContext *context) = 0;

    virtual antlrcpp::Any visitExpression_statement(CminusParser::Expression_statementContext *context) = 0;

    virtual antlrcpp::Any visitSelection_statement(CminusParser::Selection_statementContext *context) = 0;

    virtual antlrcpp::Any visitIteration_statement(CminusParser::Iteration_statementContext *context) = 0;

    virtual antlrcpp::Any visitReturn_statement(CminusParser::Return_statementContext *context) = 0;

    virtual antlrcpp::Any visitExpression(CminusParser::ExpressionContext *context) = 0;

    virtual antlrcpp::Any visitVar(CminusParser::VarContext *context) = 0;

    virtual antlrcpp::Any visitSimple_expression(CminusParser::Simple_expressionContext *context) = 0;

    virtual antlrcpp::Any visitRelop(CminusParser::RelopContext *context) = 0;

    virtual antlrcpp::Any visitAdditive_expression(CminusParser::Additive_expressionContext *context) = 0;

    virtual antlrcpp::Any visitAddop(CminusParser::AddopContext *context) = 0;

    virtual antlrcpp::Any visitTerm(CminusParser::TermContext *context) = 0;

    virtual antlrcpp::Any visitMulop(CminusParser::MulopContext *context) = 0;

    virtual antlrcpp::Any visitFactor(CminusParser::FactorContext *context) = 0;

    virtual antlrcpp::Any visitCall(CminusParser::CallContext *context) = 0;

    virtual antlrcpp::Any visitArgs(CminusParser::ArgsContext *context) = 0;

    virtual antlrcpp::Any visitArg_list(CminusParser::Arg_listContext *context) = 0;


};

