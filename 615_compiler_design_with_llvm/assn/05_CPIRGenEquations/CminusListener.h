
// Generated from /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"
#include "CminusParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by CminusParser.
 */
class  CminusListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(CminusParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(CminusParser::ProgramContext *ctx) = 0;

  virtual void enterVar_decleration(CminusParser::Var_declerationContext *ctx) = 0;
  virtual void exitVar_decleration(CminusParser::Var_declerationContext *ctx) = 0;

  virtual void enterFun_decleration(CminusParser::Fun_declerationContext *ctx) = 0;
  virtual void exitFun_decleration(CminusParser::Fun_declerationContext *ctx) = 0;

  virtual void enterParam(CminusParser::ParamContext *ctx) = 0;
  virtual void exitParam(CminusParser::ParamContext *ctx) = 0;

  virtual void enterCompound_stmt(CminusParser::Compound_stmtContext *ctx) = 0;
  virtual void exitCompound_stmt(CminusParser::Compound_stmtContext *ctx) = 0;

  virtual void enterStatement(CminusParser::StatementContext *ctx) = 0;
  virtual void exitStatement(CminusParser::StatementContext *ctx) = 0;

  virtual void enterSelection_stmt(CminusParser::Selection_stmtContext *ctx) = 0;
  virtual void exitSelection_stmt(CminusParser::Selection_stmtContext *ctx) = 0;

  virtual void enterIteration_stmt(CminusParser::Iteration_stmtContext *ctx) = 0;
  virtual void exitIteration_stmt(CminusParser::Iteration_stmtContext *ctx) = 0;

  virtual void enterAssignment_stmt(CminusParser::Assignment_stmtContext *ctx) = 0;
  virtual void exitAssignment_stmt(CminusParser::Assignment_stmtContext *ctx) = 0;

  virtual void enterReturn_stmt(CminusParser::Return_stmtContext *ctx) = 0;
  virtual void exitReturn_stmt(CminusParser::Return_stmtContext *ctx) = 0;

  virtual void enterAdd_exp(CminusParser::Add_expContext *ctx) = 0;
  virtual void exitAdd_exp(CminusParser::Add_expContext *ctx) = 0;

  virtual void enterParen_exp(CminusParser::Paren_expContext *ctx) = 0;
  virtual void exitParen_exp(CminusParser::Paren_expContext *ctx) = 0;

  virtual void enterNum_exp(CminusParser::Num_expContext *ctx) = 0;
  virtual void exitNum_exp(CminusParser::Num_expContext *ctx) = 0;

  virtual void enterCall_exp(CminusParser::Call_expContext *ctx) = 0;
  virtual void exitCall_exp(CminusParser::Call_expContext *ctx) = 0;

  virtual void enterVal_exp(CminusParser::Val_expContext *ctx) = 0;
  virtual void exitVal_exp(CminusParser::Val_expContext *ctx) = 0;

  virtual void enterMult_exp(CminusParser::Mult_expContext *ctx) = 0;
  virtual void exitMult_exp(CminusParser::Mult_expContext *ctx) = 0;

  virtual void enterRelational_exp(CminusParser::Relational_expContext *ctx) = 0;
  virtual void exitRelational_exp(CminusParser::Relational_expContext *ctx) = 0;


};

