
// Generated from /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4 by ANTLR 4.9


#include "SemPred.hpp"


#include "CminusListener.h"
#include "CminusVisitor.h"

#include "CminusParser.h"


using namespace antlrcpp;
using namespace antlr4;

CminusParser::CminusParser(TokenStream *input) : Parser(input) {
  _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA, _sharedContextCache);
}

CminusParser::~CminusParser() {
  delete _interpreter;
}

std::string CminusParser::getGrammarFileName() const {
  return "Cminus.g4";
}

const std::vector<std::string>& CminusParser::getRuleNames() const {
  return _ruleNames;
}

dfa::Vocabulary& CminusParser::getVocabulary() const {
  return _vocabulary;
}


//----------------- ProgramContext ------------------------------------------------------------------

CminusParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Declaration_listContext* CminusParser::ProgramContext::declaration_list() {
  return getRuleContext<CminusParser::Declaration_listContext>(0);
}

tree::TerminalNode* CminusParser::ProgramContext::EOF() {
  return getToken(CminusParser::EOF, 0);
}


size_t CminusParser::ProgramContext::getRuleIndex() const {
  return CminusParser::RuleProgram;
}

void CminusParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void CminusParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


antlrcpp::Any CminusParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::ProgramContext* CminusParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, CminusParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(58);
    declaration_list(0);
    setState(59);
    match(CminusParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Declaration_listContext ------------------------------------------------------------------

CminusParser::Declaration_listContext::Declaration_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::DeclarationContext* CminusParser::Declaration_listContext::declaration() {
  return getRuleContext<CminusParser::DeclarationContext>(0);
}

CminusParser::Declaration_listContext* CminusParser::Declaration_listContext::declaration_list() {
  return getRuleContext<CminusParser::Declaration_listContext>(0);
}


size_t CminusParser::Declaration_listContext::getRuleIndex() const {
  return CminusParser::RuleDeclaration_list;
}

void CminusParser::Declaration_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration_list(this);
}

void CminusParser::Declaration_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration_list(this);
}


antlrcpp::Any CminusParser::Declaration_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitDeclaration_list(this);
  else
    return visitor->visitChildren(this);
}


CminusParser::Declaration_listContext* CminusParser::declaration_list() {
   return declaration_list(0);
}

CminusParser::Declaration_listContext* CminusParser::declaration_list(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::Declaration_listContext *_localctx = _tracker.createInstance<Declaration_listContext>(_ctx, parentState);
  CminusParser::Declaration_listContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, CminusParser::RuleDeclaration_list, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(62);
    declaration();
    _ctx->stop = _input->LT(-1);
    setState(68);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Declaration_listContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleDeclaration_list);
        setState(64);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(65);
        declaration(); 
      }
      setState(70);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- DeclarationContext ------------------------------------------------------------------

CminusParser::DeclarationContext::DeclarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Var_declarationContext* CminusParser::DeclarationContext::var_declaration() {
  return getRuleContext<CminusParser::Var_declarationContext>(0);
}

CminusParser::Fun_declarationContext* CminusParser::DeclarationContext::fun_declaration() {
  return getRuleContext<CminusParser::Fun_declarationContext>(0);
}


size_t CminusParser::DeclarationContext::getRuleIndex() const {
  return CminusParser::RuleDeclaration;
}

void CminusParser::DeclarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDeclaration(this);
}

void CminusParser::DeclarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDeclaration(this);
}


antlrcpp::Any CminusParser::DeclarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitDeclaration(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::DeclarationContext* CminusParser::declaration() {
  DeclarationContext *_localctx = _tracker.createInstance<DeclarationContext>(_ctx, getState());
  enterRule(_localctx, 4, CminusParser::RuleDeclaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(73);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 1, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(71);
      var_declaration();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(72);
      fun_declaration();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_declarationContext ------------------------------------------------------------------

CminusParser::Var_declarationContext::Var_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Type_specifierContext* CminusParser::Var_declarationContext::type_specifier() {
  return getRuleContext<CminusParser::Type_specifierContext>(0);
}

tree::TerminalNode* CminusParser::Var_declarationContext::ID() {
  return getToken(CminusParser::ID, 0);
}

tree::TerminalNode* CminusParser::Var_declarationContext::SEMICOLON() {
  return getToken(CminusParser::SEMICOLON, 0);
}

tree::TerminalNode* CminusParser::Var_declarationContext::LBRACKET() {
  return getToken(CminusParser::LBRACKET, 0);
}

tree::TerminalNode* CminusParser::Var_declarationContext::NUM() {
  return getToken(CminusParser::NUM, 0);
}

tree::TerminalNode* CminusParser::Var_declarationContext::RBRACKET() {
  return getToken(CminusParser::RBRACKET, 0);
}


size_t CminusParser::Var_declarationContext::getRuleIndex() const {
  return CminusParser::RuleVar_declaration;
}

void CminusParser::Var_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar_declaration(this);
}

void CminusParser::Var_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar_declaration(this);
}


antlrcpp::Any CminusParser::Var_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitVar_declaration(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Var_declarationContext* CminusParser::var_declaration() {
  Var_declarationContext *_localctx = _tracker.createInstance<Var_declarationContext>(_ctx, getState());
  enterRule(_localctx, 6, CminusParser::RuleVar_declaration);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(75);
    dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext = type_specifier();
    setState(76);
    dynamic_cast<Var_declarationContext *>(_localctx)->idToken = match(CminusParser::ID);
    setState(80);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CminusParser::LBRACKET) {
      setState(77);
      match(CminusParser::LBRACKET);
      setState(78);
      match(CminusParser::NUM);
      setState(79);
      match(CminusParser::RBRACKET);
    }
    setState(82);
    match(CminusParser::SEMICOLON);
    setState(83);

    if (!(semantics.isValidVarType((dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext->start, dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext->stop) : nullptr))
    		)) throw FailedPredicateException(this, "semantics.isValidVarType($type_specifier.text)\n\t\t");
    semantics.addSymbol((dynamic_cast<Var_declarationContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Var_declarationContext *>(_localctx)->idToken->getText() : ""), (dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext->start, dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext->stop) : nullptr));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Type_specifierContext ------------------------------------------------------------------

CminusParser::Type_specifierContext::Type_specifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Type_specifierContext::INT() {
  return getToken(CminusParser::INT, 0);
}

tree::TerminalNode* CminusParser::Type_specifierContext::VOID() {
  return getToken(CminusParser::VOID, 0);
}


size_t CminusParser::Type_specifierContext::getRuleIndex() const {
  return CminusParser::RuleType_specifier;
}

void CminusParser::Type_specifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterType_specifier(this);
}

void CminusParser::Type_specifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitType_specifier(this);
}


antlrcpp::Any CminusParser::Type_specifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitType_specifier(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Type_specifierContext* CminusParser::type_specifier() {
  Type_specifierContext *_localctx = _tracker.createInstance<Type_specifierContext>(_ctx, getState());
  enterRule(_localctx, 8, CminusParser::RuleType_specifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(86);
    _la = _input->LA(1);
    if (!(_la == CminusParser::INT

    || _la == CminusParser::VOID)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fun_declarationContext ------------------------------------------------------------------

CminusParser::Fun_declarationContext::Fun_declarationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Type_specifierContext* CminusParser::Fun_declarationContext::type_specifier() {
  return getRuleContext<CminusParser::Type_specifierContext>(0);
}

tree::TerminalNode* CminusParser::Fun_declarationContext::ID() {
  return getToken(CminusParser::ID, 0);
}

tree::TerminalNode* CminusParser::Fun_declarationContext::LPAREN() {
  return getToken(CminusParser::LPAREN, 0);
}

CminusParser::ParamsContext* CminusParser::Fun_declarationContext::params() {
  return getRuleContext<CminusParser::ParamsContext>(0);
}

tree::TerminalNode* CminusParser::Fun_declarationContext::RPAREN() {
  return getToken(CminusParser::RPAREN, 0);
}

CminusParser::Compound_statementContext* CminusParser::Fun_declarationContext::compound_statement() {
  return getRuleContext<CminusParser::Compound_statementContext>(0);
}


size_t CminusParser::Fun_declarationContext::getRuleIndex() const {
  return CminusParser::RuleFun_declaration;
}

void CminusParser::Fun_declarationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFun_declaration(this);
}

void CminusParser::Fun_declarationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFun_declaration(this);
}


antlrcpp::Any CminusParser::Fun_declarationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitFun_declaration(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Fun_declarationContext* CminusParser::fun_declaration() {
  Fun_declarationContext *_localctx = _tracker.createInstance<Fun_declarationContext>(_ctx, getState());
  enterRule(_localctx, 10, CminusParser::RuleFun_declaration);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(88);
    dynamic_cast<Fun_declarationContext *>(_localctx)->type_specifierContext = type_specifier();
    setState(89);
    dynamic_cast<Fun_declarationContext *>(_localctx)->idToken = match(CminusParser::ID);
    setState(90);

    if (!(semantics.canDeclareFunc((dynamic_cast<Fun_declarationContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Fun_declarationContext *>(_localctx)->idToken->getText() : ""), (dynamic_cast<Fun_declarationContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<Fun_declarationContext *>(_localctx)->type_specifierContext->start, dynamic_cast<Fun_declarationContext *>(_localctx)->type_specifierContext->stop) : nullptr)))) throw FailedPredicateException(this, "semantics.canDeclareFunc($ID.text, $type_specifier.text)");
    setState(91);
    match(CminusParser::LPAREN);
    setState(92);
    params();
    setState(93);
    match(CminusParser::RPAREN);
    setState(94);
    compound_statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ParamsContext ------------------------------------------------------------------

CminusParser::ParamsContext::ParamsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Param_listContext* CminusParser::ParamsContext::param_list() {
  return getRuleContext<CminusParser::Param_listContext>(0);
}

tree::TerminalNode* CminusParser::ParamsContext::VOID() {
  return getToken(CminusParser::VOID, 0);
}


size_t CminusParser::ParamsContext::getRuleIndex() const {
  return CminusParser::RuleParams;
}

void CminusParser::ParamsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParams(this);
}

void CminusParser::ParamsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParams(this);
}


antlrcpp::Any CminusParser::ParamsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitParams(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::ParamsContext* CminusParser::params() {
  ParamsContext *_localctx = _tracker.createInstance<ParamsContext>(_ctx, getState());
  enterRule(_localctx, 12, CminusParser::RuleParams);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(100);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(96);
      dynamic_cast<ParamsContext *>(_localctx)->param_listContext = param_list(0);
      semantics.setNumArgs((dynamic_cast<ParamsContext *>(_localctx)->param_listContext != nullptr ? _input->getText(dynamic_cast<ParamsContext *>(_localctx)->param_listContext->start, dynamic_cast<ParamsContext *>(_localctx)->param_listContext->stop) : nullptr));
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(99);
      match(CminusParser::VOID);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Param_listContext ------------------------------------------------------------------

CminusParser::Param_listContext::Param_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::ParamContext* CminusParser::Param_listContext::param() {
  return getRuleContext<CminusParser::ParamContext>(0);
}

CminusParser::Param_listContext* CminusParser::Param_listContext::param_list() {
  return getRuleContext<CminusParser::Param_listContext>(0);
}

tree::TerminalNode* CminusParser::Param_listContext::COMMA() {
  return getToken(CminusParser::COMMA, 0);
}


size_t CminusParser::Param_listContext::getRuleIndex() const {
  return CminusParser::RuleParam_list;
}

void CminusParser::Param_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam_list(this);
}

void CminusParser::Param_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam_list(this);
}


antlrcpp::Any CminusParser::Param_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitParam_list(this);
  else
    return visitor->visitChildren(this);
}


