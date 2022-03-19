
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#include "CminusListener.h"
#include "CminusVisitor.h"

#include "CminusParser.h"

using namespace antlrcpp;
using namespace antlr4;

CminusParser::CminusParser(TokenStream* input) : Parser(input) {
    _interpreter = new atn::ParserATNSimulator(this, _atn, _decisionToDFA,
                                               _sharedContextCache);
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

//----------------- ProgramContext
//------------------------------------------------------------------

CminusParser::ProgramContext::ProgramContext(ParserRuleContext* parent,
                                             size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::ProgramContext::EOF() {
    return getToken(CminusParser::EOF, 0);
}

std::vector<CminusParser::Var_declarationContext*>
CminusParser::ProgramContext::var_declaration() {
    return getRuleContexts<CminusParser::Var_declarationContext>();
}

CminusParser::Var_declarationContext*
CminusParser::ProgramContext::var_declaration(size_t i) {
    return getRuleContext<CminusParser::Var_declarationContext>(i);
}

std::vector<CminusParser::Fun_declarationContext*>
CminusParser::ProgramContext::fun_declaration() {
    return getRuleContexts<CminusParser::Fun_declarationContext>();
}

CminusParser::Fun_declarationContext*
CminusParser::ProgramContext::fun_declaration(size_t i) {
    return getRuleContext<CminusParser::Fun_declarationContext>(i);
}

size_t CminusParser::ProgramContext::getRuleIndex() const {
    return CminusParser::RuleProgram;
}

void CminusParser::ProgramContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterProgram(this);
}

void CminusParser::ProgramContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitProgram(this);
}

antlrcpp::Any
CminusParser::ProgramContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitProgram(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::ProgramContext* CminusParser::program() {
    ProgramContext* _localctx =
        _tracker.createInstance<ProgramContext>(_ctx, getState());
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
        setState(34);
        _errHandler->sync(this);
        _la = _input->LA(1);
        do {
            setState(34);
            _errHandler->sync(this);
            switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
                _input, 0, _ctx)) {
                case 1: {
                    setState(32);
                    var_declaration();
                    break;
                }

                case 2: {
                    setState(33);
                    fun_declaration();
                    break;
                }

                default:
                    break;
            }
            setState(36);
            _errHandler->sync(this);
            _la = _input->LA(1);
        } while (_la == CminusParser::INT

                 || _la == CminusParser::VOID);
        setState(38);
        match(CminusParser::EOF);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Var_declarationContext
//------------------------------------------------------------------

CminusParser::Var_declarationContext::Var_declarationContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::Var_declarationContext::INT() {
    return getToken(CminusParser::INT, 0);
}

tree::TerminalNode* CminusParser::Var_declarationContext::ID() {
    return getToken(CminusParser::ID, 0);
}

tree::TerminalNode* CminusParser::Var_declarationContext::NUM() {
    return getToken(CminusParser::NUM, 0);
}

size_t CminusParser::Var_declarationContext::getRuleIndex() const {
    return CminusParser::RuleVar_declaration;
}

void CminusParser::Var_declarationContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterVar_declaration(this);
}

void CminusParser::Var_declarationContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitVar_declaration(this);
}

antlrcpp::Any
CminusParser::Var_declarationContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitVar_declaration(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Var_declarationContext* CminusParser::var_declaration() {
    Var_declarationContext* _localctx =
        _tracker.createInstance<Var_declarationContext>(_ctx, getState());
    enterRule(_localctx, 2, CminusParser::RuleVar_declaration);
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
        setState(40);
        match(CminusParser::INT);
        setState(41);
        match(CminusParser::ID);
        setState(45);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CminusParser::T__0) {
            setState(42);
            match(CminusParser::T__0);
            setState(43);
            match(CminusParser::NUM);
            setState(44);
            match(CminusParser::T__1);
        }
        setState(47);
        match(CminusParser::T__2);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Fun_declarationContext
//------------------------------------------------------------------

CminusParser::Fun_declarationContext::Fun_declarationContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

CminusParser::Fun_type_specifierContext*
CminusParser::Fun_declarationContext::fun_type_specifier() {
    return getRuleContext<CminusParser::Fun_type_specifierContext>(0);
}

tree::TerminalNode* CminusParser::Fun_declarationContext::ID() {
    return getToken(CminusParser::ID, 0);
}

CminusParser::Compound_stmtContext*
CminusParser::Fun_declarationContext::compound_stmt() {
    return getRuleContext<CminusParser::Compound_stmtContext>(0);
}

std::vector<CminusParser::ParamContext*>
CminusParser::Fun_declarationContext::param() {
    return getRuleContexts<CminusParser::ParamContext>();
}

CminusParser::ParamContext*
CminusParser::Fun_declarationContext::param(size_t i) {
    return getRuleContext<CminusParser::ParamContext>(i);
}

tree::TerminalNode* CminusParser::Fun_declarationContext::VOID() {
    return getToken(CminusParser::VOID, 0);
}

size_t CminusParser::Fun_declarationContext::getRuleIndex() const {
    return CminusParser::RuleFun_declaration;
}

void CminusParser::Fun_declarationContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterFun_declaration(this);
}

void CminusParser::Fun_declarationContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitFun_declaration(this);
}

antlrcpp::Any
CminusParser::Fun_declarationContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitFun_declaration(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Fun_declarationContext* CminusParser::fun_declaration() {
    Fun_declarationContext* _localctx =
        _tracker.createInstance<Fun_declarationContext>(_ctx, getState());
    enterRule(_localctx, 4, CminusParser::RuleFun_declaration);
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
        setState(49);
        fun_type_specifier();
        setState(50);
        match(CminusParser::ID);
        setState(51);
        match(CminusParser::T__3);
        setState(61);
        _errHandler->sync(this);
        switch (_input->LA(1)) {
            case CminusParser::INT: {
                setState(52);
                param();
                setState(57);
                _errHandler->sync(this);
                _la = _input->LA(1);
                while (_la == CminusParser::T__4) {
                    setState(53);
                    match(CminusParser::T__4);
                    setState(54);
                    param();
                    setState(59);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                }
                break;
            }

            case CminusParser::VOID: {
                setState(60);
                match(CminusParser::VOID);
                break;
            }

            default:
                throw NoViableAltException(this);
        }
        setState(63);
        match(CminusParser::T__5);
        setState(64);
        compound_stmt();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Fun_type_specifierContext
//------------------------------------------------------------------

CminusParser::Fun_type_specifierContext::Fun_type_specifierContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::Fun_type_specifierContext::INT() {
    return getToken(CminusParser::INT, 0);
}

tree::TerminalNode* CminusParser::Fun_type_specifierContext::VOID() {
    return getToken(CminusParser::VOID, 0);
}

size_t CminusParser::Fun_type_specifierContext::getRuleIndex() const {
    return CminusParser::RuleFun_type_specifier;
}

void CminusParser::Fun_type_specifierContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterFun_type_specifier(this);
}

void CminusParser::Fun_type_specifierContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitFun_type_specifier(this);
}

