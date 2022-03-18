
// Generated from /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4 by ANTLR 4.9


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

tree::TerminalNode* CminusParser::ProgramContext::EOF() {
  return getToken(CminusParser::EOF, 0);
}

std::vector<CminusParser::Var_declerationContext *> CminusParser::ProgramContext::var_decleration() {
  return getRuleContexts<CminusParser::Var_declerationContext>();
}

CminusParser::Var_declerationContext* CminusParser::ProgramContext::var_decleration(size_t i) {
  return getRuleContext<CminusParser::Var_declerationContext>(i);
}

std::vector<CminusParser::Fun_declerationContext *> CminusParser::ProgramContext::fun_decleration() {
  return getRuleContexts<CminusParser::Fun_declerationContext>();
}

CminusParser::Fun_declerationContext* CminusParser::ProgramContext::fun_decleration(size_t i) {
  return getRuleContext<CminusParser::Fun_declerationContext>(i);
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
    setState(26); 
    _errHandler->sync(this);
    _la = _input->LA(1);
    do {
      setState(26);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 0, _ctx)) {
      case 1: {
        setState(24);
        var_decleration();
        break;
      }

      case 2: {
        setState(25);
        fun_decleration();
        break;
      }

      default:
        break;
      }
      setState(28); 
      _errHandler->sync(this);
      _la = _input->LA(1);
    } while (_la == CminusParser::T__0

    || _la == CminusParser::T__4);
    setState(30);
    match(CminusParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Var_declerationContext ------------------------------------------------------------------

CminusParser::Var_declerationContext::Var_declerationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Var_declerationContext::ID() {
  return getToken(CminusParser::ID, 0);
}

tree::TerminalNode* CminusParser::Var_declerationContext::NUM() {
  return getToken(CminusParser::NUM, 0);
}


size_t CminusParser::Var_declerationContext::getRuleIndex() const {
  return CminusParser::RuleVar_decleration;
}

void CminusParser::Var_declerationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVar_decleration(this);
}

void CminusParser::Var_declerationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVar_decleration(this);
}


antlrcpp::Any CminusParser::Var_declerationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitVar_decleration(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Var_declerationContext* CminusParser::var_decleration() {
  Var_declerationContext *_localctx = _tracker.createInstance<Var_declerationContext>(_ctx, getState());
  enterRule(_localctx, 2, CminusParser::RuleVar_decleration);
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
    setState(32);
    match(CminusParser::T__0);
    setState(33);
    match(CminusParser::ID);
    setState(37);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CminusParser::T__1) {
      setState(34);
      match(CminusParser::T__1);
      setState(35);
      match(CminusParser::NUM);
      setState(36);
      match(CminusParser::T__2);
    }
    setState(39);
    match(CminusParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Fun_declerationContext ------------------------------------------------------------------

CminusParser::Fun_declerationContext::Fun_declerationContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Fun_declerationContext::ID() {
  return getToken(CminusParser::ID, 0);
}

CminusParser::Compound_stmtContext* CminusParser::Fun_declerationContext::compound_stmt() {
  return getRuleContext<CminusParser::Compound_stmtContext>(0);
}

std::vector<CminusParser::ParamContext *> CminusParser::Fun_declerationContext::param() {
  return getRuleContexts<CminusParser::ParamContext>();
}

CminusParser::ParamContext* CminusParser::Fun_declerationContext::param(size_t i) {
  return getRuleContext<CminusParser::ParamContext>(i);
}


size_t CminusParser::Fun_declerationContext::getRuleIndex() const {
  return CminusParser::RuleFun_decleration;
}

void CminusParser::Fun_declerationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFun_decleration(this);
}

void CminusParser::Fun_declerationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFun_decleration(this);
}


