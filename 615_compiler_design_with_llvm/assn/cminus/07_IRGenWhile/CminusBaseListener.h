
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/07_CPIRGenWhile/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "CminusListener.h"
#include "antlr4-runtime.h"

/**
 * This class provides an empty implementation of CminusListener,
 * which can be extended to create a listener which only needs to handle a
 * subset of the available methods.
 */
class CminusBaseListener : public CminusListener {
public:
    virtual void enterProgram(CminusParser::ProgramContext* /*ctx*/) override {}
    virtual void exitProgram(CminusParser::ProgramContext* /*ctx*/) override {}

    virtual void enterVar_declaration(
        CminusParser::Var_declarationContext* /*ctx*/) override {}
    virtual void exitVar_declaration(
        CminusParser::Var_declarationContext* /*ctx*/) override {}

    virtual void enterFun_declaration(
        CminusParser::Fun_declarationContext* /*ctx*/) override {}
    virtual void exitFun_declaration(
        CminusParser::Fun_declarationContext* /*ctx*/) override {}

    virtual void enterFun_type_specifier(
        CminusParser::Fun_type_specifierContext* /*ctx*/) override {}
    virtual void exitFun_type_specifier(
        CminusParser::Fun_type_specifierContext* /*ctx*/) override {}

    virtual void enterParam(CminusParser::ParamContext* /*ctx*/) override {}
    virtual void exitParam(CminusParser::ParamContext* /*ctx*/) override {}

    virtual void
    enterCompound_stmt(CminusParser::Compound_stmtContext* /*ctx*/) override {}
    virtual void
    exitCompound_stmt(CminusParser::Compound_stmtContext* /*ctx*/) override {}

    virtual void
    enterStatement(CminusParser::StatementContext* /*ctx*/) override {}
    virtual void
    exitStatement(CminusParser::StatementContext* /*ctx*/) override {}

    virtual void
    enterSelection_stmt(CminusParser::Selection_stmtContext* /*ctx*/) override {
    }
    virtual void
    exitSelection_stmt(CminusParser::Selection_stmtContext* /*ctx*/) override {}

    virtual void
    enterIteration_stmt(CminusParser::Iteration_stmtContext* /*ctx*/) override {
    }
    virtual void
    exitIteration_stmt(CminusParser::Iteration_stmtContext* /*ctx*/) override {}

    virtual void enterAssignment_stmt(
        CminusParser::Assignment_stmtContext* /*ctx*/) override {}
    virtual void exitAssignment_stmt(
        CminusParser::Assignment_stmtContext* /*ctx*/) override {}

    virtual void
    enterReturn_stmt(CminusParser::Return_stmtContext* /*ctx*/) override {}
    virtual void
    exitReturn_stmt(CminusParser::Return_stmtContext* /*ctx*/) override {}

    virtual void enterAdd_exp(CminusParser::Add_expContext* /*ctx*/) override {}
    virtual void exitAdd_exp(CminusParser::Add_expContext* /*ctx*/) override {}

    virtual void
    enterParen_exp(CminusParser::Paren_expContext* /*ctx*/) override {}
    virtual void
    exitParen_exp(CminusParser::Paren_expContext* /*ctx*/) override {}

    virtual void enterNum_exp(CminusParser::Num_expContext* /*ctx*/) override {}
    virtual void exitNum_exp(CminusParser::Num_expContext* /*ctx*/) override {}

    virtual void
    enterCall_exp(CminusParser::Call_expContext* /*ctx*/) override {}
    virtual void exitCall_exp(CminusParser::Call_expContext* /*ctx*/) override {
    }

    virtual void enterVal_exp(CminusParser::Val_expContext* /*ctx*/) override {}
    virtual void exitVal_exp(CminusParser::Val_expContext* /*ctx*/) override {}

    virtual void
    enterMult_exp(CminusParser::Mult_expContext* /*ctx*/) override {}
    virtual void exitMult_exp(CminusParser::Mult_expContext* /*ctx*/) override {
    }

    virtual void enterAddop(CminusParser::AddopContext* /*ctx*/) override {}
    virtual void exitAddop(CminusParser::AddopContext* /*ctx*/) override {}

    virtual void enterMultop(CminusParser::MultopContext* /*ctx*/) override {}
    virtual void exitMultop(CminusParser::MultopContext* /*ctx*/) override {}

    virtual void
    enterRelational_exp(CminusParser::Relational_expContext* /*ctx*/) override {
    }
    virtual void
    exitRelational_exp(CminusParser::Relational_expContext* /*ctx*/) override {}

    virtual void enterRelop(CminusParser::RelopContext* /*ctx*/) override {}
    virtual void exitRelop(CminusParser::RelopContext* /*ctx*/) override {}

    virtual void enterEveryRule(antlr4::ParserRuleContext* /*ctx*/) override {}
    virtual void exitEveryRule(antlr4::ParserRuleContext* /*ctx*/) override {}
    virtual void visitTerminal(antlr4::tree::TerminalNode* /*node*/) override {}
    virtual void visitErrorNode(antlr4::tree::ErrorNode* /*node*/) override {}
};