CminusParser::Param_listContext* CminusParser::param_list() {
   return param_list(0);
}

CminusParser::Param_listContext* CminusParser::param_list(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::Param_listContext *_localctx = _tracker.createInstance<Param_listContext>(_ctx, parentState);
  CminusParser::Param_listContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 14;
  enterRecursionRule(_localctx, 14, CminusParser::RuleParam_list, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(103);
    param();
    _ctx->stop = _input->LT(-1);
    setState(110);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Param_listContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleParam_list);
        setState(105);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(106);
        match(CminusParser::COMMA);
        setState(107);
        param(); 
      }
      setState(112);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 4, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ParamContext ------------------------------------------------------------------

CminusParser::ParamContext::ParamContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Type_specifierContext* CminusParser::ParamContext::type_specifier() {
  return getRuleContext<CminusParser::Type_specifierContext>(0);
}

tree::TerminalNode* CminusParser::ParamContext::ID() {
  return getToken(CminusParser::ID, 0);
}

tree::TerminalNode* CminusParser::ParamContext::LBRACKET() {
  return getToken(CminusParser::LBRACKET, 0);
}

tree::TerminalNode* CminusParser::ParamContext::RBRACKET() {
  return getToken(CminusParser::RBRACKET, 0);
}


size_t CminusParser::ParamContext::getRuleIndex() const {
  return CminusParser::RuleParam;
}

void CminusParser::ParamContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParam(this);
}

void CminusParser::ParamContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParam(this);
}


antlrcpp::Any CminusParser::ParamContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitParam(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::ParamContext* CminusParser::param() {
  ParamContext *_localctx = _tracker.createInstance<ParamContext>(_ctx, getState());
  enterRule(_localctx, 16, CminusParser::RuleParam);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(113);
    dynamic_cast<ParamContext *>(_localctx)->type_specifierContext = type_specifier();
    setState(114);

    if (!(semantics.isValidVarType((dynamic_cast<ParamContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<ParamContext *>(_localctx)->type_specifierContext->start, dynamic_cast<ParamContext *>(_localctx)->type_specifierContext->stop) : nullptr)))) throw FailedPredicateException(this, "semantics.isValidVarType($type_specifier.text)");
    setState(115);
    dynamic_cast<ParamContext *>(_localctx)->idToken = match(CminusParser::ID);
    setState(118);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      setState(116);
      match(CminusParser::LBRACKET);
      setState(117);
      match(CminusParser::RBRACKET);
      break;
    }

    default:
      break;
    }
    semantics.addSymbol((dynamic_cast<ParamContext *>(_localctx)->idToken != nullptr ? dynamic_cast<ParamContext *>(_localctx)->idToken->getText() : ""), (dynamic_cast<ParamContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<ParamContext *>(_localctx)->type_specifierContext->start, dynamic_cast<ParamContext *>(_localctx)->type_specifierContext->stop) : nullptr));
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Compound_statementContext ------------------------------------------------------------------

CminusParser::Compound_statementContext::Compound_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Local_declarationsContext* CminusParser::Compound_statementContext::local_declarations() {
  return getRuleContext<CminusParser::Local_declarationsContext>(0);
}

CminusParser::Statement_listContext* CminusParser::Compound_statementContext::statement_list() {
  return getRuleContext<CminusParser::Statement_listContext>(0);
}


size_t CminusParser::Compound_statementContext::getRuleIndex() const {
  return CminusParser::RuleCompound_statement;
}

void CminusParser::Compound_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompound_statement(this);
}

void CminusParser::Compound_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompound_statement(this);
}


antlrcpp::Any CminusParser::Compound_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitCompound_statement(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Compound_statementContext* CminusParser::compound_statement() {
  Compound_statementContext *_localctx = _tracker.createInstance<Compound_statementContext>(_ctx, getState());
  enterRule(_localctx, 18, CminusParser::RuleCompound_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(CminusParser::T__0);
    setState(123);
    local_declarations(0);
    setState(124);
    statement_list(0);
    setState(125);
    match(CminusParser::T__1);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Local_declarationsContext ------------------------------------------------------------------

CminusParser::Local_declarationsContext::Local_declarationsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Local_declarationsContext* CminusParser::Local_declarationsContext::local_declarations() {
  return getRuleContext<CminusParser::Local_declarationsContext>(0);
}

CminusParser::Var_declarationContext* CminusParser::Local_declarationsContext::var_declaration() {
  return getRuleContext<CminusParser::Var_declarationContext>(0);
}


size_t CminusParser::Local_declarationsContext::getRuleIndex() const {
  return CminusParser::RuleLocal_declarations;
}

void CminusParser::Local_declarationsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLocal_declarations(this);
}

void CminusParser::Local_declarationsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLocal_declarations(this);
}


antlrcpp::Any CminusParser::Local_declarationsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitLocal_declarations(this);
  else
    return visitor->visitChildren(this);
}


CminusParser::Local_declarationsContext* CminusParser::local_declarations() {
   return local_declarations(0);
}

CminusParser::Local_declarationsContext* CminusParser::local_declarations(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::Local_declarationsContext *_localctx = _tracker.createInstance<Local_declarationsContext>(_ctx, parentState);
  CminusParser::Local_declarationsContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, CminusParser::RuleLocal_declarations, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _ctx->stop = _input->LT(-1);
    setState(132);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Local_declarationsContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleLocal_declarations);
        setState(128);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(129);
        var_declaration(); 
      }
      setState(134);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Statement_listContext ------------------------------------------------------------------

CminusParser::Statement_listContext::Statement_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Statement_listContext* CminusParser::Statement_listContext::statement_list() {
  return getRuleContext<CminusParser::Statement_listContext>(0);
}

CminusParser::StatementContext* CminusParser::Statement_listContext::statement() {
  return getRuleContext<CminusParser::StatementContext>(0);
}


size_t CminusParser::Statement_listContext::getRuleIndex() const {
  return CminusParser::RuleStatement_list;
}

void CminusParser::Statement_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement_list(this);
}

void CminusParser::Statement_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement_list(this);
}


antlrcpp::Any CminusParser::Statement_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitStatement_list(this);
  else
    return visitor->visitChildren(this);
}


CminusParser::Statement_listContext* CminusParser::statement_list() {
   return statement_list(0);
}

CminusParser::Statement_listContext* CminusParser::statement_list(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::Statement_listContext *_localctx = _tracker.createInstance<Statement_listContext>(_ctx, parentState);
  CminusParser::Statement_listContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 22;
  enterRecursionRule(_localctx, 22, CminusParser::RuleStatement_list, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    _ctx->stop = _input->LT(-1);
    setState(140);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Statement_listContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleStatement_list);
        setState(136);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(137);
        statement(); 
      }
      setState(142);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

CminusParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Expression_statementContext* CminusParser::StatementContext::expression_statement() {
  return getRuleContext<CminusParser::Expression_statementContext>(0);
}

CminusParser::Compound_statementContext* CminusParser::StatementContext::compound_statement() {
  return getRuleContext<CminusParser::Compound_statementContext>(0);
}

CminusParser::Selection_statementContext* CminusParser::StatementContext::selection_statement() {
  return getRuleContext<CminusParser::Selection_statementContext>(0);
}