antlrcpp::Any CminusParser::Fun_type_specifierContext::accept(
    tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitFun_type_specifier(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Fun_type_specifierContext* CminusParser::fun_type_specifier() {
    Fun_type_specifierContext* _localctx =
        _tracker.createInstance<Fun_type_specifierContext>(_ctx, getState());
    enterRule(_localctx, 6, CminusParser::RuleFun_type_specifier);
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
        setState(66);
        _la = _input->LA(1);
        if (!(_la == CminusParser::INT

              || _la == CminusParser::VOID)) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ParamContext
//------------------------------------------------------------------

CminusParser::ParamContext::ParamContext(ParserRuleContext* parent,
                                         size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::ParamContext::INT() {
    return getToken(CminusParser::INT, 0);
}

tree::TerminalNode* CminusParser::ParamContext::ID() {
    return getToken(CminusParser::ID, 0);
}

size_t CminusParser::ParamContext::getRuleIndex() const {
    return CminusParser::RuleParam;
}

void CminusParser::ParamContext::enterRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterParam(this);
}

void CminusParser::ParamContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitParam(this);
}

antlrcpp::Any
CminusParser::ParamContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitParam(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::ParamContext* CminusParser::param() {
    ParamContext* _localctx =
        _tracker.createInstance<ParamContext>(_ctx, getState());
    enterRule(_localctx, 8, CminusParser::RuleParam);
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
        setState(68);
        match(CminusParser::INT);
        setState(69);
        match(CminusParser::ID);
        setState(72);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CminusParser::T__0) {
            setState(70);
            match(CminusParser::T__0);
            setState(71);
            match(CminusParser::T__1);
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Compound_stmtContext
//------------------------------------------------------------------

CminusParser::Compound_stmtContext::Compound_stmtContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<CminusParser::Var_declarationContext*>
CminusParser::Compound_stmtContext::var_declaration() {
    return getRuleContexts<CminusParser::Var_declarationContext>();
}

CminusParser::Var_declarationContext*
CminusParser::Compound_stmtContext::var_declaration(size_t i) {
    return getRuleContext<CminusParser::Var_declarationContext>(i);
}

std::vector<CminusParser::StatementContext*>
CminusParser::Compound_stmtContext::statement() {
    return getRuleContexts<CminusParser::StatementContext>();
}

CminusParser::StatementContext*
CminusParser::Compound_stmtContext::statement(size_t i) {
    return getRuleContext<CminusParser::StatementContext>(i);
}

size_t CminusParser::Compound_stmtContext::getRuleIndex() const {
    return CminusParser::RuleCompound_stmt;
}

void CminusParser::Compound_stmtContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterCompound_stmt(this);
}

void CminusParser::Compound_stmtContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitCompound_stmt(this);
}

antlrcpp::Any
CminusParser::Compound_stmtContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitCompound_stmt(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Compound_stmtContext* CminusParser::compound_stmt() {
    Compound_stmtContext* _localctx =
        _tracker.createInstance<Compound_stmtContext>(_ctx, getState());
    enterRule(_localctx, 10, CminusParser::RuleCompound_stmt);
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
        setState(74);
        match(CminusParser::T__6);
        setState(78);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while (_la == CminusParser::INT) {
            setState(75);
            var_declaration();
            setState(80);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(84);
        _errHandler->sync(this);
        _la = _input->LA(1);
        while ((((_la & ~0x3fULL) == 0) &&
                ((1ULL << _la) &
                 ((1ULL << CminusParser::T__2) | (1ULL << CminusParser::T__3) |
                  (1ULL << CminusParser::T__6) | (1ULL << CminusParser::IF) |
                  (1ULL << CminusParser::WHILE) |
                  (1ULL << CminusParser::RETURN) | (1ULL << CminusParser::ID) |
                  (1ULL << CminusParser::NUM))) != 0)) {
            setState(81);
            statement();
            setState(86);
            _errHandler->sync(this);
            _la = _input->LA(1);
        }
        setState(87);
        match(CminusParser::T__7);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- StatementContext
//------------------------------------------------------------------

CminusParser::StatementContext::StatementContext(ParserRuleContext* parent,
                                                 size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

CminusParser::Compound_stmtContext*
CminusParser::StatementContext::compound_stmt() {
    return getRuleContext<CminusParser::Compound_stmtContext>(0);
}

CminusParser::Selection_stmtContext*
CminusParser::StatementContext::selection_stmt() {
    return getRuleContext<CminusParser::Selection_stmtContext>(0);
}

CminusParser::Iteration_stmtContext*
CminusParser::StatementContext::iteration_stmt() {
    return getRuleContext<CminusParser::Iteration_stmtContext>(0);
}

CminusParser::Assignment_stmtContext*
CminusParser::StatementContext::assignment_stmt() {
    return getRuleContext<CminusParser::Assignment_stmtContext>(0);
}

CminusParser::Return_stmtContext*
CminusParser::StatementContext::return_stmt() {
    return getRuleContext<CminusParser::Return_stmtContext>(0);
}

CminusParser::ExpContext* CminusParser::StatementContext::exp() {
    return getRuleContext<CminusParser::ExpContext>(0);
}

size_t CminusParser::StatementContext::getRuleIndex() const {
    return CminusParser::RuleStatement;
}

void CminusParser::StatementContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterStatement(this);
}

void CminusParser::StatementContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitStatement(this);
}

antlrcpp::Any
CminusParser::StatementContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitStatement(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::StatementContext* CminusParser::statement() {
    StatementContext* _localctx =
        _tracker.createInstance<StatementContext>(_ctx, getState());
    enterRule(_localctx, 12, CminusParser::RuleStatement);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        setState(98);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 8, _ctx)) {
            case 1: {
                enterOuterAlt(_localctx, 1);
                setState(89);
                compound_stmt();
                break;
            }

            case 2: {
                enterOuterAlt(_localctx, 2);
                setState(90);
                selection_stmt();
                break;
            }

            case 3: {
                enterOuterAlt(_localctx, 3);
                setState(91);
                iteration_stmt();
                break;
            }

            case 4: {
                enterOuterAlt(_localctx, 4);
                setState(92);
                assignment_stmt();
                break;
            }

            case 5: {
                enterOuterAlt(_localctx, 5);
                setState(93);
                return_stmt();
                break;
            }

            case 6: {
                enterOuterAlt(_localctx, 6);
                setState(94);
                exp(0);
                setState(95);
                match(CminusParser::T__2);
                break;
            }

            case 7: {
                enterOuterAlt(_localctx, 7);
                setState(97);
                match(CminusParser::T__2);
                break;
            }

            default:
                break;
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Selection_stmtContext
//------------------------------------------------------------------

CminusParser::Selection_stmtContext::Selection_stmtContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::Selection_stmtContext::IF() {
    return getToken(CminusParser::IF, 0);
}

std::vector<CminusParser::StatementContext*>
CminusParser::Selection_stmtContext::statement() {
    return getRuleContexts<CminusParser::StatementContext>();
}

CminusParser::StatementContext*
CminusParser::Selection_stmtContext::statement(size_t i) {
    return getRuleContext<CminusParser::StatementContext>(i);
}

CminusParser::ExpContext* CminusParser::Selection_stmtContext::exp() {
    return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Relational_expContext*
CminusParser::Selection_stmtContext::relational_exp() {
    return getRuleContext<CminusParser::Relational_expContext>(0);
}

tree::TerminalNode* CminusParser::Selection_stmtContext::ELSE() {
    return getToken(CminusParser::ELSE, 0);
}

size_t CminusParser::Selection_stmtContext::getRuleIndex() const {
    return CminusParser::RuleSelection_stmt;
}

void CminusParser::Selection_stmtContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterSelection_stmt(this);
}

void CminusParser::Selection_stmtContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitSelection_stmt(this);
}

antlrcpp::Any
CminusParser::Selection_stmtContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitSelection_stmt(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Selection_stmtContext* CminusParser::selection_stmt() {
    Selection_stmtContext* _localctx =
        _tracker.createInstance<Selection_stmtContext>(_ctx, getState());
    enterRule(_localctx, 14, CminusParser::RuleSelection_stmt);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(100);
        match(CminusParser::IF);
        setState(101);
        match(CminusParser::T__3);
        setState(104);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 9, _ctx)) {
            case 1: {
                setState(102);
                exp(0);
                break;
            }

            case 2: {
                setState(103);
                relational_exp();
                break;
            }

            default:
                break;
        }
        setState(106);
        match(CminusParser::T__5);
        setState(107);
        statement();
        setState(110);
        _errHandler->sync(this);

        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 10, _ctx)) {
            case 1: {
                setState(108);
                match(CminusParser::ELSE);
                setState(109);
                statement();
                break;
            }

            default:
                break;
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Iteration_stmtContext
//------------------------------------------------------------------

CminusParser::Iteration_stmtContext::Iteration_stmtContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::Iteration_stmtContext::WHILE() {
    return getToken(CminusParser::WHILE, 0);
}

CminusParser::StatementContext*
CminusParser::Iteration_stmtContext::statement() {
    return getRuleContext<CminusParser::StatementContext>(0);
}

CminusParser::ExpContext* CminusParser::Iteration_stmtContext::exp() {
    return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Relational_expContext*
CminusParser::Iteration_stmtContext::relational_exp() {
    return getRuleContext<CminusParser::Relational_expContext>(0);
}

size_t CminusParser::Iteration_stmtContext::getRuleIndex() const {
    return CminusParser::RuleIteration_stmt;
}

void CminusParser::Iteration_stmtContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterIteration_stmt(this);
}

void CminusParser::Iteration_stmtContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitIteration_stmt(this);
}

antlrcpp::Any
CminusParser::Iteration_stmtContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitIteration_stmt(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Iteration_stmtContext* CminusParser::iteration_stmt() {
    Iteration_stmtContext* _localctx =
        _tracker.createInstance<Iteration_stmtContext>(_ctx, getState());
    enterRule(_localctx, 16, CminusParser::RuleIteration_stmt);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(112);
        match(CminusParser::WHILE);
        setState(113);
        match(CminusParser::T__3);
        setState(116);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 11, _ctx)) {
            case 1: {
                setState(114);
                exp(0);
                break;
            }

            case 2: {
                setState(115);
                relational_exp();
                break;
            }

            default:
                break;
        }
        setState(118);
        match(CminusParser::T__5);
        setState(119);
        statement();

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Assignment_stmtContext
//------------------------------------------------------------------

CminusParser::Assignment_stmtContext::Assignment_stmtContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::Assignment_stmtContext::ID() {
    return getToken(CminusParser::ID, 0);
}

std::vector<CminusParser::ExpContext*>
CminusParser::Assignment_stmtContext::exp() {
    return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Assignment_stmtContext::exp(size_t i) {
    return getRuleContext<CminusParser::ExpContext>(i);
}

size_t CminusParser::Assignment_stmtContext::getRuleIndex() const {
    return CminusParser::RuleAssignment_stmt;
}

void CminusParser::Assignment_stmtContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterAssignment_stmt(this);
}

void CminusParser::Assignment_stmtContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitAssignment_stmt(this);
}

antlrcpp::Any
CminusParser::Assignment_stmtContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitAssignment_stmt(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Assignment_stmtContext* CminusParser::assignment_stmt() {
    Assignment_stmtContext* _localctx =
        _tracker.createInstance<Assignment_stmtContext>(_ctx, getState());
    enterRule(_localctx, 18, CminusParser::RuleAssignment_stmt);
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
        setState(121);
        match(CminusParser::ID);
        setState(126);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if (_la == CminusParser::T__0) {
            setState(122);
            match(CminusParser::T__0);
            setState(123);
            exp(0);
            setState(124);
            match(CminusParser::T__1);
        }
        setState(128);
        match(CminusParser::T__8);
        setState(129);
        exp(0);
        setState(130);
        match(CminusParser::T__2);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- Return_stmtContext
//------------------------------------------------------------------

CminusParser::Return_stmtContext::Return_stmtContext(ParserRuleContext* parent,
                                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::Return_stmtContext::RETURN() {
    return getToken(CminusParser::RETURN, 0);
}

CminusParser::ExpContext* CminusParser::Return_stmtContext::exp() {
    return getRuleContext<CminusParser::ExpContext>(0);
}

size_t CminusParser::Return_stmtContext::getRuleIndex() const {
    return CminusParser::RuleReturn_stmt;
}

void CminusParser::Return_stmtContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterReturn_stmt(this);
}

void CminusParser::Return_stmtContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitReturn_stmt(this);
}

antlrcpp::Any
CminusParser::Return_stmtContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitReturn_stmt(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Return_stmtContext* CminusParser::return_stmt() {
    Return_stmtContext* _localctx =
        _tracker.createInstance<Return_stmtContext>(_ctx, getState());
    enterRule(_localctx, 20, CminusParser::RuleReturn_stmt);
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
        setState(132);
        match(CminusParser::RETURN);
        setState(134);
        _errHandler->sync(this);

        _la = _input->LA(1);
        if ((((_la & ~0x3fULL) == 0) &&
             ((1ULL << _la) &
              ((1ULL << CminusParser::T__3) | (1ULL << CminusParser::ID) |
               (1ULL << CminusParser::NUM))) != 0)) {
            setState(133);
            exp(0);
        }
        setState(136);
        match(CminusParser::T__2);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- ExpContext
//------------------------------------------------------------------

CminusParser::ExpContext::ExpContext(ParserRuleContext* parent,
                                     size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t CminusParser::ExpContext::getRuleIndex() const {
    return CminusParser::RuleExp;
}

void CminusParser::ExpContext::copyFrom(ExpContext* ctx) {
    ParserRuleContext::copyFrom(ctx);
}

//----------------- Add_expContext
//------------------------------------------------------------------

std::vector<CminusParser::ExpContext*> CminusParser::Add_expContext::exp() {
    return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Add_expContext::exp(size_t i) {
    return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::AddopContext* CminusParser::Add_expContext::addop() {
    return getRuleContext<CminusParser::AddopContext>(0);
}

CminusParser::Add_expContext::Add_expContext(ExpContext* ctx) {
    copyFrom(ctx);
}

void CminusParser::Add_expContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterAdd_exp(this);
}
void CminusParser::Add_expContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitAdd_exp(this);
}

antlrcpp::Any
CminusParser::Add_expContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitAdd_exp(this);
    else
        return visitor->visitChildren(this);
}
//----------------- Paren_expContext
//------------------------------------------------------------------

CminusParser::ExpContext* CminusParser::Paren_expContext::exp() {
    return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Relational_expContext*
CminusParser::Paren_expContext::relational_exp() {
    return getRuleContext<CminusParser::Relational_expContext>(0);
}

CminusParser::Paren_expContext::Paren_expContext(ExpContext* ctx) {
    copyFrom(ctx);
}

void CminusParser::Paren_expContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterParen_exp(this);
}
void CminusParser::Paren_expContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitParen_exp(this);
}

antlrcpp::Any
CminusParser::Paren_expContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitParen_exp(this);
    else
        return visitor->visitChildren(this);
}
//----------------- Num_expContext
//------------------------------------------------------------------

tree::TerminalNode* CminusParser::Num_expContext::NUM() {
    return getToken(CminusParser::NUM, 0);
}

CminusParser::Num_expContext::Num_expContext(ExpContext* ctx) {
    copyFrom(ctx);
}

void CminusParser::Num_expContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterNum_exp(this);
}
void CminusParser::Num_expContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitNum_exp(this);
}