antlrcpp::Any CminusParser::Fun_declerationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitFun_decleration(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Fun_declerationContext* CminusParser::fun_decleration() {
  Fun_declerationContext *_localctx = _tracker.createInstance<Fun_declerationContext>(_ctx, getState());
  enterRule(_localctx, 4, CminusParser::RuleFun_decleration);
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
    setState(41);
    _la = _input->LA(1);
    if (!(_la == CminusParser::T__0

    || _la == CminusParser::T__4)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(42);
    match(CminusParser::ID);
    setState(43);
    match(CminusParser::T__5);
    setState(53);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case CminusParser::T__0: {
        setState(44);
        param();
        setState(49);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CminusParser::T__6) {
          setState(45);
          match(CminusParser::T__6);
          setState(46);
          param();
          setState(51);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
        break;
      }

      case CminusParser::T__4: {
        setState(52);
        match(CminusParser::T__4);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    setState(55);
    match(CminusParser::T__7);
    setState(56);
    compound_stmt();
   
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

tree::TerminalNode* CminusParser::ParamContext::ID() {
  return getToken(CminusParser::ID, 0);
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
  enterRule(_localctx, 6, CminusParser::RuleParam);
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
    setState(58);
    match(CminusParser::T__0);
    setState(59);
    match(CminusParser::ID);
    setState(62);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CminusParser::T__1) {
      setState(60);
      match(CminusParser::T__1);
      setState(61);
      match(CminusParser::T__2);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Compound_stmtContext ------------------------------------------------------------------

CminusParser::Compound_stmtContext::Compound_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CminusParser::Var_declerationContext *> CminusParser::Compound_stmtContext::var_decleration() {
  return getRuleContexts<CminusParser::Var_declerationContext>();
}

CminusParser::Var_declerationContext* CminusParser::Compound_stmtContext::var_decleration(size_t i) {
  return getRuleContext<CminusParser::Var_declerationContext>(i);
}

std::vector<CminusParser::StatementContext *> CminusParser::Compound_stmtContext::statement() {
  return getRuleContexts<CminusParser::StatementContext>();
}

CminusParser::StatementContext* CminusParser::Compound_stmtContext::statement(size_t i) {
  return getRuleContext<CminusParser::StatementContext>(i);
}


size_t CminusParser::Compound_stmtContext::getRuleIndex() const {
  return CminusParser::RuleCompound_stmt;
}

void CminusParser::Compound_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCompound_stmt(this);
}

void CminusParser::Compound_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCompound_stmt(this);
}


antlrcpp::Any CminusParser::Compound_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitCompound_stmt(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Compound_stmtContext* CminusParser::compound_stmt() {
  Compound_stmtContext *_localctx = _tracker.createInstance<Compound_stmtContext>(_ctx, getState());
  enterRule(_localctx, 8, CminusParser::RuleCompound_stmt);
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
    setState(64);
    match(CminusParser::T__8);
    setState(68);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == CminusParser::T__0) {
      setState(65);
      var_decleration();
      setState(70);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(74);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CminusParser::T__3)
      | (1ULL << CminusParser::T__5)
      | (1ULL << CminusParser::T__8)
      | (1ULL << CminusParser::T__10)
      | (1ULL << CminusParser::T__12)
      | (1ULL << CminusParser::T__14)
      | (1ULL << CminusParser::ID)
      | (1ULL << CminusParser::NUM))) != 0)) {
      setState(71);
      statement();
      setState(76);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(77);
    match(CminusParser::T__9);
   
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

CminusParser::Compound_stmtContext* CminusParser::StatementContext::compound_stmt() {
  return getRuleContext<CminusParser::Compound_stmtContext>(0);
}

CminusParser::Selection_stmtContext* CminusParser::StatementContext::selection_stmt() {
  return getRuleContext<CminusParser::Selection_stmtContext>(0);
}

CminusParser::Iteration_stmtContext* CminusParser::StatementContext::iteration_stmt() {
  return getRuleContext<CminusParser::Iteration_stmtContext>(0);
}

CminusParser::Assignment_stmtContext* CminusParser::StatementContext::assignment_stmt() {
  return getRuleContext<CminusParser::Assignment_stmtContext>(0);
}

CminusParser::Return_stmtContext* CminusParser::StatementContext::return_stmt() {
  return getRuleContext<CminusParser::Return_stmtContext>(0);
}

CminusParser::ExpContext* CminusParser::StatementContext::exp() {
  return getRuleContext<CminusParser::ExpContext>(0);
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
  enterRule(_localctx, 10, CminusParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(88);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 8, _ctx)) {
    case 1: {
      enterOuterAlt(_localctx, 1);
      setState(79);
      compound_stmt();
      break;
    }

    case 2: {
      enterOuterAlt(_localctx, 2);
      setState(80);
      selection_stmt();
      break;
    }

    case 3: {
      enterOuterAlt(_localctx, 3);
      setState(81);
      iteration_stmt();
      break;
    }

    case 4: {
      enterOuterAlt(_localctx, 4);
      setState(82);
      assignment_stmt();
      break;
    }

    case 5: {
      enterOuterAlt(_localctx, 5);
      setState(83);
      return_stmt();
      break;
    }

    case 6: {
      enterOuterAlt(_localctx, 6);
      setState(84);
      exp(0);
      setState(85);
      match(CminusParser::T__3);
      break;
    }

    case 7: {
      enterOuterAlt(_localctx, 7);
      setState(87);
      match(CminusParser::T__3);
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

//----------------- Selection_stmtContext ------------------------------------------------------------------

CminusParser::Selection_stmtContext::Selection_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CminusParser::StatementContext *> CminusParser::Selection_stmtContext::statement() {
  return getRuleContexts<CminusParser::StatementContext>();
}

CminusParser::StatementContext* CminusParser::Selection_stmtContext::statement(size_t i) {
  return getRuleContext<CminusParser::StatementContext>(i);
}

CminusParser::ExpContext* CminusParser::Selection_stmtContext::exp() {
  return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Relational_expContext* CminusParser::Selection_stmtContext::relational_exp() {
  return getRuleContext<CminusParser::Relational_expContext>(0);
}


size_t CminusParser::Selection_stmtContext::getRuleIndex() const {
  return CminusParser::RuleSelection_stmt;
}

void CminusParser::Selection_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSelection_stmt(this);
}

void CminusParser::Selection_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSelection_stmt(this);
}


antlrcpp::Any CminusParser::Selection_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitSelection_stmt(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Selection_stmtContext* CminusParser::selection_stmt() {
  Selection_stmtContext *_localctx = _tracker.createInstance<Selection_stmtContext>(_ctx, getState());
  enterRule(_localctx, 12, CminusParser::RuleSelection_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(90);
    match(CminusParser::T__10);
    setState(91);
    match(CminusParser::T__5);
    setState(94);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 9, _ctx)) {
    case 1: {
      setState(92);
      exp(0);
      break;
    }

    case 2: {
      setState(93);
      relational_exp();
      break;
    }

    default:
      break;
    }
    setState(96);
    match(CminusParser::T__7);
    setState(97);
    statement();
    setState(100);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 10, _ctx)) {
    case 1: {
      setState(98);
      match(CminusParser::T__11);
      setState(99);
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

//----------------- Iteration_stmtContext ------------------------------------------------------------------

CminusParser::Iteration_stmtContext::Iteration_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::StatementContext* CminusParser::Iteration_stmtContext::statement() {
  return getRuleContext<CminusParser::StatementContext>(0);
}

CminusParser::ExpContext* CminusParser::Iteration_stmtContext::exp() {
  return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Relational_expContext* CminusParser::Iteration_stmtContext::relational_exp() {
  return getRuleContext<CminusParser::Relational_expContext>(0);
}


size_t CminusParser::Iteration_stmtContext::getRuleIndex() const {
  return CminusParser::RuleIteration_stmt;
}

void CminusParser::Iteration_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIteration_stmt(this);
}

void CminusParser::Iteration_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIteration_stmt(this);
}


antlrcpp::Any CminusParser::Iteration_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitIteration_stmt(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Iteration_stmtContext* CminusParser::iteration_stmt() {
  Iteration_stmtContext *_localctx = _tracker.createInstance<Iteration_stmtContext>(_ctx, getState());
  enterRule(_localctx, 14, CminusParser::RuleIteration_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(102);
    match(CminusParser::T__12);
    setState(103);
    match(CminusParser::T__5);
    setState(106);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 11, _ctx)) {
    case 1: {
      setState(104);
      exp(0);
      break;
    }

    case 2: {
      setState(105);
      relational_exp();
      break;
    }

    default:
      break;
    }
    setState(108);
    match(CminusParser::T__7);
    setState(109);
    statement();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assignment_stmtContext ------------------------------------------------------------------

CminusParser::Assignment_stmtContext::Assignment_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* CminusParser::Assignment_stmtContext::ID() {
  return getToken(CminusParser::ID, 0);
}

std::vector<CminusParser::ExpContext *> CminusParser::Assignment_stmtContext::exp() {
  return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Assignment_stmtContext::exp(size_t i) {
  return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::Relational_expContext* CminusParser::Assignment_stmtContext::relational_exp() {
  return getRuleContext<CminusParser::Relational_expContext>(0);
}


size_t CminusParser::Assignment_stmtContext::getRuleIndex() const {
  return CminusParser::RuleAssignment_stmt;
}

void CminusParser::Assignment_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment_stmt(this);
}

void CminusParser::Assignment_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment_stmt(this);
}


antlrcpp::Any CminusParser::Assignment_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitAssignment_stmt(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Assignment_stmtContext* CminusParser::assignment_stmt() {
  Assignment_stmtContext *_localctx = _tracker.createInstance<Assignment_stmtContext>(_ctx, getState());
  enterRule(_localctx, 16, CminusParser::RuleAssignment_stmt);
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
    setState(111);
    match(CminusParser::ID);
    setState(116);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == CminusParser::T__1) {
      setState(112);
      match(CminusParser::T__1);
      setState(113);
      exp(0);
      setState(114);
      match(CminusParser::T__2);
    }
    setState(118);
    match(CminusParser::T__13);
    setState(121);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 13, _ctx)) {
    case 1: {
      setState(119);
      exp(0);
      break;
    }

    case 2: {
      setState(120);
      relational_exp();
      break;
    }

    default:
      break;
    }
    setState(123);
    match(CminusParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Return_stmtContext ------------------------------------------------------------------

CminusParser::Return_stmtContext::Return_stmtContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

CminusParser::ExpContext* CminusParser::Return_stmtContext::exp() {
  return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Relational_expContext* CminusParser::Return_stmtContext::relational_exp() {
  return getRuleContext<CminusParser::Relational_expContext>(0);
}


size_t CminusParser::Return_stmtContext::getRuleIndex() const {
  return CminusParser::RuleReturn_stmt;
}

void CminusParser::Return_stmtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterReturn_stmt(this);
}

void CminusParser::Return_stmtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitReturn_stmt(this);
}


antlrcpp::Any CminusParser::Return_stmtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitReturn_stmt(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Return_stmtContext* CminusParser::return_stmt() {
  Return_stmtContext *_localctx = _tracker.createInstance<Return_stmtContext>(_ctx, getState());
  enterRule(_localctx, 18, CminusParser::RuleReturn_stmt);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(125);
    match(CminusParser::T__14);
    setState(128);
    _errHandler->sync(this);

    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 14, _ctx)) {
    case 1: {
      setState(126);
      exp(0);
      break;
    }

    case 2: {
      setState(127);
      relational_exp();
      break;
    }

    default:
      break;
    }
    setState(130);
    match(CminusParser::T__3);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExpContext ------------------------------------------------------------------

CminusParser::ExpContext::ExpContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t CminusParser::ExpContext::getRuleIndex() const {
  return CminusParser::RuleExp;
}

void CminusParser::ExpContext::copyFrom(ExpContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- Add_expContext ------------------------------------------------------------------

std::vector<CminusParser::ExpContext *> CminusParser::Add_expContext::exp() {
  return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Add_expContext::exp(size_t i) {
  return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::Add_expContext::Add_expContext(ExpContext *ctx) { copyFrom(ctx); }

void CminusParser::Add_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdd_exp(this);
}
void CminusParser::Add_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdd_exp(this);
}

antlrcpp::Any CminusParser::Add_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitAdd_exp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Paren_expContext ------------------------------------------------------------------

CminusParser::ExpContext* CminusParser::Paren_expContext::exp() {
  return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Relational_expContext* CminusParser::Paren_expContext::relational_exp() {
  return getRuleContext<CminusParser::Relational_expContext>(0);
}

CminusParser::Paren_expContext::Paren_expContext(ExpContext *ctx) { copyFrom(ctx); }

void CminusParser::Paren_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParen_exp(this);
}
void CminusParser::Paren_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParen_exp(this);
}

antlrcpp::Any CminusParser::Paren_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitParen_exp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Num_expContext ------------------------------------------------------------------

tree::TerminalNode* CminusParser::Num_expContext::NUM() {
  return getToken(CminusParser::NUM, 0);
}

CminusParser::Num_expContext::Num_expContext(ExpContext *ctx) { copyFrom(ctx); }

void CminusParser::Num_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNum_exp(this);
}
void CminusParser::Num_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNum_exp(this);
}

