
// Generated from /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4 by ANTLR 4.9

#pragma once


#include "antlr4-runtime.h"
#include "CminusListener.h"


/**
 * This class provides an empty implementation of CminusListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  CminusBaseListener : public CminusListener {
public:

  virtual void enterProgram(CminusParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(CminusParser::ProgramContext * /*ctx*/) override { }

  virtual void enterDeclaration_list(CminusParser::Declaration_listContext * /*ctx*/) override { }
  virtual void exitDeclaration_list(CminusParser::Declaration_listContext * /*ctx*/) override { }

  virtual void enterDeclaration(CminusParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(CminusParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterVar_declaration(CminusParser::Var_declarationContext * /*ctx*/) override { }
  virtual void exitVar_declaration(CminusParser::Var_declarationContext * /*ctx*/) override { }

  virtual void enterType_specifier(CminusParser::Type_specifierContext * /*ctx*/) override { }
  virtual void exitType_specifier(CminusParser::Type_specifierContext * /*ctx*/) override { }

  virtual void enterFun_declaration(CminusParser::Fun_declarationContext * /*ctx*/) override { }
  virtual void exitFun_declaration(CminusParser::Fun_declarationContext * /*ctx*/) override { }

  virtual void enterParams(CminusParser::ParamsContext * /*ctx*/) override { }
  virtual void exitParams(CminusParser::ParamsContext * /*ctx*/) override { }

  virtual void enterParam_list(CminusParser::Param_listContext * /*ctx*/) override { }
  virtual void exitParam_list(CminusParser::Param_listContext * /*ctx*/) override { }

  virtual void enterParam(CminusParser::ParamContext * /*ctx*/) override { }
  virtual void exitParam(CminusParser::ParamContext * /*ctx*/) override { }

  virtual void enterCompound_statement(CminusParser::Compound_statementContext * /*ctx*/) override { }
  virtual void exitCompound_statement(CminusParser::Compound_statementContext * /*ctx*/) override { }

  virtual void enterLocal_declarations(CminusParser::Local_declarationsContext * /*ctx*/) override { }
  virtual void exitLocal_declarations(CminusParser::Local_declarationsContext * /*ctx*/) override { }

  virtual void enterStatement_list(CminusParser::Statement_listContext * /*ctx*/) override { }
  virtual void exitStatement_list(CminusParser::Statement_listContext * /*ctx*/) override { }

  virtual void enterStatement(CminusParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(CminusParser::StatementContext * /*ctx*/) override { }

  virtual void enterExpression_statement(CminusParser::Expression_statementContext * /*ctx*/) override { }
  virtual void exitExpression_statement(CminusParser::Expression_statementContext * /*ctx*/) override { }

  virtual void enterSelection_statement(CminusParser::Selection_statementContext * /*ctx*/) override { }
  virtual void exitSelection_statement(CminusParser::Selection_statementContext * /*ctx*/) override { }

  virtual void enterIteration_statement(CminusParser::Iteration_statementContext * /*ctx*/) override { }
  virtual void exitIteration_statement(CminusParser::Iteration_statementContext * /*ctx*/) override { }

  virtual void enterReturn_statement(CminusParser::Return_statementContext * /*ctx*/) override { }
  virtual void exitReturn_statement(CminusParser::Return_statementContext * /*ctx*/) override { }

  virtual void enterExpression(CminusParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(CminusParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterVar(CminusParser::VarContext * /*ctx*/) override { }
  virtual void exitVar(CminusParser::VarContext * /*ctx*/) override { }

  virtual void enterSimple_expression(CminusParser::Simple_expressionContext * /*ctx*/) override { }
  virtual void exitSimple_expression(CminusParser::Simple_expressionContext * /*ctx*/) override { }

  virtual void enterRelop(CminusParser::RelopContext * /*ctx*/) override { }
  virtual void exitRelop(CminusParser::RelopContext * /*ctx*/) override { }

  virtual void enterAdditive_expression(CminusParser::Additive_expressionContext * /*ctx*/) override { }
  virtual void exitAdditive_expression(CminusParser::Additive_expressionContext * /*ctx*/) override { }

  virtual void enterAddop(CminusParser::AddopContext * /*ctx*/) override { }
  virtual void exitAddop(CminusParser::AddopContext * /*ctx*/) override { }

  virtual void enterTerm(CminusParser::TermContext * /*ctx*/) override { }
  virtual void exitTerm(CminusParser::TermContext * /*ctx*/) override { }

  virtual void enterMulop(CminusParser::MulopContext * /*ctx*/) override { }
  virtual void exitMulop(CminusParser::MulopContext * /*ctx*/) override { }

  virtual void enterFactor(CminusParser::FactorContext * /*ctx*/) override { }
  virtual void exitFactor(CminusParser::FactorContext * /*ctx*/) override { }

  virtual void enterCall(CminusParser::CallContext * /*ctx*/) override { }
  virtual void exitCall(CminusParser::CallContext * /*ctx*/) override { }

  virtual void enterArgs(CminusParser::ArgsContext * /*ctx*/) override { }
  virtual void exitArgs(CminusParser::ArgsContext * /*ctx*/) override { }

  virtual void enterArg_list(CminusParser::Arg_listContext * /*ctx*/) override { }
  virtual void exitArg_list(CminusParser::Arg_listContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