antlrcpp::Any
CminusParser::Num_expContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitNum_exp(this);
    else
        return visitor->visitChildren(this);
}
//----------------- Call_expContext
//------------------------------------------------------------------

tree::TerminalNode* CminusParser::Call_expContext::ID() {
    return getToken(CminusParser::ID, 0);
}

std::vector<CminusParser::ExpContext*> CminusParser::Call_expContext::exp() {
    return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Call_expContext::exp(size_t i) {
    return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::Call_expContext::Call_expContext(ExpContext* ctx) {
    copyFrom(ctx);
}

void CminusParser::Call_expContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterCall_exp(this);
}
void CminusParser::Call_expContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitCall_exp(this);
}

antlrcpp::Any
CminusParser::Call_expContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitCall_exp(this);
    else
        return visitor->visitChildren(this);
}
//----------------- Val_expContext
//------------------------------------------------------------------

tree::TerminalNode* CminusParser::Val_expContext::ID() {
    return getToken(CminusParser::ID, 0);
}

CminusParser::ExpContext* CminusParser::Val_expContext::exp() {
    return getRuleContext<CminusParser::ExpContext>(0);
}

CminusParser::Val_expContext::Val_expContext(ExpContext* ctx) {
    copyFrom(ctx);
}

void CminusParser::Val_expContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterVal_exp(this);
}
void CminusParser::Val_expContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitVal_exp(this);
}