CminusParser::Iteration_statementContext* CminusParser::StatementContext::iteration_statement() {
  return getRuleContext<CminusParser::Iteration_statementContext>(0);
}

CminusParser::Return_statementContext* CminusParser::StatementContext::return_statement() {
  return getRuleContext<CminusParser::Return_statementContext>(0);
}


size_t CminusParser::StatementContext::getRuleIndex() const {
  return CminusParser::RuleStatement;
}

void CminusParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void CminusParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


antlrcpp::Any CminusParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::StatementContext* CminusParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 24, CminusParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(148);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CminusParser::SEMICOLON:
      case CminusParser::LPAREN:
      case CminusParser::ID:
      case CminusParser::NUM: {
        enterOuterAlt(_localctx, 1);
        setState(143);
        expression_statement();
        break;
      }

      case CminusParser::T__0: {
        enterOuterAlt(_localctx, 2);
        setState(144);
        compound_statement();
        break;
      }

      case CminusParser::IF: {
        enterOuterAlt(_localctx, 3);
        setState(145);
        selection_statement();
        break;
      }

      case CminusParser::WHILE: {
        enterOuterAlt(_localctx, 4);
        setState(146);
        iteration_statement();
        break;
      }

      case CminusParser::RETURN: {
        enterOuterAlt(_localctx, 5);
        setState(147);
        return_statement();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Expression_statementContext ------------------------------------------------------------------

CminusParser::Expression_statementContext::Expression_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Expression_statementContext::SEMICOLON() {
  return getToken(CminusParser::SEMICOLON, 0);
}

CminusParser::ExpressionContext* CminusParser::Expression_statementContext::expression() {
  return getRuleContext<CminusParser::ExpressionContext>(0);
}


size_t CminusParser::Expression_statementContext::getRuleIndex() const {
  return CminusParser::RuleExpression_statement;
}

void CminusParser::Expression_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression_statement(this);
}

void CminusParser::Expression_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression_statement(this);
}


antlrcpp::Any CminusParser::Expression_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitExpression_statement(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Expression_statementContext* CminusParser::expression_statement() {
  Expression_statementContext *_localctx = _tracker.createInstance<Expression_statementContext>(_ctx, getState());
  enterRule(_localctx, 26, CminusParser::RuleExpression_statement);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(151);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CminusParser::LPAREN)
      | (1ULL << CminusParser::ID)
      | (1ULL << CminusParser::NUM))) != 0)) {
      setState(150);
      expression();
    }
    setState(153);
    match(CminusParser::SEMICOLON);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Selection_statementContext ------------------------------------------------------------------

CminusParser::Selection_statementContext::Selection_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Selection_statementContext::IF() {
  return getToken(CminusParser::IF, 0);
}

tree::TerminalNode* CminusParser::Selection_statementContext::LPAREN() {
  return getToken(CminusParser::LPAREN, 0);
}

CminusParser::Simple_expressionContext* CminusParser::Selection_statementContext::simple_expression() {
  return getRuleContext<CminusParser::Simple_expressionContext>(0);
}

tree::TerminalNode* CminusParser::Selection_statementContext::RPAREN() {
  return getToken(CminusParser::RPAREN, 0);
}

std::vector<CminusParser::StatementContext *> CminusParser::Selection_statementContext::statement() {
  return getRuleContexts<CminusParser::StatementContext>();
}

CminusParser::StatementContext* CminusParser::Selection_statementContext::statement(size_t i) {
  return getRuleContext<CminusParser::StatementContext>(i);
}

tree::TerminalNode* CminusParser::Selection_statementContext::ELSE() {
  return getToken(CminusParser::ELSE, 0);
}


size_t CminusParser::Selection_statementContext::getRuleIndex() const {
  return CminusParser::RuleSelection_statement;
}

void CminusParser::Selection_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelection_statement(this);
}

void CminusParser::Selection_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelection_statement(this);
}


antlrcpp::Any CminusParser::Selection_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitSelection_statement(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Selection_statementContext* CminusParser::selection_statement() {
  Selection_statementContext *_localctx = _tracker.createInstance<Selection_statementContext>(_ctx, getState());
  enterRule(_localctx, 28, CminusParser::RuleSelection_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(155);
    match(CminusParser::IF);
    setState(156);
    match(CminusParser::LPAREN);
    setState(157);
    simple_expression();
    setState(158);
    match(CminusParser::RPAREN);
    setState(159);
    statement();
    setState(162);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(160);
      match(CminusParser::ELSE);
      setState(161);
      statement();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Iteration_statementContext ------------------------------------------------------------------

CminusParser::Iteration_statementContext::Iteration_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Iteration_statementContext::WHILE() {
  return getToken(CminusParser::WHILE, 0);
}

tree::TerminalNode* CminusParser::Iteration_statementContext::LPAREN() {
  return getToken(CminusParser::LPAREN, 0);
}

CminusParser::Simple_expressionContext* CminusParser::Iteration_statementContext::simple_expression() {
  return getRuleContext<CminusParser::Simple_expressionContext>(0);
}

tree::TerminalNode* CminusParser::Iteration_statementContext::RPAREN() {
  return getToken(CminusParser::RPAREN, 0);
}

CminusParser::StatementContext* CminusParser::Iteration_statementContext::statement() {
  return getRuleContext<CminusParser::StatementContext>(0);
}


size_t CminusParser::Iteration_statementContext::getRuleIndex() const {
  return CminusParser::RuleIteration_statement;
}

void CminusParser::Iteration_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIteration_statement(this);
}

void CminusParser::Iteration_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIteration_statement(this);
}


antlrcpp::Any CminusParser::Iteration_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitIteration_statement(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Iteration_statementContext* CminusParser::iteration_statement() {
  Iteration_statementContext *_localctx = _tracker.createInstance<Iteration_statementContext>(_ctx, getState());
  enterRule(_localctx, 30, CminusParser::RuleIteration_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(164);
    match(CminusParser::WHILE);
    setState(165);
    match(CminusParser::LPAREN);
    setState(166);
    simple_expression();
    setState(167);
    match(CminusParser::RPAREN);
    setState(168);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Return_statementContext ------------------------------------------------------------------

CminusParser::Return_statementContext::Return_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Return_statementContext::RETURN() {
  return getToken(CminusParser::RETURN, 0);
}

tree::TerminalNode* CminusParser::Return_statementContext::SEMICOLON() {
  return getToken(CminusParser::SEMICOLON, 0);
}

CminusParser::Simple_expressionContext* CminusParser::Return_statementContext::simple_expression() {
  return getRuleContext<CminusParser::Simple_expressionContext>(0);
}


size_t CminusParser::Return_statementContext::getRuleIndex() const {
  return CminusParser::RuleReturn_statement;
}

void CminusParser::Return_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturn_statement(this);
}

void CminusParser::Return_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturn_statement(this);
}


antlrcpp::Any CminusParser::Return_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitReturn_statement(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Return_statementContext* CminusParser::return_statement() {
  Return_statementContext *_localctx = _tracker.createInstance<Return_statementContext>(_ctx, getState());
  enterRule(_localctx, 32, CminusParser::RuleReturn_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(178);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(170);
      match(CminusParser::RETURN);
      setState(171);
      match(CminusParser::SEMICOLON);
      setState(172);

      if (!(semantics.checkReturnType())) throw FailedPredicateException(this, "semantics.checkReturnType()");
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(173);
      match(CminusParser::RETURN);
      setState(174);
      dynamic_cast<Return_statementContext *>(_localctx)->simple_expressionContext = simple_expression();
      setState(175);
      match(CminusParser::SEMICOLON);
      setState(176);

      if (!(semantics.checkReturnType((dynamic_cast<Return_statementContext *>(_localctx)->simple_expressionContext != nullptr ? _input->getText(dynamic_cast<Return_statementContext *>(_localctx)->simple_expressionContext->start, dynamic_cast<Return_statementContext *>(_localctx)->simple_expressionContext->stop) : nullptr)))) throw FailedPredicateException(this, "semantics.checkReturnType($simple_expression.text)");
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpressionContext ------------------------------------------------------------------

CminusParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::VarContext* CminusParser::ExpressionContext::var() {
  return getRuleContext<CminusParser::VarContext>(0);
}

CminusParser::Simple_expressionContext* CminusParser::ExpressionContext::simple_expression() {
  return getRuleContext<CminusParser::Simple_expressionContext>(0);
}


size_t CminusParser::ExpressionContext::getRuleIndex() const {
  return CminusParser::RuleExpression;
}

void CminusParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void CminusParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


antlrcpp::Any CminusParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::ExpressionContext* CminusParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 34, CminusParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(186);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 12, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(180);
      var();
      setState(181);
      match(CminusParser::T__2);
      setState(182);
      dynamic_cast<ExpressionContext *>(_localctx)->simple_expressionContext = simple_expression();
      setState(183);

      if (!(semantics.canReturn((dynamic_cast<ExpressionContext *>(_localctx)->simple_expressionContext != nullptr ? _input->getText(dynamic_cast<ExpressionContext *>(_localctx)->simple_expressionContext->start, dynamic_cast<ExpressionContext *>(_localctx)->simple_expressionContext->stop) : nullptr)))) throw FailedPredicateException(this, "semantics.canReturn($simple_expression.text)");
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(185);
      simple_expression();
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- VarContext ------------------------------------------------------------------

CminusParser::VarContext::VarContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::VarContext::ID() {
  return getToken(CminusParser::ID, 0);
}

tree::TerminalNode* CminusParser::VarContext::LBRACKET() {
  return getToken(CminusParser::LBRACKET, 0);
}

CminusParser::ExpressionContext* CminusParser::VarContext::expression() {
  return getRuleContext<CminusParser::ExpressionContext>(0);
}

tree::TerminalNode* CminusParser::VarContext::RBRACKET() {
  return getToken(CminusParser::RBRACKET, 0);
}


size_t CminusParser::VarContext::getRuleIndex() const {
  return CminusParser::RuleVar;
}

void CminusParser::VarContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar(this);
}

void CminusParser::VarContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar(this);
}


antlrcpp::Any CminusParser::VarContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitVar(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::VarContext* CminusParser::var() {
  VarContext *_localctx = _tracker.createInstance<VarContext>(_ctx, getState());
  enterRule(_localctx, 36, CminusParser::RuleVar);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(188);
    dynamic_cast<VarContext *>(_localctx)->idToken = match(CminusParser::ID);
    setState(193);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(189);
      match(CminusParser::LBRACKET);
      setState(190);
      expression();
      setState(191);
      match(CminusParser::RBRACKET);
      break;
    }

    default:
      break;
    }
    setState(195);

    if (!(semantics.checkSymbol((dynamic_cast<VarContext *>(_localctx)->idToken != nullptr ? dynamic_cast<VarContext *>(_localctx)->idToken->getText() : "")))) throw FailedPredicateException(this, "semantics.checkSymbol($ID.text)");
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Simple_expressionContext ------------------------------------------------------------------

CminusParser::Simple_expressionContext::Simple_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CminusParser::Additive_expressionContext *> CminusParser::Simple_expressionContext::additive_expression() {
  return getRuleContexts<CminusParser::Additive_expressionContext>();
}

CminusParser::Additive_expressionContext* CminusParser::Simple_expressionContext::additive_expression(size_t i) {
  return getRuleContext<CminusParser::Additive_expressionContext>(i);
}

CminusParser::RelopContext* CminusParser::Simple_expressionContext::relop() {
  return getRuleContext<CminusParser::RelopContext>(0);
}


size_t CminusParser::Simple_expressionContext::getRuleIndex() const {
  return CminusParser::RuleSimple_expression;
}

void CminusParser::Simple_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSimple_expression(this);
}

void CminusParser::Simple_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSimple_expression(this);
}


antlrcpp::Any CminusParser::Simple_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitSimple_expression(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Simple_expressionContext* CminusParser::simple_expression() {
  Simple_expressionContext *_localctx = _tracker.createInstance<Simple_expressionContext>(_ctx, getState());
  enterRule(_localctx, 38, CminusParser::RuleSimple_expression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(197);
    additive_expression(0);
    setState(201);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(198);
      relop();
      setState(199);
      additive_expression(0);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RelopContext ------------------------------------------------------------------

CminusParser::RelopContext::RelopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CminusParser::RelopContext::getRuleIndex() const {
  return CminusParser::RuleRelop;
}

void CminusParser::RelopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelop(this);
}

void CminusParser::RelopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelop(this);
}


antlrcpp::Any CminusParser::RelopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitRelop(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::RelopContext* CminusParser::relop() {
  RelopContext *_localctx = _tracker.createInstance<RelopContext>(_ctx, getState());
  enterRule(_localctx, 40, CminusParser::RuleRelop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(203);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CminusParser::T__3)
      | (1ULL << CminusParser::T__4)
      | (1ULL << CminusParser::T__5)
      | (1ULL << CminusParser::T__6)
      | (1ULL << CminusParser::T__7)
      | (1ULL << CminusParser::T__8))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Additive_expressionContext ------------------------------------------------------------------

CminusParser::Additive_expressionContext::Additive_expressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::TermContext* CminusParser::Additive_expressionContext::term() {
  return getRuleContext<CminusParser::TermContext>(0);
}

CminusParser::Additive_expressionContext* CminusParser::Additive_expressionContext::additive_expression() {
  return getRuleContext<CminusParser::Additive_expressionContext>(0);
}

CminusParser::AddopContext* CminusParser::Additive_expressionContext::addop() {
  return getRuleContext<CminusParser::AddopContext>(0);
}


size_t CminusParser::Additive_expressionContext::getRuleIndex() const {
  return CminusParser::RuleAdditive_expression;
}

void CminusParser::Additive_expressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditive_expression(this);
}

void CminusParser::Additive_expressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditive_expression(this);
}


antlrcpp::Any CminusParser::Additive_expressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitAdditive_expression(this);
  else
    return visitor->visitChildren(this);
}


