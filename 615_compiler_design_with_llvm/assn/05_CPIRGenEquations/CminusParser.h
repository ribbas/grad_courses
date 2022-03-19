
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/05_CPIRGenEquations/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "antlr4-runtime.h"

class CminusParser : public antlr4::Parser {
public:
    enum {
        T__0 = 1,
        T__1 = 2,
        T__2 = 3,
        T__3 = 4,
        T__4 = 5,
        T__5 = 6,
        T__6 = 7,
        T__7 = 8,
        T__8 = 9,
        T__9 = 10,
        T__10 = 11,
        T__11 = 12,
        T__12 = 13,
        T__13 = 14,
        T__14 = 15,
        IF = 16,
        ELSE = 17,
        WHILE = 18,
        RETURN = 19,
        INT = 20,
        VOID = 21,
        ADD = 22,
        SUB = 23,
        MULT = 24,
        DIV = 25,
        ID = 26,
        NUM = 27,
        COMMENT = 28,
        WS = 29
    };

    enum {
        RuleProgram = 0,
        RuleVar_declaration = 1,
        RuleFun_declaration = 2,
        RuleFun_type_specifier = 3,
        RuleParam = 4,
        RuleCompound_stmt = 5,
        RuleStatement = 6,
        RuleSelection_stmt = 7,
        RuleIteration_stmt = 8,
        RuleAssignment_stmt = 9,
        RuleReturn_stmt = 10,
        RuleExp = 11,
        RuleRelational_exp = 12,
        RuleAddop = 13,
        RuleMultop = 14,
        RuleRelop = 15
    };

    explicit CminusParser(antlr4::TokenStream* input);
    ~CminusParser();

    virtual std::string getGrammarFileName() const override;
    virtual const antlr4::atn::ATN& getATN() const override {
        return _atn;
    };
    virtual const std::vector<std::string>& getTokenNames() const override {
        return _tokenNames;
    }; // deprecated: use vocabulary instead.
    virtual const std::vector<std::string>& getRuleNames() const override;
    virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

    class ProgramContext;
    class Var_declarationContext;
    class Fun_declarationContext;
    class Fun_type_specifierContext;
    class ParamContext;
    class Compound_stmtContext;
    class StatementContext;
    class Selection_stmtContext;
    class Iteration_stmtContext;
    class Assignment_stmtContext;
    class Return_stmtContext;
    class ExpContext;
    class Relational_expContext;
    class AddopContext;
    class MultopContext;
    class RelopContext;

    class ProgramContext : public antlr4::ParserRuleContext {
    public:
        ProgramContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* EOF();
        std::vector<Var_declarationContext*> var_declaration();
        Var_declarationContext* var_declaration(size_t i);
        std::vector<Fun_declarationContext*> fun_declaration();
        Fun_declarationContext* fun_declaration(size_t i);

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ProgramContext* program();