antlrcpp::Any
CminusParser::Val_expContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitVal_exp(this);
    else
        return visitor->visitChildren(this);
}
//----------------- Mult_expContext
//------------------------------------------------------------------

std::vector<CminusParser::ExpContext*> CminusParser::Mult_expContext::exp() {
    return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Mult_expContext::exp(size_t i) {
    return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::MultopContext* CminusParser::Mult_expContext::multop() {
    return getRuleContext<CminusParser::MultopContext>(0);
}

CminusParser::Mult_expContext::Mult_expContext(ExpContext* ctx) {
    copyFrom(ctx);
}

void CminusParser::Mult_expContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterMult_exp(this);
}
void CminusParser::Mult_expContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitMult_exp(this);
}

antlrcpp::Any
CminusParser::Mult_expContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitMult_exp(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::ExpContext* CminusParser::exp() {
    return exp(0);
}

CminusParser::ExpContext* CminusParser::exp(int precedence) {
    ParserRuleContext* parentContext = _ctx;
    size_t parentState = getState();
    CminusParser::ExpContext* _localctx =
        _tracker.createInstance<ExpContext>(_ctx, parentState);
    CminusParser::ExpContext* previousContext = _localctx;
    (void)previousContext; // Silence compiler, in case the context is not used
                           // by generated code.
    size_t startState = 22;
    enterRecursionRule(_localctx, 22, CminusParser::RuleExp, precedence);

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
        setState(167);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 18, _ctx)) {
            case 1: {
                _localctx =
                    _tracker.createInstance<Paren_expContext>(_localctx);
                _ctx = _localctx;
                previousContext = _localctx;

                setState(139);
                match(CminusParser::T__3);
                setState(142);
                _errHandler->sync(this);
                switch (
                    getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
                        _input, 14, _ctx)) {
                    case 1: {
                        setState(140);
                        exp(0);
                        break;
                    }

                    case 2: {
                        setState(141);
                        relational_exp();
                        break;
                    }

                    default:
                        break;
                }
                setState(144);
                match(CminusParser::T__5);
                break;
            }

            case 2: {
                _localctx = _tracker.createInstance<Val_expContext>(_localctx);
                _ctx = _localctx;
                previousContext = _localctx;
                setState(146);
                match(CminusParser::ID);
                setState(151);
                _errHandler->sync(this);

                switch (
                    getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
                        _input, 15, _ctx)) {
                    case 1: {
                        setState(147);
                        match(CminusParser::T__0);
                        setState(148);
                        exp(0);
                        setState(149);
                        match(CminusParser::T__1);
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
                setState(153);
                match(CminusParser::ID);
                setState(154);
                match(CminusParser::T__3);
                setState(163);
                _errHandler->sync(this);

                _la = _input->LA(1);
                if ((((_la & ~0x3fULL) == 0) &&
                     ((1ULL << _la) & ((1ULL << CminusParser::T__3) |
                                       (1ULL << CminusParser::ID) |
                                       (1ULL << CminusParser::NUM))) != 0)) {
                    setState(155);
                    exp(0);
                    setState(160);
                    _errHandler->sync(this);
                    _la = _input->LA(1);
                    while (_la == CminusParser::T__4) {
                        setState(156);
                        match(CminusParser::T__4);
                        setState(157);
                        exp(0);
                        setState(162);
                        _errHandler->sync(this);
                        _la = _input->LA(1);
                    }
                }
                setState(165);
                match(CminusParser::T__5);
                break;
            }

            case 4: {
                _localctx = _tracker.createInstance<Num_expContext>(_localctx);
                _ctx = _localctx;
                previousContext = _localctx;
                setState(166);
                match(CminusParser::NUM);
                break;
            }

            default:
                break;
        }
        _ctx->stop = _input->LT(-1);
        setState(179);
        _errHandler->sync(this);
        alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
            _input, 20, _ctx);
        while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
            if (alt == 1) {
                if (!_parseListeners.empty())
                    triggerExitRuleEvent();
                previousContext = _localctx;
                setState(177);
                _errHandler->sync(this);
                switch (
                    getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
                        _input, 19, _ctx)) {
                    case 1: {
                        auto newContext =
                            _tracker.createInstance<Mult_expContext>(
                                _tracker.createInstance<ExpContext>(
                                    parentContext, parentState));
                        _localctx = newContext;
                        pushNewRecursionContext(newContext, startState,
                                                RuleExp);
                        setState(169);

                        if (!(precpred(_ctx, 6)))
                            throw FailedPredicateException(this,
                                                           "precpred(_ctx, 6)");
                        setState(170);
                        multop();
                        setState(171);
                        exp(7);
                        break;
                    }

                    case 2: {
                        auto newContext =
                            _tracker.createInstance<Add_expContext>(
                                _tracker.createInstance<ExpContext>(
                                    parentContext, parentState));
                        _localctx = newContext;
                        pushNewRecursionContext(newContext, startState,
                                                RuleExp);
                        setState(173);

                        if (!(precpred(_ctx, 5)))
                            throw FailedPredicateException(this,
                                                           "precpred(_ctx, 5)");
                        setState(174);
                        addop();
                        setState(175);
                        exp(6);
                        break;
                    }

                    default:
                        break;
                }
            }
            setState(181);
            _errHandler->sync(this);
            alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(
                _input, 20, _ctx);
        }
    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }
    return _localctx;
}

