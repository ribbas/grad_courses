
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "IR_Gen.h"
#include "SemPred.h"

#include "CminusParser.h"
#include "antlr4-runtime.h"

/**
 * This class defines an abstract visitor for a parse tree
 * produced by CminusParser.
 */
class CminusVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:
    SemanticPredicate semantics;

    /**
     * Visit parse trees produced by CminusParser.
     */
    virtual antlrcpp::Any
    visitProgram(CminusParser::ProgramContext* context) = 0;

    virtual antlrcpp::Any
    visitVar_declaration(CminusParser::Var_declarationContext* context) = 0;

    virtual antlrcpp::Any
    visitFun_declaration(CminusParser::Fun_declarationContext* context) = 0;

    virtual antlrcpp::Any visitFun_type_specifier(
        CminusParser::Fun_type_specifierContext* context) = 0;

    virtual antlrcpp::Any visitParam(CminusParser::ParamContext* context) = 0;

    virtual antlrcpp::Any
    visitCompound_stmt(CminusParser::Compound_stmtContext* context) = 0;

    virtual antlrcpp::Any
    visitStatement(CminusParser::StatementContext* context) = 0;

    virtual antlrcpp::Any
    visitSelection_stmt(CminusParser::Selection_stmtContext* context) = 0;

    virtual antlrcpp::Any
    visitIteration_stmt(CminusParser::Iteration_stmtContext* context) = 0;

    virtual antlrcpp::Any
    visitAssignment_stmt(CminusParser::Assignment_stmtContext* context) = 0;

    virtual antlrcpp::Any
    visitReturn_stmt(CminusParser::Return_stmtContext* context) = 0;

    virtual antlrcpp::Any
    visitAdd_exp(CminusParser::Add_expContext* context) = 0;

    virtual antlrcpp::Any
    visitParen_exp(CminusParser::Paren_expContext* context) = 0;

    virtual antlrcpp::Any
    visitNum_exp(CminusParser::Num_expContext* context) = 0;

    virtual antlrcpp::Any
    visitCall_exp(CminusParser::Call_expContext* context) = 0;

    virtual antlrcpp::Any
    visitVal_exp(CminusParser::Val_expContext* context) = 0;

    virtual antlrcpp::Any
    visitMult_exp(CminusParser::Mult_expContext* context) = 0;

    virtual antlrcpp::Any
    visitRelational_exp(CminusParser::Relational_expContext* context) = 0;

    virtual antlrcpp::Any visitAddop(CminusParser::AddopContext* context) = 0;

    virtual antlrcpp::Any visitMultop(CminusParser::MultopContext* context) = 0;

    virtual antlrcpp::Any visitRelop(CminusParser::RelopContext* context) = 0;
};