    class Var_declarationContext : public antlr4::ParserRuleContext {
    public:
        Var_declarationContext(antlr4::ParserRuleContext* parent,
                               size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* INT();
        antlr4::tree::TerminalNode* ID();
        antlr4::tree::TerminalNode* NUM();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Var_declarationContext* var_declaration();

    class Fun_declarationContext : public antlr4::ParserRuleContext {
    public:
        Fun_declarationContext(antlr4::ParserRuleContext* parent,
                               size_t invokingState);
        virtual size_t getRuleIndex() const override;
        Fun_type_specifierContext* fun_type_specifier();
        antlr4::tree::TerminalNode* ID();
        Compound_stmtContext* compound_stmt();
        std::vector<ParamContext*> param();
        ParamContext* param(size_t i);
        antlr4::tree::TerminalNode* VOID();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Fun_declarationContext* fun_declaration();

    class Fun_type_specifierContext : public antlr4::ParserRuleContext {
    public:
        Fun_type_specifierContext(antlr4::ParserRuleContext* parent,
                                  size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* INT();
        antlr4::tree::TerminalNode* VOID();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Fun_type_specifierContext* fun_type_specifier();

    class ParamContext : public antlr4::ParserRuleContext {
    public:
        ParamContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* INT();
        antlr4::tree::TerminalNode* ID();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ParamContext* param();

    class Compound_stmtContext : public antlr4::ParserRuleContext {
    public:
        Compound_stmtContext(antlr4::ParserRuleContext* parent,
                             size_t invokingState);
        virtual size_t getRuleIndex() const override;
        std::vector<Var_declarationContext*> var_declaration();
        Var_declarationContext* var_declaration(size_t i);
        std::vector<StatementContext*> statement();
        StatementContext* statement(size_t i);

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Compound_stmtContext* compound_stmt();

    class StatementContext : public antlr4::ParserRuleContext {
    public:
        StatementContext(antlr4::ParserRuleContext* parent,
                         size_t invokingState);
        virtual size_t getRuleIndex() const override;
        Compound_stmtContext* compound_stmt();
        Selection_stmtContext* selection_stmt();
        Iteration_stmtContext* iteration_stmt();
        Assignment_stmtContext* assignment_stmt();
        Return_stmtContext* return_stmt();
        ExpContext* exp();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    StatementContext* statement();

    class Selection_stmtContext : public antlr4::ParserRuleContext {
    public:
        Selection_stmtContext(antlr4::ParserRuleContext* parent,
                              size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* IF();
        std::vector<StatementContext*> statement();
        StatementContext* statement(size_t i);
        ExpContext* exp();
        Relational_expContext* relational_exp();
        antlr4::tree::TerminalNode* ELSE();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Selection_stmtContext* selection_stmt();

    class Iteration_stmtContext : public antlr4::ParserRuleContext {
    public:
        Iteration_stmtContext(antlr4::ParserRuleContext* parent,
                              size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* WHILE();
        StatementContext* statement();
        ExpContext* exp();
        Relational_expContext* relational_exp();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Iteration_stmtContext* iteration_stmt();

    class Assignment_stmtContext : public antlr4::ParserRuleContext {
    public:
        Assignment_stmtContext(antlr4::ParserRuleContext* parent,
                               size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* ID();
        std::vector<ExpContext*> exp();
        ExpContext* exp(size_t i);

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Assignment_stmtContext* assignment_stmt();

    class Return_stmtContext : public antlr4::ParserRuleContext {
    public:
        Return_stmtContext(antlr4::ParserRuleContext* parent,
                           size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* RETURN();
        ExpContext* exp();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Return_stmtContext* return_stmt();

    class ExpContext : public antlr4::ParserRuleContext {
    public:
        ExpContext(antlr4::ParserRuleContext* parent, size_t invokingState);

        ExpContext() = default;
        void copyFrom(ExpContext* context);
        using antlr4::ParserRuleContext::copyFrom;

        virtual size_t getRuleIndex() const override;
    };

    class Add_expContext : public ExpContext {
    public:
        Add_expContext(ExpContext* ctx);

        std::vector<ExpContext*> exp();
        ExpContext* exp(size_t i);
        AddopContext* addop();
        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class Paren_expContext : public ExpContext {
    public:
        Paren_expContext(ExpContext* ctx);

        ExpContext* exp();
        Relational_expContext* relational_exp();
        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class Num_expContext : public ExpContext {
    public:
        Num_expContext(ExpContext* ctx);

        antlr4::tree::TerminalNode* NUM();
        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class Call_expContext : public ExpContext {
    public:
        Call_expContext(ExpContext* ctx);

        antlr4::tree::TerminalNode* ID();
        std::vector<ExpContext*> exp();
        ExpContext* exp(size_t i);
        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class Val_expContext : public ExpContext {
    public:
        Val_expContext(ExpContext* ctx);

        antlr4::tree::TerminalNode* ID();
        ExpContext* exp();
        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    class Mult_expContext : public ExpContext {
    public:
        Mult_expContext(ExpContext* ctx);

        std::vector<ExpContext*> exp();
        ExpContext* exp(size_t i);
        MultopContext* multop();
        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    ExpContext* exp();
    ExpContext* exp(int precedence);
    class Relational_expContext : public antlr4::ParserRuleContext {
    public:
        Relational_expContext(antlr4::ParserRuleContext* parent,
                              size_t invokingState);
        virtual size_t getRuleIndex() const override;
        std::vector<ExpContext*> exp();
        ExpContext* exp(size_t i);
        RelopContext* relop();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    Relational_expContext* relational_exp();

    class AddopContext : public antlr4::ParserRuleContext {
    public:
        AddopContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* ADD();
        antlr4::tree::TerminalNode* SUB();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    AddopContext* addop();

    class MultopContext : public antlr4::ParserRuleContext {
    public:
        MultopContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;
        antlr4::tree::TerminalNode* MULT();
        antlr4::tree::TerminalNode* DIV();

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    MultopContext* multop();

    class RelopContext : public antlr4::ParserRuleContext {
    public:
        RelopContext(antlr4::ParserRuleContext* parent, size_t invokingState);
        virtual size_t getRuleIndex() const override;

        virtual void
        enterRule(antlr4::tree::ParseTreeListener* listener) override;
        virtual void
        exitRule(antlr4::tree::ParseTreeListener* listener) override;

        virtual antlrcpp::Any
        accept(antlr4::tree::ParseTreeVisitor* visitor) override;
    };

    RelopContext* relop();

    virtual bool sempred(antlr4::RuleContext* _localctx, size_t ruleIndex,
                         size_t predicateIndex) override;
    bool expSempred(ExpContext* _localctx, size_t predicateIndex);

private:
    static std::vector<antlr4::dfa::DFA> _decisionToDFA;
    static antlr4::atn::PredictionContextCache _sharedContextCache;
    static std::vector<std::string> _ruleNames;
    static std::vector<std::string> _tokenNames;

    static std::vector<std::string> _literalNames;
    static std::vector<std::string> _symbolicNames;
    static antlr4::dfa::Vocabulary _vocabulary;
    static antlr4::atn::ATN _atn;
    static std::vector<uint16_t> _serializedATN;

    struct Initializer {
        Initializer();
    };
    static Initializer _init;
};