antlrcpp::Any CminusParser::Num_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitNum_exp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Call_expContext ------------------------------------------------------------------

tree::TerminalNode* CminusParser::Call_expContext::ID() {
  return getToken(CminusParser::ID, 0);
}

std::vector<CminusParser::ExpContext *> CminusParser::Call_expContext::exp() {
  return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Call_expContext::exp(size_t i) {
  return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::Call_expContext::Call_expContext(ExpContext *ctx) { copyFrom(ctx); }

void CminusParser::Call_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCall_exp(this);
}
void CminusParser::Call_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCall_exp(this);
}

antlrcpp::Any CminusParser::Call_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitCall_exp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Val_expContext ------------------------------------------------------------------

tree::TerminalNode* CminusParser::Val_expContext::ID() {
  return getToken(CminusParser::ID, 0);
}

CminusParser::ExpContext* CminusParser::Val_expContext::exp() {
  return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Val_expContext::Val_expContext(ExpContext *ctx) { copyFrom(ctx); }

void CminusParser::Val_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterVal_exp(this);
}
void CminusParser::Val_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitVal_exp(this);
}

antlrcpp::Any CminusParser::Val_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitVal_exp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- Mult_expContext ------------------------------------------------------------------

std::vector<CminusParser::ExpContext *> CminusParser::Mult_expContext::exp() {
  return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Mult_expContext::exp(size_t i) {
  return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::Mult_expContext::Mult_expContext(ExpContext *ctx) { copyFrom(ctx); }

void CminusParser::Mult_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMult_exp(this);
}
void CminusParser::Mult_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMult_exp(this);
}