CminusParser::Additive_expressionContext* CminusParser::additive_expression() {
   return additive_expression(0);
}

CminusParser::Additive_expressionContext* CminusParser::additive_expression(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::Additive_expressionContext *_localctx = _tracker.createInstance<Additive_expressionContext>(_ctx, parentState);
  CminusParser::Additive_expressionContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 42;
  enterRecursionRule(_localctx, 42, CminusParser::RuleAdditive_expression, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(206);
    term(0);
    _ctx->stop = _input->LT(-1);
    setState(214);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Additive_expressionContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleAdditive_expression);
        setState(208);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(209);
        addop();
        setState(210);
        term(0); 
      }
      setState(216);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AddopContext ------------------------------------------------------------------

CminusParser::AddopContext::AddopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CminusParser::AddopContext::getRuleIndex() const {
  return CminusParser::RuleAddop;
}

void CminusParser::AddopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAddop(this);
}

void CminusParser::AddopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAddop(this);
}


antlrcpp::Any CminusParser::AddopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitAddop(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::AddopContext* CminusParser::addop() {
  AddopContext *_localctx = _tracker.createInstance<AddopContext>(_ctx, getState());
  enterRule(_localctx, 44, CminusParser::RuleAddop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(217);
    _la = _input->LA(1);
    if (!(_la == CminusParser::T__9

    || _la == CminusParser::T__10)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TermContext ------------------------------------------------------------------

CminusParser::TermContext::TermContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::FactorContext* CminusParser::TermContext::factor() {
  return getRuleContext<CminusParser::FactorContext>(0);
}

CminusParser::TermContext* CminusParser::TermContext::term() {
  return getRuleContext<CminusParser::TermContext>(0);
}

CminusParser::MulopContext* CminusParser::TermContext::mulop() {
  return getRuleContext<CminusParser::MulopContext>(0);
}


size_t CminusParser::TermContext::getRuleIndex() const {
  return CminusParser::RuleTerm;
}

void CminusParser::TermContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTerm(this);
}

void CminusParser::TermContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTerm(this);
}


antlrcpp::Any CminusParser::TermContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitTerm(this);
  else
    return visitor->visitChildren(this);
}


CminusParser::TermContext* CminusParser::term() {
   return term(0);
}

CminusParser::TermContext* CminusParser::term(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::TermContext *_localctx = _tracker.createInstance<TermContext>(_ctx, parentState);
  CminusParser::TermContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 46;
  enterRecursionRule(_localctx, 46, CminusParser::RuleTerm, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(220);
    factor();
    _ctx->stop = _input->LT(-1);
    setState(228);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<TermContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleTerm);
        setState(222);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(223);
        mulop();
        setState(224);
        factor(); 
      }
      setState(230);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- MulopContext ------------------------------------------------------------------

CminusParser::MulopContext::MulopContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CminusParser::MulopContext::getRuleIndex() const {
  return CminusParser::RuleMulop;
}

void CminusParser::MulopContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMulop(this);
}

void CminusParser::MulopContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMulop(this);
}


antlrcpp::Any CminusParser::MulopContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitMulop(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::MulopContext* CminusParser::mulop() {
  MulopContext *_localctx = _tracker.createInstance<MulopContext>(_ctx, getState());
  enterRule(_localctx, 48, CminusParser::RuleMulop);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(231);
    _la = _input->LA(1);
    if (!(_la == CminusParser::T__11

    || _la == CminusParser::T__12)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FactorContext ------------------------------------------------------------------

CminusParser::FactorContext::FactorContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::FactorContext::LPAREN() {
  return getToken(CminusParser::LPAREN, 0);
}

CminusParser::ExpressionContext* CminusParser::FactorContext::expression() {
  return getRuleContext<CminusParser::ExpressionContext>(0);
}

tree::TerminalNode* CminusParser::FactorContext::RPAREN() {
  return getToken(CminusParser::RPAREN, 0);
}

CminusParser::VarContext* CminusParser::FactorContext::var() {
  return getRuleContext<CminusParser::VarContext>(0);
}

CminusParser::CallContext* CminusParser::FactorContext::call() {
  return getRuleContext<CminusParser::CallContext>(0);
}

tree::TerminalNode* CminusParser::FactorContext::NUM() {
  return getToken(CminusParser::NUM, 0);
}


size_t CminusParser::FactorContext::getRuleIndex() const {
  return CminusParser::RuleFactor;
}

void CminusParser::FactorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFactor(this);
}

void CminusParser::FactorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFactor(this);
}


antlrcpp::Any CminusParser::FactorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitFactor(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::FactorContext* CminusParser::factor() {
  FactorContext *_localctx = _tracker.createInstance<FactorContext>(_ctx, getState());
  enterRule(_localctx, 50, CminusParser::RuleFactor);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(240);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 17, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(233);
      match(CminusParser::LPAREN);
      setState(234);
      expression();
      setState(235);
      match(CminusParser::RPAREN);
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(237);
      var();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(238);
      call();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(239);
      match(CminusParser::NUM);
      break;
    }

    default:
      break;
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CallContext ------------------------------------------------------------------

CminusParser::CallContext::CallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::CallContext::ID() {
  return getToken(CminusParser::ID, 0);
}

tree::TerminalNode* CminusParser::CallContext::LPAREN() {
  return getToken(CminusParser::LPAREN, 0);
}

CminusParser::ArgsContext* CminusParser::CallContext::args() {
  return getRuleContext<CminusParser::ArgsContext>(0);
}

tree::TerminalNode* CminusParser::CallContext::RPAREN() {
  return getToken(CminusParser::RPAREN, 0);
}


size_t CminusParser::CallContext::getRuleIndex() const {
  return CminusParser::RuleCall;
}

void CminusParser::CallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall(this);
}

void CminusParser::CallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall(this);
}


