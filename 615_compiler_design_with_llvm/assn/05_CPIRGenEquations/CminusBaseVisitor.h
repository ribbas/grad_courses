
// Generated from /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"
#include "CminusVisitor.h"


/**
 * This class provides an empty implementation of CminusVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  CminusBaseVisitor : public CminusVisitor {
public:

  virtual antlrcpp::Any visitProgram(CminusParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVar_decleration(CminusParser::Var_declerationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitFun_decleration(CminusParser::Fun_declerationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParam(CminusParser::ParamContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCompound_stmt(CminusParser::Compound_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitStatement(CminusParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitSelection_stmt(CminusParser::Selection_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitIteration_stmt(CminusParser::Iteration_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAssignment_stmt(CminusParser::Assignment_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitReturn_stmt(CminusParser::Return_stmtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitAdd_exp(CminusParser::Add_expContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitParen_exp(CminusParser::Paren_expContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitNum_exp(CminusParser::Num_expContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitCall_exp(CminusParser::Call_expContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitVal_exp(CminusParser::Val_expContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitMult_exp(CminusParser::Mult_expContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual antlrcpp::Any visitRelational_exp(CminusParser::Relational_expContext *ctx) override {
    return visitChildren(ctx);
  }


};