antlrcpp::Any CminusParser::Mult_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitMult_exp(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::ExpContext* CminusParser::exp() {
   return exp(0);
}

CminusParser::ExpContext* CminusParser::exp(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  CminusParser::ExpContext *_localctx = _tracker.createInstance<ExpContext>(_ctx, parentState);
  CminusParser::ExpContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 20;
  enterRecursionRule(_localctx, 20, CminusParser::RuleExp, precedence);

    size_t _la = 0;

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
    setState(161);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 19, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<Paren_expContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(133);
      match(CminusParser::T__5);
      setState(136);
      _errHandler->sync(this);
      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 15, _ctx)) {
      case 1: {
        setState(134);
        exp(0);
        break;
      }

      case 2: {
        setState(135);
        relational_exp();
        break;
      }

      default:
        break;
      }
      setState(138);
      match(CminusParser::T__7);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<Val_expContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(140);
      match(CminusParser::ID);
      setState(145);
      _errHandler->sync(this);

      switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 16, _ctx)) {
      case 1: {
        setState(141);
        match(CminusParser::T__1);
        setState(142);
        exp(0);
        setState(143);
        match(CminusParser::T__2);
        break;
      }

      default:
        break;
      }
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<Call_expContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(147);
      match(CminusParser::ID);
      setState(148);
      match(CminusParser::T__5);
      setState(157);
      _errHandler->sync(this);

      _la = _input->LA(1);
      if ((((_la & ~ 0x3fULL) == 0) &&
        ((1ULL << _la) & ((1ULL << CminusParser::T__5)
        | (1ULL << CminusParser::ID)
        | (1ULL << CminusParser::NUM))) != 0)) {
        setState(149);
        exp(0);
        setState(154);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CminusParser::T__6) {
          setState(150);
          match(CminusParser::T__6);
          setState(151);
          exp(0);
          setState(156);
          _errHandler->sync(this);
          _la = _input->LA(1);
        }
      }
      setState(159);
      match(CminusParser::T__7);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<Num_expContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(160);
      match(CminusParser::NUM);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(171);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(169);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 20, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<Mult_expContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(163);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(164);
          _la = _input->LA(1);
          if (!(_la == CminusParser::T__15

          || _la == CminusParser::T__16)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(165);
          exp(7);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<Add_expContext>(_tracker.createInstance<ExpContext>(parentContext, parentState));
          _localctx = newContext;
          pushNewRecursionContext(newContext, startState, RuleExp);
          setState(166);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(167);
          _la = _input->LA(1);
          if (!(_la == CminusParser::T__17

          || _la == CminusParser::T__18)) {
          _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(168);
          exp(6);
          break;
        }

        default:
          break;
        } 
      }
      setState(173);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 21, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- Relational_expContext ------------------------------------------------------------------