antlrcpp::Any CminusParser::CallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitCall(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::CallContext* CminusParser::call() {
  CallContext *_localctx = _tracker.createInstance<CallContext>(_ctx, getState());
  enterRule(_localctx, 52, CminusParser::RuleCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(242);
    dynamic_cast<CallContext *>(_localctx)->idToken = match(CminusParser::ID);
    setState(243);

    if (!(semantics.checkSymbol((dynamic_cast<CallContext *>(_localctx)->idToken != nullptr ? dynamic_cast<CallContext *>(_localctx)->idToken->getText() : "")))) throw FailedPredicateException(this, "semantics.checkSymbol($ID.text)");
    semantics.setCurFuncName((dynamic_cast<CallContext *>(_localctx)->idToken != nullptr ? dynamic_cast<CallContext *>(_localctx)->idToken->getText() : ""));
    setState(245);
    match(CminusParser::LPAREN);
    setState(246);
    args();
    setState(247);
    match(CminusParser::RPAREN);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

CminusParser::ArgsContext::ArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::Arg_listContext* CminusParser::ArgsContext::arg_list() {
  return getRuleContext<CminusParser::Arg_listContext>(0);
}


size_t CminusParser::ArgsContext::getRuleIndex() const {
  return CminusParser::RuleArgs;
}

void CminusParser::ArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgs(this);
}

void CminusParser::ArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgs(this);
}


antlrcpp::Any CminusParser::ArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitArgs(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::ArgsContext* CminusParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 54, CminusParser::RuleArgs);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(253);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CminusParser::LPAREN:
      case CminusParser::ID:
      case CminusParser::NUM: {
        enterOuterAlt(_localctx, 1);
        setState(249);
        dynamic_cast<ArgsContext *>(_localctx)->arg_listContext = arg_list(0);
        setState(250);

        if (!(semantics.isValidNumArgs((dynamic_cast<ArgsContext *>(_localctx)->arg_listContext != nullptr ? _input->getText(dynamic_cast<ArgsContext *>(_localctx)->arg_listContext->start, dynamic_cast<ArgsContext *>(_localctx)->arg_listContext->stop) : nullptr)))) throw FailedPredicateException(this, "semantics.isValidNumArgs($arg_list.text)");
        break;
      }

      case CminusParser::RPAREN: {
        enterOuterAlt(_localctx, 2);

        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Arg_listContext ------------------------------------------------------------------

CminusParser::Arg_listContext::Arg_listContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::ExpressionContext* CminusParser::Arg_listContext::expression() {
  return getRuleContext<CminusParser::ExpressionContext>(0);
}

CminusParser::Arg_listContext* CminusParser::Arg_listContext::arg_list() {
  return getRuleContext<CminusParser::Arg_listContext>(0);
}

tree::TerminalNode* CminusParser::Arg_listContext::COMMA() {
  return getToken(CminusParser::COMMA, 0);
}


size_t CminusParser::Arg_listContext::getRuleIndex() const {
  return CminusParser::RuleArg_list;
}

void CminusParser::Arg_listContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArg_list(this);
}

void CminusParser::Arg_listContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArg_list(this);
}


antlrcpp::Any CminusParser::Arg_listContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitArg_list(this);
  else
    return visitor->visitChildren(this);
}


CminusParser::Arg_listContext* CminusParser::arg_list() {
   return arg_list(0);
}

CminusParser::Arg_listContext* CminusParser::arg_list(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::Arg_listContext *_localctx = _tracker.createInstance<Arg_listContext>(_ctx, parentState);
  CminusParser::Arg_listContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 56;
  enterRecursionRule(_localctx, 56, CminusParser::RuleArg_list, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(256);
    expression();
    _ctx->stop = _input->LT(-1);
    setState(263);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        _localctx = _tracker.createInstance<Arg_listContext>(parentContext, parentState);
        pushNewRecursionContext(_localctx, startState, RuleArg_list);
        setState(258);

        if (!(precpred(_ctx, 2))) throw FailedPredicateException(this, "precpred(_ctx, 2)");
        setState(259);
        match(CminusParser::COMMA);
        setState(260);
        expression(); 
      }
      setState(265);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

bool CminusParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return declaration_listSempred(dynamic_cast<Declaration_listContext *>(context), predicateIndex);
    case 3: return var_declarationSempred(dynamic_cast<Var_declarationContext *>(context), predicateIndex);
    case 5: return fun_declarationSempred(dynamic_cast<Fun_declarationContext *>(context), predicateIndex);
    case 7: return param_listSempred(dynamic_cast<Param_listContext *>(context), predicateIndex);
    case 8: return paramSempred(dynamic_cast<ParamContext *>(context), predicateIndex);
    case 10: return local_declarationsSempred(dynamic_cast<Local_declarationsContext *>(context), predicateIndex);
    case 11: return statement_listSempred(dynamic_cast<Statement_listContext *>(context), predicateIndex);
    case 16: return return_statementSempred(dynamic_cast<Return_statementContext *>(context), predicateIndex);
    case 17: return expressionSempred(dynamic_cast<ExpressionContext *>(context), predicateIndex);
    case 18: return varSempred(dynamic_cast<VarContext *>(context), predicateIndex);
    case 21: return additive_expressionSempred(dynamic_cast<Additive_expressionContext *>(context), predicateIndex);
    case 23: return termSempred(dynamic_cast<TermContext *>(context), predicateIndex);
    case 26: return callSempred(dynamic_cast<CallContext *>(context), predicateIndex);
    case 27: return argsSempred(dynamic_cast<ArgsContext *>(context), predicateIndex);
    case 28: return arg_listSempred(dynamic_cast<Arg_listContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CminusParser::declaration_listSempred(Declaration_listContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CminusParser::var_declarationSempred(Var_declarationContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 1: return semantics.isValidVarType((dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext->start, dynamic_cast<Var_declarationContext *>(_localctx)->type_specifierContext->stop) : nullptr))
    		;

  default:
    break;
  }
  return true;
}

bool CminusParser::fun_declarationSempred(Fun_declarationContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 2: return semantics.canDeclareFunc((dynamic_cast<Fun_declarationContext *>(_localctx)->idToken != nullptr ? dynamic_cast<Fun_declarationContext *>(_localctx)->idToken->getText() : ""), (dynamic_cast<Fun_declarationContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<Fun_declarationContext *>(_localctx)->type_specifierContext->start, dynamic_cast<Fun_declarationContext *>(_localctx)->type_specifierContext->stop) : nullptr));

  default:
    break;
  }
  return true;
}

bool CminusParser::param_listSempred(Param_listContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 3: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CminusParser::paramSempred(ParamContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 4: return semantics.isValidVarType((dynamic_cast<ParamContext *>(_localctx)->type_specifierContext != nullptr ? _input->getText(dynamic_cast<ParamContext *>(_localctx)->type_specifierContext->start, dynamic_cast<ParamContext *>(_localctx)->type_specifierContext->stop) : nullptr));

  default:
    break;
  }
  return true;
}

bool CminusParser::local_declarationsSempred(Local_declarationsContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 5: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CminusParser::statement_listSempred(Statement_listContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 6: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CminusParser::return_statementSempred(Return_statementContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 7: return semantics.checkReturnType();
    case 8: return semantics.checkReturnType((dynamic_cast<Return_statementContext *>(_localctx)->simple_expressionContext != nullptr ? _input->getText(dynamic_cast<Return_statementContext *>(_localctx)->simple_expressionContext->start, dynamic_cast<Return_statementContext *>(_localctx)->simple_expressionContext->stop) : nullptr));

  default:
    break;
  }
  return true;
}

bool CminusParser::expressionSempred(ExpressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 9: return semantics.canReturn((dynamic_cast<ExpressionContext *>(_localctx)->simple_expressionContext != nullptr ? _input->getText(dynamic_cast<ExpressionContext *>(_localctx)->simple_expressionContext->start, dynamic_cast<ExpressionContext *>(_localctx)->simple_expressionContext->stop) : nullptr));

  default:
    break;
  }
  return true;
}

bool CminusParser::varSempred(VarContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 10: return semantics.checkSymbol((dynamic_cast<VarContext *>(_localctx)->idToken != nullptr ? dynamic_cast<VarContext *>(_localctx)->idToken->getText() : ""));

  default:
    break;
  }
  return true;
}