//----------------- Relational_expContext
//------------------------------------------------------------------

CminusParser::Relational_expContext::Relational_expContext(
    ParserRuleContext* parent, size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

std::vector<CminusParser::ExpContext*>
CminusParser::Relational_expContext::exp() {
    return getRuleContexts<CminusParser::ExpContext>();
}

CminusParser::ExpContext* CminusParser::Relational_expContext::exp(size_t i) {
    return getRuleContext<CminusParser::ExpContext>(i);
}

CminusParser::RelopContext* CminusParser::Relational_expContext::relop() {
    return getRuleContext<CminusParser::RelopContext>(0);
}

size_t CminusParser::Relational_expContext::getRuleIndex() const {
    return CminusParser::RuleRelational_exp;
}

void CminusParser::Relational_expContext::enterRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterRelational_exp(this);
}

void CminusParser::Relational_expContext::exitRule(
    tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitRelational_exp(this);
}

antlrcpp::Any
CminusParser::Relational_expContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitRelational_exp(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::Relational_expContext* CminusParser::relational_exp() {
    Relational_expContext* _localctx =
        _tracker.createInstance<Relational_expContext>(_ctx, getState());
    enterRule(_localctx, 24, CminusParser::RuleRelational_exp);

#if __cplusplus > 201703L
    auto onExit = finally([=, this] {
#else
    auto onExit = finally([=] {
#endif
        exitRule();
    });
    try {
        enterOuterAlt(_localctx, 1);
        setState(182);
        exp(0);
        setState(183);
        relop();
        setState(184);
        exp(0);

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- AddopContext
//------------------------------------------------------------------

CminusParser::AddopContext::AddopContext(ParserRuleContext* parent,
                                         size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::AddopContext::ADD() {
    return getToken(CminusParser::ADD, 0);
}

tree::TerminalNode* CminusParser::AddopContext::SUB() {
    return getToken(CminusParser::SUB, 0);
}

size_t CminusParser::AddopContext::getRuleIndex() const {
    return CminusParser::RuleAddop;
}

void CminusParser::AddopContext::enterRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterAddop(this);
}

void CminusParser::AddopContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitAddop(this);
}

antlrcpp::Any
CminusParser::AddopContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitAddop(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::AddopContext* CminusParser::addop() {
    AddopContext* _localctx =
        _tracker.createInstance<AddopContext>(_ctx, getState());
    enterRule(_localctx, 26, CminusParser::RuleAddop);
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
        setState(186);
        _la = _input->LA(1);
        if (!(_la == CminusParser::ADD

              || _la == CminusParser::SUB)) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- MultopContext
//------------------------------------------------------------------

CminusParser::MultopContext::MultopContext(ParserRuleContext* parent,
                                           size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

tree::TerminalNode* CminusParser::MultopContext::MULT() {
    return getToken(CminusParser::MULT, 0);
}

tree::TerminalNode* CminusParser::MultopContext::DIV() {
    return getToken(CminusParser::DIV, 0);
}

size_t CminusParser::MultopContext::getRuleIndex() const {
    return CminusParser::RuleMultop;
}

void CminusParser::MultopContext::enterRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterMultop(this);
}

void CminusParser::MultopContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitMultop(this);
}

antlrcpp::Any
CminusParser::MultopContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitMultop(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::MultopContext* CminusParser::multop() {
    MultopContext* _localctx =
        _tracker.createInstance<MultopContext>(_ctx, getState());
    enterRule(_localctx, 28, CminusParser::RuleMultop);
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
        setState(188);
        _la = _input->LA(1);
        if (!(_la == CminusParser::MULT

              || _la == CminusParser::DIV)) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

//----------------- RelopContext
//------------------------------------------------------------------

CminusParser::RelopContext::RelopContext(ParserRuleContext* parent,
                                         size_t invokingState)
    : ParserRuleContext(parent, invokingState) {}

size_t CminusParser::RelopContext::getRuleIndex() const {
    return CminusParser::RuleRelop;
}

void CminusParser::RelopContext::enterRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->enterRelop(this);
}

void CminusParser::RelopContext::exitRule(tree::ParseTreeListener* listener) {
    auto parserListener = dynamic_cast<CminusListener*>(listener);
    if (parserListener != nullptr)
        parserListener->exitRelop(this);
}

antlrcpp::Any
CminusParser::RelopContext::accept(tree::ParseTreeVisitor* visitor) {
    if (auto parserVisitor = dynamic_cast<CminusVisitor*>(visitor))
        return parserVisitor->visitRelop(this);
    else
        return visitor->visitChildren(this);
}

CminusParser::RelopContext* CminusParser::relop() {
    RelopContext* _localctx =
        _tracker.createInstance<RelopContext>(_ctx, getState());
    enterRule(_localctx, 30, CminusParser::RuleRelop);
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
        setState(190);
        _la = _input->LA(1);
        if (!((((_la & ~0x3fULL) == 0) &&
               ((1ULL << _la) &
                ((1ULL << CminusParser::T__9) | (1ULL << CminusParser::T__10) |
                 (1ULL << CminusParser::T__11) | (1ULL << CminusParser::T__12) |
                 (1ULL << CminusParser::T__13) |
                 (1ULL << CminusParser::T__14))) != 0))) {
            _errHandler->recoverInline(this);
        } else {
            _errHandler->reportMatch(this);
            consume();
        }

    } catch (RecognitionException& e) {
        _errHandler->reportError(this, e);
        _localctx->exception = std::current_exception();
        _errHandler->recover(this, _localctx->exception);
    }

    return _localctx;
}

bool CminusParser::sempred(RuleContext* context, size_t ruleIndex,
                           size_t predicateIndex) {
    switch (ruleIndex) {
        case 11:
            return expSempred(dynamic_cast<ExpContext*>(context),
                              predicateIndex);

        default:
            break;
    }
    return true;
}

bool CminusParser::expSempred(ExpContext* _localctx, size_t predicateIndex) {
    switch (predicateIndex) {
        case 0:
            return precpred(_ctx, 6);
        case 1:
            return precpred(_ctx, 5);

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
    "program",         "var_declaration",
    "fun_declaration", "fun_type_specifier",
    "param",           "compound_stmt",
    "statement",       "selection_stmt",
    "iteration_stmt",  "assignment_stmt",
    "return_stmt",     "exp",
    "relational_exp",  "addop",
    "multop",          "relop"};

std::vector<std::string> CminusParser::_literalNames = {
    "",       "'['",  "']'",  "';'",    "'('",     "','",      "')'",
    "'{'",    "'}'",  "'='",  "'<='",   "'<'",     "'>'",      "'>='",
    "'=='",   "'!='", "'if'", "'else'", "'while'", "'return'", "'int'",
    "'void'", "'+'",  "'-'",  "'*'",    "'/'"};

std::vector<std::string> CminusParser::_symbolicNames = {
    "",     "",     "",      "",       "",        "",     "",    "",
    "",     "",     "",      "",       "",        "",     "",    "",
    "IF",   "ELSE", "WHILE", "RETURN", "INT",     "VOID", "ADD", "SUB",
    "MULT", "DIV",  "ID",    "NUM",    "COMMENT", "WS"};

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
        0x3,  0x608b, 0xa72a, 0x8133, 0xb9ed, 0x417c, 0x3be7, 0x7786, 0x5964,
        0x3,  0x1f,   0xc3,   0x4,    0x2,    0x9,    0x2,    0x4,    0x3,
        0x9,  0x3,    0x4,    0x4,    0x9,    0x4,    0x4,    0x5,    0x9,
        0x5,  0x4,    0x6,    0x9,    0x6,    0x4,    0x7,    0x9,    0x7,
        0x4,  0x8,    0x9,    0x8,    0x4,    0x9,    0x9,    0x9,    0x4,
        0xa,  0x9,    0xa,    0x4,    0xb,    0x9,    0xb,    0x4,    0xc,
        0x9,  0xc,    0x4,    0xd,    0x9,    0xd,    0x4,    0xe,    0x9,
        0xe,  0x4,    0xf,    0x9,    0xf,    0x4,    0x10,   0x9,    0x10,
        0x4,  0x11,   0x9,    0x11,   0x3,    0x2,    0x3,    0x2,    0x6,
        0x2,  0x25,   0xa,    0x2,    0xd,    0x2,    0xe,    0x2,    0x26,
        0x3,  0x2,    0x3,    0x2,    0x3,    0x3,    0x3,    0x3,    0x3,
        0x3,  0x3,    0x3,    0x3,    0x3,    0x5,    0x3,    0x30,   0xa,
        0x3,  0x3,    0x3,    0x3,    0x3,    0x3,    0x4,    0x3,    0x4,
        0x3,  0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x4,    0x7,
        0x4,  0x3a,   0xa,    0x4,    0xc,    0x4,    0xe,    0x4,    0x3d,
        0xb,  0x4,    0x3,    0x4,    0x5,    0x4,    0x40,   0xa,    0x4,
        0x3,  0x4,    0x3,    0x4,    0x3,    0x4,    0x3,    0x5,    0x3,
        0x5,  0x3,    0x6,    0x3,    0x6,    0x3,    0x6,    0x3,    0x6,
        0x5,  0x6,    0x4b,   0xa,    0x6,    0x3,    0x7,    0x3,    0x7,
        0x7,  0x7,    0x4f,   0xa,    0x7,    0xc,    0x7,    0xe,    0x7,
        0x52, 0xb,    0x7,    0x3,    0x7,    0x7,    0x7,    0x55,   0xa,
        0x7,  0xc,    0x7,    0xe,    0x7,    0x58,   0xb,    0x7,    0x3,
        0x7,  0x3,    0x7,    0x3,    0x8,    0x3,    0x8,    0x3,    0x8,
        0x3,  0x8,    0x3,    0x8,    0x3,    0x8,    0x3,    0x8,    0x3,
        0x8,  0x3,    0x8,    0x5,    0x8,    0x65,   0xa,    0x8,    0x3,
        0x9,  0x3,    0x9,    0x3,    0x9,    0x3,    0x9,    0x5,    0x9,
        0x6b, 0xa,    0x9,    0x3,    0x9,    0x3,    0x9,    0x3,    0x9,
        0x3,  0x9,    0x5,    0x9,    0x71,   0xa,    0x9,    0x3,    0xa,
        0x3,  0xa,    0x3,    0xa,    0x3,    0xa,    0x5,    0xa,    0x77,
        0xa,  0xa,    0x3,    0xa,    0x3,    0xa,    0x3,    0xa,    0x3,
        0xb,  0x3,    0xb,    0x3,    0xb,    0x3,    0xb,    0x3,    0xb,
        0x5,  0xb,    0x81,   0xa,    0xb,    0x3,    0xb,    0x3,    0xb,
        0x3,  0xb,    0x3,    0xb,    0x3,    0xc,    0x3,    0xc,    0x5,
        0xc,  0x89,   0xa,    0xc,    0x3,    0xc,    0x3,    0xc,    0x3,
        0xd,  0x3,    0xd,    0x3,    0xd,    0x3,    0xd,    0x5,    0xd,
        0x91, 0xa,    0xd,    0x3,    0xd,    0x3,    0xd,    0x3,    0xd,
        0x3,  0xd,    0x3,    0xd,    0x3,    0xd,    0x3,    0xd,    0x5,
        0xd,  0x9a,   0xa,    0xd,    0x3,    0xd,    0x3,    0xd,    0x3,
        0xd,  0x3,    0xd,    0x3,    0xd,    0x7,    0xd,    0xa1,   0xa,
        0xd,  0xc,    0xd,    0xe,    0xd,    0xa4,   0xb,    0xd,    0x5,
        0xd,  0xa6,   0xa,    0xd,    0x3,    0xd,    0x3,    0xd,    0x5,
        0xd,  0xaa,   0xa,    0xd,    0x3,    0xd,    0x3,    0xd,    0x3,
        0xd,  0x3,    0xd,    0x3,    0xd,    0x3,    0xd,    0x3,    0xd,
        0x3,  0xd,    0x7,    0xd,    0xb4,   0xa,    0xd,    0xc,    0xd,
        0xe,  0xd,    0xb7,   0xb,    0xd,    0x3,    0xe,    0x3,    0xe,
        0x3,  0xe,    0x3,    0xe,    0x3,    0xf,    0x3,    0xf,    0x3,
        0x10, 0x3,    0x10,   0x3,    0x11,   0x3,    0x11,   0x3,    0x11,
        0x2,  0x3,    0x18,   0x12,   0x2,    0x4,    0x6,    0x8,    0xa,
        0xc,  0xe,    0x10,   0x12,   0x14,   0x16,   0x18,   0x1a,   0x1c,
        0x1e, 0x20,   0x2,    0x6,    0x3,    0x2,    0x16,   0x17,   0x3,
        0x2,  0x18,   0x19,   0x3,    0x2,    0x1a,   0x1b,   0x3,    0x2,
        0xc,  0x11,   0x2,    0xce,   0x2,    0x24,   0x3,    0x2,    0x2,
        0x2,  0x4,    0x2a,   0x3,    0x2,    0x2,    0x2,    0x6,    0x33,
        0x3,  0x2,    0x2,    0x2,    0x8,    0x44,   0x3,    0x2,    0x2,
        0x2,  0xa,    0x46,   0x3,    0x2,    0x2,    0x2,    0xc,    0x4c,
        0x3,  0x2,    0x2,    0x2,    0xe,    0x64,   0x3,    0x2,    0x2,
        0x2,  0x10,   0x66,   0x3,    0x2,    0x2,    0x2,    0x12,   0x72,
        0x3,  0x2,    0x2,    0x2,    0x14,   0x7b,   0x3,    0x2,    0x2,
        0x2,  0x16,   0x86,   0x3,    0x2,    0x2,    0x2,    0x18,   0xa9,
        0x3,  0x2,    0x2,    0x2,    0x1a,   0xb8,   0x3,    0x2,    0x2,
        0x2,  0x1c,   0xbc,   0x3,    0x2,    0x2,    0x2,    0x1e,   0xbe,
        0x3,  0x2,    0x2,    0x2,    0x20,   0xc0,   0x3,    0x2,    0x2,
        0x2,  0x22,   0x25,   0x5,    0x4,    0x3,    0x2,    0x23,   0x25,
        0x5,  0x6,    0x4,    0x2,    0x24,   0x22,   0x3,    0x2,    0x2,
        0x2,  0x24,   0x23,   0x3,    0x2,    0x2,    0x2,    0x25,   0x26,
        0x3,  0x2,    0x2,    0x2,    0x26,   0x24,   0x3,    0x2,    0x2,
        0x2,  0x26,   0x27,   0x3,    0x2,    0x2,    0x2,    0x27,   0x28,
        0x3,  0x2,    0x2,    0x2,    0x28,   0x29,   0x7,    0x2,    0x2,
        0x3,  0x29,   0x3,    0x3,    0x2,    0x2,    0x2,    0x2a,   0x2b,
        0x7,  0x16,   0x2,    0x2,    0x2b,   0x2f,   0x7,    0x1c,   0x2,
        0x2,  0x2c,   0x2d,   0x7,    0x3,    0x2,    0x2,    0x2d,   0x2e,
        0x7,  0x1d,   0x2,    0x2,    0x2e,   0x30,   0x7,    0x4,    0x2,
        0x2,  0x2f,   0x2c,   0x3,    0x2,    0x2,    0x2,    0x2f,   0x30,
        0x3,  0x2,    0x2,    0x2,    0x30,   0x31,   0x3,    0x2,    0x2,
        0x2,  0x31,   0x32,   0x7,    0x5,    0x2,    0x2,    0x32,   0x5,
        0x3,  0x2,    0x2,    0x2,    0x33,   0x34,   0x5,    0x8,    0x5,
        0x2,  0x34,   0x35,   0x7,    0x1c,   0x2,    0x2,    0x35,   0x3f,
        0x7,  0x6,    0x2,    0x2,    0x36,   0x3b,   0x5,    0xa,    0x6,
        0x2,  0x37,   0x38,   0x7,    0x7,    0x2,    0x2,    0x38,   0x3a,
        0x5,  0xa,    0x6,    0x2,    0x39,   0x37,   0x3,    0x2,    0x2,
        0x2,  0x3a,   0x3d,   0x3,    0x2,    0x2,    0x2,    0x3b,   0x39,
        0x3,  0x2,    0x2,    0x2,    0x3b,   0x3c,   0x3,    0x2,    0x2,
        0x2,  0x3c,   0x40,   0x3,    0x2,    0x2,    0x2,    0x3d,   0x3b,
        0x3,  0x2,    0x2,    0x2,    0x3e,   0x40,   0x7,    0x17,   0x2,
        0x2,  0x3f,   0x36,   0x3,    0x2,    0x2,    0x2,    0x3f,   0x3e,
        0x3,  0x2,    0x2,    0x2,    0x40,   0x41,   0x3,    0x2,    0x2,
        0x2,  0x41,   0x42,   0x7,    0x8,    0x2,    0x2,    0x42,   0x43,
        0x5,  0xc,    0x7,    0x2,    0x43,   0x7,    0x3,    0x2,    0x2,
        0x2,  0x44,   0x45,   0x9,    0x2,    0x2,    0x2,    0x45,   0x9,
        0x3,  0x2,    0x2,    0x2,    0x46,   0x47,   0x7,    0x16,   0x2,
        0x2,  0x47,   0x4a,   0x7,    0x1c,   0x2,    0x2,    0x48,   0x49,
        0x7,  0x3,    0x2,    0x2,    0x49,   0x4b,   0x7,    0x4,    0x2,
        0x2,  0x4a,   0x48,   0x3,    0x2,    0x2,    0x2,    0x4a,   0x4b,
        0x3,  0x2,    0x2,    0x2,    0x4b,   0xb,    0x3,    0x2,    0x2,
        0x2,  0x4c,   0x50,   0x7,    0x9,    0x2,    0x2,    0x4d,   0x4f,
        0x5,  0x4,    0x3,    0x2,    0x4e,   0x4d,   0x3,    0x2,    0x2,
        0x2,  0x4f,   0x52,   0x3,    0x2,    0x2,    0x2,    0x50,   0x4e,
        0x3,  0x2,    0x2,    0x2,    0x50,   0x51,   0x3,    0x2,    0x2,
        0x2,  0x51,   0x56,   0x3,    0x2,    0x2,    0x2,    0x52,   0x50,
        0x3,  0x2,    0x2,    0x2,    0x53,   0x55,   0x5,    0xe,    0x8,
        0x2,  0x54,   0x53,   0x3,    0x2,    0x2,    0x2,    0x55,   0x58,
        0x3,  0x2,    0x2,    0x2,    0x56,   0x54,   0x3,    0x2,    0x2,
        0x2,  0x56,   0x57,   0x3,    0x2,    0x2,    0x2,    0x57,   0x59,
        0x3,  0x2,    0x2,    0x2,    0x58,   0x56,   0x3,    0x2,    0x2,
        0x2,  0x59,   0x5a,   0x7,    0xa,    0x2,    0x2,    0x5a,   0xd,
        0x3,  0x2,    0x2,    0x2,    0x5b,   0x65,   0x5,    0xc,    0x7,
        0x2,  0x5c,   0x65,   0x5,    0x10,   0x9,    0x2,    0x5d,   0x65,
        0x5,  0x12,   0xa,    0x2,    0x5e,   0x65,   0x5,    0x14,   0xb,
        0x2,  0x5f,   0x65,   0x5,    0x16,   0xc,    0x2,    0x60,   0x61,
        0x5,  0x18,   0xd,    0x2,    0x61,   0x62,   0x7,    0x5,    0x2,
        0x2,  0x62,   0x65,   0x3,    0x2,    0x2,    0x2,    0x63,   0x65,
        0x7,  0x5,    0x2,    0x2,    0x64,   0x5b,   0x3,    0x2,    0x2,
        0x2,  0x64,   0x5c,   0x3,    0x2,    0x2,    0x2,    0x64,   0x5d,
        0x3,  0x2,    0x2,    0x2,    0x64,   0x5e,   0x3,    0x2,    0x2,
        0x2,  0x64,   0x5f,   0x3,    0x2,    0x2,    0x2,    0x64,   0x60,
        0x3,  0x2,    0x2,    0x2,    0x64,   0x63,   0x3,    0x2,    0x2,
        0x2,  0x65,   0xf,    0x3,    0x2,    0x2,    0x2,    0x66,   0x67,
        0x7,  0x12,   0x2,    0x2,    0x67,   0x6a,   0x7,    0x6,    0x2,
        0x2,  0x68,   0x6b,   0x5,    0x18,   0xd,    0x2,    0x69,   0x6b,
        0x5,  0x1a,   0xe,    0x2,    0x6a,   0x68,   0x3,    0x2,    0x2,
        0x2,  0x6a,   0x69,   0x3,    0x2,    0x2,    0x2,    0x6b,   0x6c,
        0x3,  0x2,    0x2,    0x2,    0x6c,   0x6d,   0x7,    0x8,    0x2,
        0x2,  0x6d,   0x70,   0x5,    0xe,    0x8,    0x2,    0x6e,   0x6f,
        0x7,  0x13,   0x2,    0x2,    0x6f,   0x71,   0x5,    0xe,    0x8,
        0x2,  0x70,   0x6e,   0x3,    0x2,    0x2,    0x2,    0x70,   0x71,
        0x3,  0x2,    0x2,    0x2,    0x71,   0x11,   0x3,    0x2,    0x2,
        0x2,  0x72,   0x73,   0x7,    0x14,   0x2,    0x2,    0x73,   0x76,
        0x7,  0x6,    0x2,    0x2,    0x74,   0x77,   0x5,    0x18,   0xd,
        0x2,  0x75,   0x77,   0x5,    0x1a,   0xe,    0x2,    0x76,   0x74,
        0x3,  0x2,    0x2,    0x2,    0x76,   0x75,   0x3,    0x2,    0x2,
        0x2,  0x77,   0x78,   0x3,    0x2,    0x2,    0x2,    0x78,   0x79,
        0x7,  0x8,    0x2,    0x2,    0x79,   0x7a,   0x5,    0xe,    0x8,
        0x2,  0x7a,   0x13,   0x3,    0x2,    0x2,    0x2,    0x7b,   0x80,
        0x7,  0x1c,   0x2,    0x2,    0x7c,   0x7d,   0x7,    0x3,    0x2,
        0x2,  0x7d,   0x7e,   0x5,    0x18,   0xd,    0x2,    0x7e,   0x7f,
        0x7,  0x4,    0x2,    0x2,    0x7f,   0x81,   0x3,    0x2,    0x2,
        0x2,  0x80,   0x7c,   0x3,    0x2,    0x2,    0x2,    0x80,   0x81,
        0x3,  0x2,    0x2,    0x2,    0x81,   0x82,   0x3,    0x2,    0x2,
        0x2,  0x82,   0x83,   0x7,    0xb,    0x2,    0x2,    0x83,   0x84,
        0x5,  0x18,   0xd,    0x2,    0x84,   0x85,   0x7,    0x5,    0x2,
        0x2,  0x85,   0x15,   0x3,    0x2,    0x2,    0x2,    0x86,   0x88,
        0x7,  0x15,   0x2,    0x2,    0x87,   0x89,   0x5,    0x18,   0xd,
        0x2,  0x88,   0x87,   0x3,    0x2,    0x2,    0x2,    0x88,   0x89,
        0x3,  0x2,    0x2,    0x2,    0x89,   0x8a,   0x3,    0x2,    0x2,
        0x2,  0x8a,   0x8b,   0x7,    0x5,    0x2,    0x2,    0x8b,   0x17,
        0x3,  0x2,    0x2,    0x2,    0x8c,   0x8d,   0x8,    0xd,    0x1,
        0x2,  0x8d,   0x90,   0x7,    0x6,    0x2,    0x2,    0x8e,   0x91,
        0x5,  0x18,   0xd,    0x2,    0x8f,   0x91,   0x5,    0x1a,   0xe,
        0x2,  0x90,   0x8e,   0x3,    0x2,    0x2,    0x2,    0x90,   0x8f,
        0x3,  0x2,    0x2,    0x2,    0x91,   0x92,   0x3,    0x2,    0x2,
        0x2,  0x92,   0x93,   0x7,    0x8,    0x2,    0x2,    0x93,   0xaa,
        0x3,  0x2,    0x2,    0x2,    0x94,   0x99,   0x7,    0x1c,   0x2,
        0x2,  0x95,   0x96,   0x7,    0x3,    0x2,    0x2,    0x96,   0x97,
        0x5,  0x18,   0xd,    0x2,    0x97,   0x98,   0x7,    0x4,    0x2,
        0x2,  0x98,   0x9a,   0x3,    0x2,    0x2,    0x2,    0x99,   0x95,
        0x3,  0x2,    0x2,    0x2,    0x99,   0x9a,   0x3,    0x2,    0x2,
        0x2,  0x9a,   0xaa,   0x3,    0x2,    0x2,    0x2,    0x9b,   0x9c,
        0x7,  0x1c,   0x2,    0x2,    0x9c,   0xa5,   0x7,    0x6,    0x2,
        0x2,  0x9d,   0xa2,   0x5,    0x18,   0xd,    0x2,    0x9e,   0x9f,
        0x7,  0x7,    0x2,    0x2,    0x9f,   0xa1,   0x5,    0x18,   0xd,
        0x2,  0xa0,   0x9e,   0x3,    0x2,    0x2,    0x2,    0xa1,   0xa4,
        0x3,  0x2,    0x2,    0x2,    0xa2,   0xa0,   0x3,    0x2,    0x2,
        0x2,  0xa2,   0xa3,   0x3,    0x2,    0x2,    0x2,    0xa3,   0xa6,
        0x3,  0x2,    0x2,    0x2,    0xa4,   0xa2,   0x3,    0x2,    0x2,
        0x2,  0xa5,   0x9d,   0x3,    0x2,    0x2,    0x2,    0xa5,   0xa6,
        0x3,  0x2,    0x2,    0x2,    0xa6,   0xa7,   0x3,    0x2,    0x2,
        0x2,  0xa7,   0xaa,   0x7,    0x8,    0x2,    0x2,    0xa8,   0xaa,
        0x7,  0x1d,   0x2,    0x2,    0xa9,   0x8c,   0x3,    0x2,    0x2,
        0x2,  0xa9,   0x94,   0x3,    0x2,    0x2,    0x2,    0xa9,   0x9b,
        0x3,  0x2,    0x2,    0x2,    0xa9,   0xa8,   0x3,    0x2,    0x2,
        0x2,  0xaa,   0xb5,   0x3,    0x2,    0x2,    0x2,    0xab,   0xac,
        0xc,  0x8,    0x2,    0x2,    0xac,   0xad,   0x5,    0x1e,   0x10,
        0x2,  0xad,   0xae,   0x5,    0x18,   0xd,    0x9,    0xae,   0xb4,
        0x3,  0x2,    0x2,    0x2,    0xaf,   0xb0,   0xc,    0x7,    0x2,
        0x2,  0xb0,   0xb1,   0x5,    0x1c,   0xf,    0x2,    0xb1,   0xb2,
        0x5,  0x18,   0xd,    0x8,    0xb2,   0xb4,   0x3,    0x2,    0x2,
        0x2,  0xb3,   0xab,   0x3,    0x2,    0x2,    0x2,    0xb3,   0xaf,
        0x3,  0x2,    0x2,    0x2,    0xb4,   0xb7,   0x3,    0x2,    0x2,
        0x2,  0xb5,   0xb3,   0x3,    0x2,    0x2,    0x2,    0xb5,   0xb6,
        0x3,  0x2,    0x2,    0x2,    0xb6,   0x19,   0x3,    0x2,    0x2,
        0x2,  0xb7,   0xb5,   0x3,    0x2,    0x2,    0x2,    0xb8,   0xb9,
        0x5,  0x18,   0xd,    0x2,    0xb9,   0xba,   0x5,    0x20,   0x11,
        0x2,  0xba,   0xbb,   0x5,    0x18,   0xd,    0x2,    0xbb,   0x1b,
        0x3,  0x2,    0x2,    0x2,    0xbc,   0xbd,   0x9,    0x3,    0x2,
        0x2,  0xbd,   0x1d,   0x3,    0x2,    0x2,    0x2,    0xbe,   0xbf,
        0x9,  0x4,    0x2,    0x2,    0xbf,   0x1f,   0x3,    0x2,    0x2,
        0x2,  0xc0,   0xc1,   0x9,    0x5,    0x2,    0x2,    0xc1,   0x21,
        0x3,  0x2,    0x2,    0x2,    0x17,   0x24,   0x26,   0x2f,   0x3b,
        0x3f, 0x4a,   0x50,   0x56,   0x64,   0x6a,   0x70,   0x76,   0x80,
        0x88, 0x90,   0x99,   0xa2,   0xa5,   0xa9,   0xb3,   0xb5,
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