CminusParser::Relational_expContext::Relational_expContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<CminusParser::ExpContext *> CminusParser::Relational_expContext::exp() {
  return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Relational_expContext::exp(size_t i) {
  return getRuleContext<CminusParser::ExpContext>(i);
}


size_t CminusParser::Relational_expContext::getRuleIndex() const {
  return CminusParser::RuleRelational_exp;
}

void CminusParser::Relational_expContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRelational_exp(this);
}

void CminusParser::Relational_expContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<CminusListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRelational_exp(this);
}


antlrcpp::Any CminusParser::Relational_expContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
    return parserVisitor->visitRelational_exp(this);
  else
    return visitor->visitChildren(this);
}

CminusParser::Relational_expContext* CminusParser::relational_exp() {
  Relational_expContext *_localctx = _tracker.createInstance<Relational_expContext>(_ctx, getState());
  enterRule(_localctx, 22, CminusParser::RuleRelational_exp);
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
    setState(174);
    exp(0);
    setState(175);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & ((1ULL << CminusParser::T__19)
      | (1ULL << CminusParser::T__20)
      | (1ULL << CminusParser::T__21)
      | (1ULL << CminusParser::T__22)
      | (1ULL << CminusParser::T__23)
      | (1ULL << CminusParser::T__24))) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
    setState(176);
    exp(0);
   
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
    case 10: return expSempred(dynamic_cast<ExpContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool CminusParser::expSempred(ExpContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 6);
    case 1: return precpred(_ctx, 5);

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
  "program", "var_decleration", "fun_decleration", "param", "compound_stmt", 
  "statement", "selection_stmt", "iteration_stmt", "assignment_stmt", "return_stmt", 
  "exp", "relational_exp"
};

std::vector<std::string> CminusParser::_literalNames = {
  "", "'int'", "'['", "']'", "';'", "'void'", "'('", "','", "')'", "'{'", 
  "'}'", "'if'", "'else'", "'while'", "'='", "'return'", "'*'", "'/'", "'+'", 
  "'-'", "'<='", "'<'", "'>'", "'>='", "'=='", "'!='"
};