bool CminusParser::additive_expressionSempred(Additive_expressionContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 11: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CminusParser::termSempred(TermContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 12: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

bool CminusParser::callSempred(CallContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 13: return semantics.checkSymbol((dynamic_cast<CallContext *>(_localctx)->idToken != nullptr ? dynamic_cast<CallContext *>(_localctx)->idToken->getText() : ""));

  default:
    break;
  }
  return true;
}

bool CminusParser::argsSempred(ArgsContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 14: return semantics.isValidNumArgs((dynamic_cast<ArgsContext *>(_localctx)->arg_listContext != nullptr ? _input->getText(dynamic_cast<ArgsContext *>(_localctx)->arg_listContext->start, dynamic_cast<ArgsContext *>(_localctx)->arg_listContext->stop) : nullptr));

  default:
    break;
  }
  return true;
}

bool CminusParser::arg_listSempred(Arg_listContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 15: return precpred(_ctx, 2);

  default:
    break;
  }
  return true;
}

// Static vars and initialization.
std::vector<dfa::DFA> CminusParser::_decisionToDFA;
atn::PredictionContextCache CminusParser::_sharedContextCache;

// We own the ATN which in turn owns the ATN states.
atn::ATN CminusParser::_atn;
std::vector<uint16_t> CminusParser::_serializedATN;

std::vector<std::string> CminusParser::_ruleNames = {
  "program", "declaration_list", "declaration", "var_declaration", "type_specifier", 
  "fun_declaration", "params", "param_list", "param", "compound_statement", 
  "local_declarations", "statement_list", "statement", "expression_statement", 
  "selection_statement", "iteration_statement", "return_statement", "expression", 
  "var", "simple_expression", "relop", "additive_expression", "addop", "term", 
  "mulop", "factor", "call", "args", "arg_list"
};

std::vector<std::string> CminusParser::_literalNames = {
  "", "'{'", "'}'", "'='", "'<='", "'<'", "'>'", "'>='", "'=='", "'!='", 
  "'+'", "'-'", "'*'", "'/'", "'if'", "'else'", "'while'", "'return'", "'int'", 
  "'void'", "','", "';'", "'['", "']'", "'('", "')'"
};

std::vector<std::string> CminusParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "IF", "ELSE", 
  "WHILE", "RETURN", "INT", "VOID", "COMMA", "SEMICOLON", "LBRACKET", "RBRACKET", 
  "LPAREN", "RPAREN", "ID", "NUM", "COMMENT", "WS"
};

dfa::Vocabulary CminusParser::_vocabulary(_literalNames, _symbolicNames);

std::vector<std::string> CminusParser::_tokenNames;

CminusParser::Initializer::Initializer() {
	for (size_t i = 0; i < _symbolicNames.size(); ++i) {
		std::string name = _vocabulary.getLiteralName(i);
		if (name.empty()) {
			name = _vocabulary.getSymbolicName(i);
		}

		if (name.empty()) {
			_tokenNames.push_back("<INVALID>");
		} else {
      _tokenNames.push_back(name);
    }
	}

  _serializedATN = {
    0x3, 0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964, 
    0x3, 0x1f, 0x10d, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 
    0x9, 0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 
    0x4, 0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 
    0x9, 0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x4, 0xe, 0x9, 0xe, 
    0x4, 0xf, 0x9, 0xf, 0x4, 0x10, 0x9, 0x10, 0x4, 0x11, 0x9, 0x11, 0x4, 
    0x12, 0x9, 0x12, 0x4, 0x13, 0x9, 0x13, 0x4, 0x14, 0x9, 0x14, 0x4, 0x15, 
    0x9, 0x15, 0x4, 0x16, 0x9, 0x16, 0x4, 0x17, 0x9, 0x17, 0x4, 0x18, 0x9, 
    0x18, 0x4, 0x19, 0x9, 0x19, 0x4, 0x1a, 0x9, 0x1a, 0x4, 0x1b, 0x9, 0x1b, 
    0x4, 0x1c, 0x9, 0x1c, 0x4, 0x1d, 0x9, 0x1d, 0x4, 0x1e, 0x9, 0x1e, 0x3, 
    0x2, 0x3, 0x2, 0x3, 0x2, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 
    0x3, 0x7, 0x3, 0x45, 0xa, 0x3, 0xc, 0x3, 0xe, 0x3, 0x48, 0xb, 0x3, 0x3, 
    0x4, 0x3, 0x4, 0x5, 0x4, 0x4c, 0xa, 0x4, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 
    0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x53, 0xa, 0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 
    0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x8, 0x3, 0x8, 0x3, 
    0x8, 0x3, 0x8, 0x5, 0x8, 0x67, 0xa, 0x8, 0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0x9, 0x3, 0x9, 0x7, 0x9, 0x6f, 0xa, 0x9, 0xc, 0x9, 0xe, 
    0x9, 0x72, 0xb, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 
    0x5, 0xa, 0x79, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x85, 
    0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0x88, 0xb, 0xc, 0x3, 0xd, 0x3, 0xd, 0x3, 
    0xd, 0x7, 0xd, 0x8d, 0xa, 0xd, 0xc, 0xd, 0xe, 0xd, 0x90, 0xb, 0xd, 0x3, 
    0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x3, 0xe, 0x5, 0xe, 0x97, 0xa, 0xe, 
    0x3, 0xf, 0x5, 0xf, 0x9a, 0xa, 0xf, 0x3, 0xf, 0x3, 0xf, 0x3, 0x10, 0x3, 
    0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x3, 0x10, 0x5, 0x10, 
    0xa5, 0xa, 0x10, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 0x3, 0x11, 
    0x3, 0x11, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 0x12, 0x3, 
    0x12, 0x3, 0x12, 0x3, 0x12, 0x5, 0x12, 0xb5, 0xa, 0x12, 0x3, 0x13, 0x3, 
    0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x3, 0x13, 0x5, 0x13, 0xbd, 0xa, 
    0x13, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x14, 0x5, 0x14, 
    0xc4, 0xa, 0x14, 0x3, 0x14, 0x3, 0x14, 0x3, 0x15, 0x3, 0x15, 0x3, 0x15, 
    0x3, 0x15, 0x5, 0x15, 0xcc, 0xa, 0x15, 0x3, 0x16, 0x3, 0x16, 0x3, 0x17, 
    0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x3, 0x17, 0x7, 
    0x17, 0xd7, 0xa, 0x17, 0xc, 0x17, 0xe, 0x17, 0xda, 0xb, 0x17, 0x3, 0x18, 
    0x3, 0x18, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 0x19, 0x3, 
    0x19, 0x3, 0x19, 0x7, 0x19, 0xe5, 0xa, 0x19, 0xc, 0x19, 0xe, 0x19, 0xe8, 
    0xb, 0x19, 0x3, 0x1a, 0x3, 0x1a, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 
    0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x3, 0x1b, 0x5, 0x1b, 0xf3, 0xa, 0x1b, 0x3, 
    0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 0x3, 0x1c, 
    0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x3, 0x1d, 0x5, 0x1d, 0x100, 0xa, 0x1d, 
    0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x3, 0x1e, 0x7, 
    0x1e, 0x108, 0xa, 0x1e, 0xc, 0x1e, 0xe, 0x1e, 0x10b, 0xb, 0x1e, 0x3, 
    0x1e, 0x2, 0x9, 0x4, 0x10, 0x16, 0x18, 0x2c, 0x30, 0x3a, 0x1f, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 
    0x1e, 0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 
    0x36, 0x38, 0x3a, 0x2, 0x6, 0x3, 0x2, 0x14, 0x15, 0x3, 0x2, 0x6, 0xb, 
    0x3, 0x2, 0xc, 0xd, 0x3, 0x2, 0xe, 0xf, 0x2, 0x108, 0x2, 0x3c, 0x3, 
    0x2, 0x2, 0x2, 0x4, 0x3f, 0x3, 0x2, 0x2, 0x2, 0x6, 0x4b, 0x3, 0x2, 0x2, 
    0x2, 0x8, 0x4d, 0x3, 0x2, 0x2, 0x2, 0xa, 0x58, 0x3, 0x2, 0x2, 0x2, 0xc, 
    0x5a, 0x3, 0x2, 0x2, 0x2, 0xe, 0x66, 0x3, 0x2, 0x2, 0x2, 0x10, 0x68, 
    0x3, 0x2, 0x2, 0x2, 0x12, 0x73, 0x3, 0x2, 0x2, 0x2, 0x14, 0x7c, 0x3, 
    0x2, 0x2, 0x2, 0x16, 0x81, 0x3, 0x2, 0x2, 0x2, 0x18, 0x89, 0x3, 0x2, 
    0x2, 0x2, 0x1a, 0x96, 0x3, 0x2, 0x2, 0x2, 0x1c, 0x99, 0x3, 0x2, 0x2, 
    0x2, 0x1e, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x20, 0xa6, 0x3, 0x2, 0x2, 0x2, 
    0x22, 0xb4, 0x3, 0x2, 0x2, 0x2, 0x24, 0xbc, 0x3, 0x2, 0x2, 0x2, 0x26, 
    0xbe, 0x3, 0x2, 0x2, 0x2, 0x28, 0xc7, 0x3, 0x2, 0x2, 0x2, 0x2a, 0xcd, 
    0x3, 0x2, 0x2, 0x2, 0x2c, 0xcf, 0x3, 0x2, 0x2, 0x2, 0x2e, 0xdb, 0x3, 
    0x2, 0x2, 0x2, 0x30, 0xdd, 0x3, 0x2, 0x2, 0x2, 0x32, 0xe9, 0x3, 0x2, 
    0x2, 0x2, 0x34, 0xf2, 0x3, 0x2, 0x2, 0x2, 0x36, 0xf4, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0xff, 0x3, 0x2, 0x2, 0x2, 0x3a, 0x101, 0x3, 0x2, 0x2, 0x2, 
    0x3c, 0x3d, 0x5, 0x4, 0x3, 0x2, 0x3d, 0x3e, 0x7, 0x2, 0x2, 0x3, 0x3e, 
    0x3, 0x3, 0x2, 0x2, 0x2, 0x3f, 0x40, 0x8, 0x3, 0x1, 0x2, 0x40, 0x41, 
    0x5, 0x6, 0x4, 0x2, 0x41, 0x46, 0x3, 0x2, 0x2, 0x2, 0x42, 0x43, 0xc, 
    0x4, 0x2, 0x2, 0x43, 0x45, 0x5, 0x6, 0x4, 0x2, 0x44, 0x42, 0x3, 0x2, 
    0x2, 0x2, 0x45, 0x48, 0x3, 0x2, 0x2, 0x2, 0x46, 0x44, 0x3, 0x2, 0x2, 
    0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 0x5, 0x3, 0x2, 0x2, 0x2, 
    0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4c, 0x5, 0x8, 0x5, 0x2, 0x4a, 
    0x4c, 0x5, 0xc, 0x7, 0x2, 0x4b, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4a, 
    0x3, 0x2, 0x2, 0x2, 0x4c, 0x7, 0x3, 0x2, 0x2, 0x2, 0x4d, 0x4e, 0x5, 
    0xa, 0x6, 0x2, 0x4e, 0x52, 0x7, 0x1c, 0x2, 0x2, 0x4f, 0x50, 0x7, 0x18, 
    0x2, 0x2, 0x50, 0x51, 0x7, 0x1d, 0x2, 0x2, 0x51, 0x53, 0x7, 0x19, 0x2, 
    0x2, 0x52, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x52, 0x53, 0x3, 0x2, 0x2, 0x2, 
    0x53, 0x54, 0x3, 0x2, 0x2, 0x2, 0x54, 0x55, 0x7, 0x17, 0x2, 0x2, 0x55, 
    0x56, 0x6, 0x5, 0x3, 0x3, 0x56, 0x57, 0x8, 0x5, 0x1, 0x2, 0x57, 0x9, 
    0x3, 0x2, 0x2, 0x2, 0x58, 0x59, 0x9, 0x2, 0x2, 0x2, 0x59, 0xb, 0x3, 
    0x2, 0x2, 0x2, 0x5a, 0x5b, 0x5, 0xa, 0x6, 0x2, 0x5b, 0x5c, 0x7, 0x1c, 
    0x2, 0x2, 0x5c, 0x5d, 0x6, 0x7, 0x4, 0x3, 0x5d, 0x5e, 0x7, 0x1a, 0x2, 
    0x2, 0x5e, 0x5f, 0x5, 0xe, 0x8, 0x2, 0x5f, 0x60, 0x7, 0x1b, 0x2, 0x2, 
    0x60, 0x61, 0x5, 0x14, 0xb, 0x2, 0x61, 0xd, 0x3, 0x2, 0x2, 0x2, 0x62, 
    0x63, 0x5, 0x10, 0x9, 0x2, 0x63, 0x64, 0x8, 0x8, 0x1, 0x2, 0x64, 0x67, 
    0x3, 0x2, 0x2, 0x2, 0x65, 0x67, 0x7, 0x15, 0x2, 0x2, 0x66, 0x62, 0x3, 
    0x2, 0x2, 0x2, 0x66, 0x65, 0x3, 0x2, 0x2, 0x2, 0x67, 0xf, 0x3, 0x2, 
    0x2, 0x2, 0x68, 0x69, 0x8, 0x9, 0x1, 0x2, 0x69, 0x6a, 0x5, 0x12, 0xa, 
    0x2, 0x6a, 0x70, 0x3, 0x2, 0x2, 0x2, 0x6b, 0x6c, 0xc, 0x4, 0x2, 0x2, 
    0x6c, 0x6d, 0x7, 0x16, 0x2, 0x2, 0x6d, 0x6f, 0x5, 0x12, 0xa, 0x2, 0x6e, 
    0x6b, 0x3, 0x2, 0x2, 0x2, 0x6f, 0x72, 0x3, 0x2, 0x2, 0x2, 0x70, 0x6e, 
    0x3, 0x2, 0x2, 0x2, 0x70, 0x71, 0x3, 0x2, 0x2, 0x2, 0x71, 0x11, 0x3, 
    0x2, 0x2, 0x2, 0x72, 0x70, 0x3, 0x2, 0x2, 0x2, 0x73, 0x74, 0x5, 0xa, 
    0x6, 0x2, 0x74, 0x75, 0x6, 0xa, 0x6, 0x3, 0x75, 0x78, 0x7, 0x1c, 0x2, 
    0x2, 0x76, 0x77, 0x7, 0x18, 0x2, 0x2, 0x77, 0x79, 0x7, 0x19, 0x2, 0x2, 
    0x78, 0x76, 0x3, 0x2, 0x2, 0x2, 0x78, 0x79, 0x3, 0x2, 0x2, 0x2, 0x79, 
    0x7a, 0x3, 0x2, 0x2, 0x2, 0x7a, 0x7b, 0x8, 0xa, 0x1, 0x2, 0x7b, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x7c, 0x7d, 0x7, 0x3, 0x2, 0x2, 0x7d, 0x7e, 0x5, 
    0x16, 0xc, 0x2, 0x7e, 0x7f, 0x5, 0x18, 0xd, 0x2, 0x7f, 0x80, 0x7, 0x4, 
    0x2, 0x2, 0x80, 0x15, 0x3, 0x2, 0x2, 0x2, 0x81, 0x86, 0x8, 0xc, 0x1, 
    0x2, 0x82, 0x83, 0xc, 0x4, 0x2, 0x2, 0x83, 0x85, 0x5, 0x8, 0x5, 0x2, 
    0x84, 0x82, 0x3, 0x2, 0x2, 0x2, 0x85, 0x88, 0x3, 0x2, 0x2, 0x2, 0x86, 
    0x84, 0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x3, 0x2, 0x2, 0x2, 0x87, 0x17, 
    0x3, 0x2, 0x2, 0x2, 0x88, 0x86, 0x3, 0x2, 0x2, 0x2, 0x89, 0x8e, 0x8, 
    0xd, 0x1, 0x2, 0x8a, 0x8b, 0xc, 0x4, 0x2, 0x2, 0x8b, 0x8d, 0x5, 0x1a, 
    0xe, 0x2, 0x8c, 0x8a, 0x3, 0x2, 0x2, 0x2, 0x8d, 0x90, 0x3, 0x2, 0x2, 
    0x2, 0x8e, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x8f, 0x3, 0x2, 0x2, 0x2, 
    0x8f, 0x19, 0x3, 0x2, 0x2, 0x2, 0x90, 0x8e, 0x3, 0x2, 0x2, 0x2, 0x91, 
    0x97, 0x5, 0x1c, 0xf, 0x2, 0x92, 0x97, 0x5, 0x14, 0xb, 0x2, 0x93, 0x97, 
    0x5, 0x1e, 0x10, 0x2, 0x94, 0x97, 0x5, 0x20, 0x11, 0x2, 0x95, 0x97, 
    0x5, 0x22, 0x12, 0x2, 0x96, 0x91, 0x3, 0x2, 0x2, 0x2, 0x96, 0x92, 0x3, 
    0x2, 0x2, 0x2, 0x96, 0x93, 0x3, 0x2, 0x2, 0x2, 0x96, 0x94, 0x3, 0x2, 
    0x2, 0x2, 0x96, 0x95, 0x3, 0x2, 0x2, 0x2, 0x97, 0x1b, 0x3, 0x2, 0x2, 
    0x2, 0x98, 0x9a, 0x5, 0x24, 0x13, 0x2, 0x99, 0x98, 0x3, 0x2, 0x2, 0x2, 
    0x99, 0x9a, 0x3, 0x2, 0x2, 0x2, 0x9a, 0x9b, 0x3, 0x2, 0x2, 0x2, 0x9b, 
    0x9c, 0x7, 0x17, 0x2, 0x2, 0x9c, 0x1d, 0x3, 0x2, 0x2, 0x2, 0x9d, 0x9e, 
    0x7, 0x10, 0x2, 0x2, 0x9e, 0x9f, 0x7, 0x1a, 0x2, 0x2, 0x9f, 0xa0, 0x5, 
    0x28, 0x15, 0x2, 0xa0, 0xa1, 0x7, 0x1b, 0x2, 0x2, 0xa1, 0xa4, 0x5, 0x1a, 
    0xe, 0x2, 0xa2, 0xa3, 0x7, 0x11, 0x2, 0x2, 0xa3, 0xa5, 0x5, 0x1a, 0xe, 
    0x2, 0xa4, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xa5, 0x3, 0x2, 0x2, 0x2, 
    0xa5, 0x1f, 0x3, 0x2, 0x2, 0x2, 0xa6, 0xa7, 0x7, 0x12, 0x2, 0x2, 0xa7, 
    0xa8, 0x7, 0x1a, 0x2, 0x2, 0xa8, 0xa9, 0x5, 0x28, 0x15, 0x2, 0xa9, 0xaa, 
    0x7, 0x1b, 0x2, 0x2, 0xaa, 0xab, 0x5, 0x1a, 0xe, 0x2, 0xab, 0x21, 0x3, 
    0x2, 0x2, 0x2, 0xac, 0xad, 0x7, 0x13, 0x2, 0x2, 0xad, 0xae, 0x7, 0x17, 
    0x2, 0x2, 0xae, 0xb5, 0x6, 0x12, 0x9, 0x2, 0xaf, 0xb0, 0x7, 0x13, 0x2, 
    0x2, 0xb0, 0xb1, 0x5, 0x28, 0x15, 0x2, 0xb1, 0xb2, 0x7, 0x17, 0x2, 0x2, 
    0xb2, 0xb3, 0x6, 0x12, 0xa, 0x3, 0xb3, 0xb5, 0x3, 0x2, 0x2, 0x2, 0xb4, 
    0xac, 0x3, 0x2, 0x2, 0x2, 0xb4, 0xaf, 0x3, 0x2, 0x2, 0x2, 0xb5, 0x23, 
    0x3, 0x2, 0x2, 0x2, 0xb6, 0xb7, 0x5, 0x26, 0x14, 0x2, 0xb7, 0xb8, 0x7, 
    0x5, 0x2, 0x2, 0xb8, 0xb9, 0x5, 0x28, 0x15, 0x2, 0xb9, 0xba, 0x6, 0x13, 
    0xb, 0x3, 0xba, 0xbd, 0x3, 0x2, 0x2, 0x2, 0xbb, 0xbd, 0x5, 0x28, 0x15, 
    0x2, 0xbc, 0xb6, 0x3, 0x2, 0x2, 0x2, 0xbc, 0xbb, 0x3, 0x2, 0x2, 0x2, 
    0xbd, 0x25, 0x3, 0x2, 0x2, 0x2, 0xbe, 0xc3, 0x7, 0x1c, 0x2, 0x2, 0xbf, 
    0xc0, 0x7, 0x18, 0x2, 0x2, 0xc0, 0xc1, 0x5, 0x24, 0x13, 0x2, 0xc1, 0xc2, 
    0x7, 0x19, 0x2, 0x2, 0xc2, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xc3, 0xbf, 0x3, 
    0x2, 0x2, 0x2, 0xc3, 0xc4, 0x3, 0x2, 0x2, 0x2, 0xc4, 0xc5, 0x3, 0x2, 
    0x2, 0x2, 0xc5, 0xc6, 0x6, 0x14, 0xc, 0x3, 0xc6, 0x27, 0x3, 0x2, 0x2, 
    0x2, 0xc7, 0xcb, 0x5, 0x2c, 0x17, 0x2, 0xc8, 0xc9, 0x5, 0x2a, 0x16, 
    0x2, 0xc9, 0xca, 0x5, 0x2c, 0x17, 0x2, 0xca, 0xcc, 0x3, 0x2, 0x2, 0x2, 
    0xcb, 0xc8, 0x3, 0x2, 0x2, 0x2, 0xcb, 0xcc, 0x3, 0x2, 0x2, 0x2, 0xcc, 
    0x29, 0x3, 0x2, 0x2, 0x2, 0xcd, 0xce, 0x9, 0x3, 0x2, 0x2, 0xce, 0x2b, 
    0x3, 0x2, 0x2, 0x2, 0xcf, 0xd0, 0x8, 0x17, 0x1, 0x2, 0xd0, 0xd1, 0x5, 
    0x30, 0x19, 0x2, 0xd1, 0xd8, 0x3, 0x2, 0x2, 0x2, 0xd2, 0xd3, 0xc, 0x4, 
    0x2, 0x2, 0xd3, 0xd4, 0x5, 0x2e, 0x18, 0x2, 0xd4, 0xd5, 0x5, 0x30, 0x19, 
    0x2, 0xd5, 0xd7, 0x3, 0x2, 0x2, 0x2, 0xd6, 0xd2, 0x3, 0x2, 0x2, 0x2, 
    0xd7, 0xda, 0x3, 0x2, 0x2, 0x2, 0xd8, 0xd6, 0x3, 0x2, 0x2, 0x2, 0xd8, 
    0xd9, 0x3, 0x2, 0x2, 0x2, 0xd9, 0x2d, 0x3, 0x2, 0x2, 0x2, 0xda, 0xd8, 
    0x3, 0x2, 0x2, 0x2, 0xdb, 0xdc, 0x9, 0x4, 0x2, 0x2, 0xdc, 0x2f, 0x3, 
    0x2, 0x2, 0x2, 0xdd, 0xde, 0x8, 0x19, 0x1, 0x2, 0xde, 0xdf, 0x5, 0x34, 
    0x1b, 0x2, 0xdf, 0xe6, 0x3, 0x2, 0x2, 0x2, 0xe0, 0xe1, 0xc, 0x4, 0x2, 
    0x2, 0xe1, 0xe2, 0x5, 0x32, 0x1a, 0x2, 0xe2, 0xe3, 0x5, 0x34, 0x1b, 
    0x2, 0xe3, 0xe5, 0x3, 0x2, 0x2, 0x2, 0xe4, 0xe0, 0x3, 0x2, 0x2, 0x2, 
    0xe5, 0xe8, 0x3, 0x2, 0x2, 0x2, 0xe6, 0xe4, 0x3, 0x2, 0x2, 0x2, 0xe6, 
    0xe7, 0x3, 0x2, 0x2, 0x2, 0xe7, 0x31, 0x3, 0x2, 0x2, 0x2, 0xe8, 0xe6, 
    0x3, 0x2, 0x2, 0x2, 0xe9, 0xea, 0x9, 0x5, 0x2, 0x2, 0xea, 0x33, 0x3, 
    0x2, 0x2, 0x2, 0xeb, 0xec, 0x7, 0x1a, 0x2, 0x2, 0xec, 0xed, 0x5, 0x24, 
    0x13, 0x2, 0xed, 0xee, 0x7, 0x1b, 0x2, 0x2, 0xee, 0xf3, 0x3, 0x2, 0x2, 
    0x2, 0xef, 0xf3, 0x5, 0x26, 0x14, 0x2, 0xf0, 0xf3, 0x5, 0x36, 0x1c, 
    0x2, 0xf1, 0xf3, 0x7, 0x1d, 0x2, 0x2, 0xf2, 0xeb, 0x3, 0x2, 0x2, 0x2, 
    0xf2, 0xef, 0x3, 0x2, 0x2, 0x2, 0xf2, 0xf0, 0x3, 0x2, 0x2, 0x2, 0xf2, 
    0xf1, 0x3, 0x2, 0x2, 0x2, 0xf3, 0x35, 0x3, 0x2, 0x2, 0x2, 0xf4, 0xf5, 
    0x7, 0x1c, 0x2, 0x2, 0xf5, 0xf6, 0x6, 0x1c, 0xf, 0x3, 0xf6, 0xf7, 0x8, 
    0x1c, 0x1, 0x2, 0xf7, 0xf8, 0x7, 0x1a, 0x2, 0x2, 0xf8, 0xf9, 0x5, 0x38, 
    0x1d, 0x2, 0xf9, 0xfa, 0x7, 0x1b, 0x2, 0x2, 0xfa, 0x37, 0x3, 0x2, 0x2, 
    0x2, 0xfb, 0xfc, 0x5, 0x3a, 0x1e, 0x2, 0xfc, 0xfd, 0x6, 0x1d, 0x10, 
    0x3, 0xfd, 0x100, 0x3, 0x2, 0x2, 0x2, 0xfe, 0x100, 0x3, 0x2, 0x2, 0x2, 
    0xff, 0xfb, 0x3, 0x2, 0x2, 0x2, 0xff, 0xfe, 0x3, 0x2, 0x2, 0x2, 0x100, 
    0x39, 0x3, 0x2, 0x2, 0x2, 0x101, 0x102, 0x8, 0x1e, 0x1, 0x2, 0x102, 
    0x103, 0x5, 0x24, 0x13, 0x2, 0x103, 0x109, 0x3, 0x2, 0x2, 0x2, 0x104, 
    0x105, 0xc, 0x4, 0x2, 0x2, 0x105, 0x106, 0x7, 0x16, 0x2, 0x2, 0x106, 
    0x108, 0x5, 0x24, 0x13, 0x2, 0x107, 0x104, 0x3, 0x2, 0x2, 0x2, 0x108, 
    0x10b, 0x3, 0x2, 0x2, 0x2, 0x109, 0x107, 0x3, 0x2, 0x2, 0x2, 0x109, 
    0x10a, 0x3, 0x2, 0x2, 0x2, 0x10a, 0x3b, 0x3, 0x2, 0x2, 0x2, 0x10b, 0x109, 
    0x3, 0x2, 0x2, 0x2, 0x16, 0x46, 0x4b, 0x52, 0x66, 0x70, 0x78, 0x86, 
    0x8e, 0x96, 0x99, 0xa4, 0xb4, 0xbc, 0xc3, 0xcb, 0xd8, 0xe6, 0xf2, 0xff, 
    0x109, 
  };

  atn::ATNDeserializer deserializer;
  _atn = deserializer.deserialize(_serializedATN);

  size_t count = _atn.getNumberOfDecisions();
  _decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    _decisionToDFA.emplace_back(_atn.getDecisionState(i), i);
  }
}

CminusParser::Initializer CminusParser::_init;