std::vector<std::string> CminusParser::_symbolicNames = {
  "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
  "", "", "", "", "", "", "", "", "ID", "NUM", "COMMENT", "WS"
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
    0x3, 0x1f, 0xb5, 0x4, 0x2, 0x9, 0x2, 0x4, 0x3, 0x9, 0x3, 0x4, 0x4, 0x9, 
    0x4, 0x4, 0x5, 0x9, 0x5, 0x4, 0x6, 0x9, 0x6, 0x4, 0x7, 0x9, 0x7, 0x4, 
    0x8, 0x9, 0x8, 0x4, 0x9, 0x9, 0x9, 0x4, 0xa, 0x9, 0xa, 0x4, 0xb, 0x9, 
    0xb, 0x4, 0xc, 0x9, 0xc, 0x4, 0xd, 0x9, 0xd, 0x3, 0x2, 0x3, 0x2, 0x6, 
    0x2, 0x1d, 0xa, 0x2, 0xd, 0x2, 0xe, 0x2, 0x1e, 0x3, 0x2, 0x3, 0x2, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x3, 0x5, 0x3, 0x28, 0xa, 0x3, 
    0x3, 0x3, 0x3, 0x3, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 
    0x3, 0x4, 0x7, 0x4, 0x32, 0xa, 0x4, 0xc, 0x4, 0xe, 0x4, 0x35, 0xb, 0x4, 
    0x3, 0x4, 0x5, 0x4, 0x38, 0xa, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 0x4, 0x3, 
    0x5, 0x3, 0x5, 0x3, 0x5, 0x3, 0x5, 0x5, 0x5, 0x41, 0xa, 0x5, 0x3, 0x6, 
    0x3, 0x6, 0x7, 0x6, 0x45, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x48, 0xb, 0x6, 
    0x3, 0x6, 0x7, 0x6, 0x4b, 0xa, 0x6, 0xc, 0x6, 0xe, 0x6, 0x4e, 0xb, 0x6, 
    0x3, 0x6, 0x3, 0x6, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 
    0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x3, 0x7, 0x5, 0x7, 0x5b, 0xa, 0x7, 0x3, 
    0x8, 0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x61, 0xa, 0x8, 0x3, 0x8, 
    0x3, 0x8, 0x3, 0x8, 0x3, 0x8, 0x5, 0x8, 0x67, 0xa, 0x8, 0x3, 0x9, 0x3, 
    0x9, 0x3, 0x9, 0x3, 0x9, 0x5, 0x9, 0x6d, 0xa, 0x9, 0x3, 0x9, 0x3, 0x9, 
    0x3, 0x9, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 
    0x77, 0xa, 0xa, 0x3, 0xa, 0x3, 0xa, 0x3, 0xa, 0x5, 0xa, 0x7c, 0xa, 0xa, 
    0x3, 0xa, 0x3, 0xa, 0x3, 0xb, 0x3, 0xb, 0x3, 0xb, 0x5, 0xb, 0x83, 0xa, 
    0xb, 0x3, 0xb, 0x3, 0xb, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 
    0xc, 0x8b, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 
    0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 0x94, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x3, 0xc, 0x3, 0xc, 0x7, 0xc, 0x9b, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 
    0x9e, 0xb, 0xc, 0x5, 0xc, 0xa0, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x5, 0xc, 
    0xa4, 0xa, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 0xc, 0x3, 
    0xc, 0x7, 0xc, 0xac, 0xa, 0xc, 0xc, 0xc, 0xe, 0xc, 0xaf, 0xb, 0xc, 0x3, 
    0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x3, 0xd, 0x2, 0x3, 0x16, 0xe, 0x2, 
    0x4, 0x6, 0x8, 0xa, 0xc, 0xe, 0x10, 0x12, 0x14, 0x16, 0x18, 0x2, 0x6, 
    0x4, 0x2, 0x3, 0x3, 0x7, 0x7, 0x3, 0x2, 0x12, 0x13, 0x3, 0x2, 0x14, 
    0x15, 0x3, 0x2, 0x16, 0x1b, 0x2, 0xc6, 0x2, 0x1c, 0x3, 0x2, 0x2, 0x2, 
    0x4, 0x22, 0x3, 0x2, 0x2, 0x2, 0x6, 0x2b, 0x3, 0x2, 0x2, 0x2, 0x8, 0x3c, 
    0x3, 0x2, 0x2, 0x2, 0xa, 0x42, 0x3, 0x2, 0x2, 0x2, 0xc, 0x5a, 0x3, 0x2, 
    0x2, 0x2, 0xe, 0x5c, 0x3, 0x2, 0x2, 0x2, 0x10, 0x68, 0x3, 0x2, 0x2, 
    0x2, 0x12, 0x71, 0x3, 0x2, 0x2, 0x2, 0x14, 0x7f, 0x3, 0x2, 0x2, 0x2, 
    0x16, 0xa3, 0x3, 0x2, 0x2, 0x2, 0x18, 0xb0, 0x3, 0x2, 0x2, 0x2, 0x1a, 
    0x1d, 0x5, 0x4, 0x3, 0x2, 0x1b, 0x1d, 0x5, 0x6, 0x4, 0x2, 0x1c, 0x1a, 
    0x3, 0x2, 0x2, 0x2, 0x1c, 0x1b, 0x3, 0x2, 0x2, 0x2, 0x1d, 0x1e, 0x3, 
    0x2, 0x2, 0x2, 0x1e, 0x1c, 0x3, 0x2, 0x2, 0x2, 0x1e, 0x1f, 0x3, 0x2, 
    0x2, 0x2, 0x1f, 0x20, 0x3, 0x2, 0x2, 0x2, 0x20, 0x21, 0x7, 0x2, 0x2, 
    0x3, 0x21, 0x3, 0x3, 0x2, 0x2, 0x2, 0x22, 0x23, 0x7, 0x3, 0x2, 0x2, 
    0x23, 0x27, 0x7, 0x1c, 0x2, 0x2, 0x24, 0x25, 0x7, 0x4, 0x2, 0x2, 0x25, 
    0x26, 0x7, 0x1d, 0x2, 0x2, 0x26, 0x28, 0x7, 0x5, 0x2, 0x2, 0x27, 0x24, 
    0x3, 0x2, 0x2, 0x2, 0x27, 0x28, 0x3, 0x2, 0x2, 0x2, 0x28, 0x29, 0x3, 
    0x2, 0x2, 0x2, 0x29, 0x2a, 0x7, 0x6, 0x2, 0x2, 0x2a, 0x5, 0x3, 0x2, 
    0x2, 0x2, 0x2b, 0x2c, 0x9, 0x2, 0x2, 0x2, 0x2c, 0x2d, 0x7, 0x1c, 0x2, 
    0x2, 0x2d, 0x37, 0x7, 0x8, 0x2, 0x2, 0x2e, 0x33, 0x5, 0x8, 0x5, 0x2, 
    0x2f, 0x30, 0x7, 0x9, 0x2, 0x2, 0x30, 0x32, 0x5, 0x8, 0x5, 0x2, 0x31, 
    0x2f, 0x3, 0x2, 0x2, 0x2, 0x32, 0x35, 0x3, 0x2, 0x2, 0x2, 0x33, 0x31, 
    0x3, 0x2, 0x2, 0x2, 0x33, 0x34, 0x3, 0x2, 0x2, 0x2, 0x34, 0x38, 0x3, 
    0x2, 0x2, 0x2, 0x35, 0x33, 0x3, 0x2, 0x2, 0x2, 0x36, 0x38, 0x7, 0x7, 
    0x2, 0x2, 0x37, 0x2e, 0x3, 0x2, 0x2, 0x2, 0x37, 0x36, 0x3, 0x2, 0x2, 
    0x2, 0x38, 0x39, 0x3, 0x2, 0x2, 0x2, 0x39, 0x3a, 0x7, 0xa, 0x2, 0x2, 
    0x3a, 0x3b, 0x5, 0xa, 0x6, 0x2, 0x3b, 0x7, 0x3, 0x2, 0x2, 0x2, 0x3c, 
    0x3d, 0x7, 0x3, 0x2, 0x2, 0x3d, 0x40, 0x7, 0x1c, 0x2, 0x2, 0x3e, 0x3f, 
    0x7, 0x4, 0x2, 0x2, 0x3f, 0x41, 0x7, 0x5, 0x2, 0x2, 0x40, 0x3e, 0x3, 
    0x2, 0x2, 0x2, 0x40, 0x41, 0x3, 0x2, 0x2, 0x2, 0x41, 0x9, 0x3, 0x2, 
    0x2, 0x2, 0x42, 0x46, 0x7, 0xb, 0x2, 0x2, 0x43, 0x45, 0x5, 0x4, 0x3, 
    0x2, 0x44, 0x43, 0x3, 0x2, 0x2, 0x2, 0x45, 0x48, 0x3, 0x2, 0x2, 0x2, 
    0x46, 0x44, 0x3, 0x2, 0x2, 0x2, 0x46, 0x47, 0x3, 0x2, 0x2, 0x2, 0x47, 
    0x4c, 0x3, 0x2, 0x2, 0x2, 0x48, 0x46, 0x3, 0x2, 0x2, 0x2, 0x49, 0x4b, 
    0x5, 0xc, 0x7, 0x2, 0x4a, 0x49, 0x3, 0x2, 0x2, 0x2, 0x4b, 0x4e, 0x3, 
    0x2, 0x2, 0x2, 0x4c, 0x4a, 0x3, 0x2, 0x2, 0x2, 0x4c, 0x4d, 0x3, 0x2, 
    0x2, 0x2, 0x4d, 0x4f, 0x3, 0x2, 0x2, 0x2, 0x4e, 0x4c, 0x3, 0x2, 0x2, 
    0x2, 0x4f, 0x50, 0x7, 0xc, 0x2, 0x2, 0x50, 0xb, 0x3, 0x2, 0x2, 0x2, 
    0x51, 0x5b, 0x5, 0xa, 0x6, 0x2, 0x52, 0x5b, 0x5, 0xe, 0x8, 0x2, 0x53, 
    0x5b, 0x5, 0x10, 0x9, 0x2, 0x54, 0x5b, 0x5, 0x12, 0xa, 0x2, 0x55, 0x5b, 
    0x5, 0x14, 0xb, 0x2, 0x56, 0x57, 0x5, 0x16, 0xc, 0x2, 0x57, 0x58, 0x7, 
    0x6, 0x2, 0x2, 0x58, 0x5b, 0x3, 0x2, 0x2, 0x2, 0x59, 0x5b, 0x7, 0x6, 
    0x2, 0x2, 0x5a, 0x51, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x52, 0x3, 0x2, 0x2, 
    0x2, 0x5a, 0x53, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x54, 0x3, 0x2, 0x2, 0x2, 
    0x5a, 0x55, 0x3, 0x2, 0x2, 0x2, 0x5a, 0x56, 0x3, 0x2, 0x2, 0x2, 0x5a, 
    0x59, 0x3, 0x2, 0x2, 0x2, 0x5b, 0xd, 0x3, 0x2, 0x2, 0x2, 0x5c, 0x5d, 
    0x7, 0xd, 0x2, 0x2, 0x5d, 0x60, 0x7, 0x8, 0x2, 0x2, 0x5e, 0x61, 0x5, 
    0x16, 0xc, 0x2, 0x5f, 0x61, 0x5, 0x18, 0xd, 0x2, 0x60, 0x5e, 0x3, 0x2, 
    0x2, 0x2, 0x60, 0x5f, 0x3, 0x2, 0x2, 0x2, 0x61, 0x62, 0x3, 0x2, 0x2, 
    0x2, 0x62, 0x63, 0x7, 0xa, 0x2, 0x2, 0x63, 0x66, 0x5, 0xc, 0x7, 0x2, 
    0x64, 0x65, 0x7, 0xe, 0x2, 0x2, 0x65, 0x67, 0x5, 0xc, 0x7, 0x2, 0x66, 
    0x64, 0x3, 0x2, 0x2, 0x2, 0x66, 0x67, 0x3, 0x2, 0x2, 0x2, 0x67, 0xf, 
    0x3, 0x2, 0x2, 0x2, 0x68, 0x69, 0x7, 0xf, 0x2, 0x2, 0x69, 0x6c, 0x7, 
    0x8, 0x2, 0x2, 0x6a, 0x6d, 0x5, 0x16, 0xc, 0x2, 0x6b, 0x6d, 0x5, 0x18, 
    0xd, 0x2, 0x6c, 0x6a, 0x3, 0x2, 0x2, 0x2, 0x6c, 0x6b, 0x3, 0x2, 0x2, 
    0x2, 0x6d, 0x6e, 0x3, 0x2, 0x2, 0x2, 0x6e, 0x6f, 0x7, 0xa, 0x2, 0x2, 
    0x6f, 0x70, 0x5, 0xc, 0x7, 0x2, 0x70, 0x11, 0x3, 0x2, 0x2, 0x2, 0x71, 
    0x76, 0x7, 0x1c, 0x2, 0x2, 0x72, 0x73, 0x7, 0x4, 0x2, 0x2, 0x73, 0x74, 
    0x5, 0x16, 0xc, 0x2, 0x74, 0x75, 0x7, 0x5, 0x2, 0x2, 0x75, 0x77, 0x3, 
    0x2, 0x2, 0x2, 0x76, 0x72, 0x3, 0x2, 0x2, 0x2, 0x76, 0x77, 0x3, 0x2, 
    0x2, 0x2, 0x77, 0x78, 0x3, 0x2, 0x2, 0x2, 0x78, 0x7b, 0x7, 0x10, 0x2, 
    0x2, 0x79, 0x7c, 0x5, 0x16, 0xc, 0x2, 0x7a, 0x7c, 0x5, 0x18, 0xd, 0x2, 
    0x7b, 0x79, 0x3, 0x2, 0x2, 0x2, 0x7b, 0x7a, 0x3, 0x2, 0x2, 0x2, 0x7c, 
    0x7d, 0x3, 0x2, 0x2, 0x2, 0x7d, 0x7e, 0x7, 0x6, 0x2, 0x2, 0x7e, 0x13, 
    0x3, 0x2, 0x2, 0x2, 0x7f, 0x82, 0x7, 0x11, 0x2, 0x2, 0x80, 0x83, 0x5, 
    0x16, 0xc, 0x2, 0x81, 0x83, 0x5, 0x18, 0xd, 0x2, 0x82, 0x80, 0x3, 0x2, 
    0x2, 0x2, 0x82, 0x81, 0x3, 0x2, 0x2, 0x2, 0x82, 0x83, 0x3, 0x2, 0x2, 
    0x2, 0x83, 0x84, 0x3, 0x2, 0x2, 0x2, 0x84, 0x85, 0x7, 0x6, 0x2, 0x2, 
    0x85, 0x15, 0x3, 0x2, 0x2, 0x2, 0x86, 0x87, 0x8, 0xc, 0x1, 0x2, 0x87, 
    0x8a, 0x7, 0x8, 0x2, 0x2, 0x88, 0x8b, 0x5, 0x16, 0xc, 0x2, 0x89, 0x8b, 
    0x5, 0x18, 0xd, 0x2, 0x8a, 0x88, 0x3, 0x2, 0x2, 0x2, 0x8a, 0x89, 0x3, 
    0x2, 0x2, 0x2, 0x8b, 0x8c, 0x3, 0x2, 0x2, 0x2, 0x8c, 0x8d, 0x7, 0xa, 
    0x2, 0x2, 0x8d, 0xa4, 0x3, 0x2, 0x2, 0x2, 0x8e, 0x93, 0x7, 0x1c, 0x2, 
    0x2, 0x8f, 0x90, 0x7, 0x4, 0x2, 0x2, 0x90, 0x91, 0x5, 0x16, 0xc, 0x2, 
    0x91, 0x92, 0x7, 0x5, 0x2, 0x2, 0x92, 0x94, 0x3, 0x2, 0x2, 0x2, 0x93, 
    0x8f, 0x3, 0x2, 0x2, 0x2, 0x93, 0x94, 0x3, 0x2, 0x2, 0x2, 0x94, 0xa4, 
    0x3, 0x2, 0x2, 0x2, 0x95, 0x96, 0x7, 0x1c, 0x2, 0x2, 0x96, 0x9f, 0x7, 
    0x8, 0x2, 0x2, 0x97, 0x9c, 0x5, 0x16, 0xc, 0x2, 0x98, 0x99, 0x7, 0x9, 
    0x2, 0x2, 0x99, 0x9b, 0x5, 0x16, 0xc, 0x2, 0x9a, 0x98, 0x3, 0x2, 0x2, 
    0x2, 0x9b, 0x9e, 0x3, 0x2, 0x2, 0x2, 0x9c, 0x9a, 0x3, 0x2, 0x2, 0x2, 
    0x9c, 0x9d, 0x3, 0x2, 0x2, 0x2, 0x9d, 0xa0, 0x3, 0x2, 0x2, 0x2, 0x9e, 
    0x9c, 0x3, 0x2, 0x2, 0x2, 0x9f, 0x97, 0x3, 0x2, 0x2, 0x2, 0x9f, 0xa0, 
    0x3, 0x2, 0x2, 0x2, 0xa0, 0xa1, 0x3, 0x2, 0x2, 0x2, 0xa1, 0xa4, 0x7, 
    0xa, 0x2, 0x2, 0xa2, 0xa4, 0x7, 0x1d, 0x2, 0x2, 0xa3, 0x86, 0x3, 0x2, 
    0x2, 0x2, 0xa3, 0x8e, 0x3, 0x2, 0x2, 0x2, 0xa3, 0x95, 0x3, 0x2, 0x2, 
    0x2, 0xa3, 0xa2, 0x3, 0x2, 0x2, 0x2, 0xa4, 0xad, 0x3, 0x2, 0x2, 0x2, 
    0xa5, 0xa6, 0xc, 0x8, 0x2, 0x2, 0xa6, 0xa7, 0x9, 0x3, 0x2, 0x2, 0xa7, 
    0xac, 0x5, 0x16, 0xc, 0x9, 0xa8, 0xa9, 0xc, 0x7, 0x2, 0x2, 0xa9, 0xaa, 
    0x9, 0x4, 0x2, 0x2, 0xaa, 0xac, 0x5, 0x16, 0xc, 0x8, 0xab, 0xa5, 0x3, 
    0x2, 0x2, 0x2, 0xab, 0xa8, 0x3, 0x2, 0x2, 0x2, 0xac, 0xaf, 0x3, 0x2, 
    0x2, 0x2, 0xad, 0xab, 0x3, 0x2, 0x2, 0x2, 0xad, 0xae, 0x3, 0x2, 0x2, 
    0x2, 0xae, 0x17, 0x3, 0x2, 0x2, 0x2, 0xaf, 0xad, 0x3, 0x2, 0x2, 0x2, 
    0xb0, 0xb1, 0x5, 0x16, 0xc, 0x2, 0xb1, 0xb2, 0x9, 0x5, 0x2, 0x2, 0xb2, 
    0xb3, 0x5, 0x16, 0xc, 0x2, 0xb3, 0x19, 0x3, 0x2, 0x2, 0x2, 0x18, 0x1c, 
    0x1e, 0x27, 0x33, 0x37, 0x40, 0x46, 0x4c, 0x5a, 0x60, 0x66, 0x6c, 0x76, 
    0x7b, 0x82, 0x8a, 0x93, 0x9c, 0x9f, 0xa3, 0xab, 0xad, 
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
