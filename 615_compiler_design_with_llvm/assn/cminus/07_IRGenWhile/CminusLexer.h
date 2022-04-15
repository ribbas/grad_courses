
// Generated from
// /home/ribbas/grad_courses/615_compiler_design_with_llvm/assn/07_CPIRGenWhile/Cminus.g4
// by ANTLR 4.9

#pragma once

#include "antlr4-runtime.h"

class CminusLexer : public antlr4::Lexer {
public:
    enum {
        T__0 = 1,
        T__1 = 2,
        IF = 3,
        ELSE = 4,
        WHILE = 5,
        RETURN = 6,
        INT = 7,
        VOID = 8,
        ADD = 9,
        SUB = 10,
        MULT = 11,
        DIV = 12,
        ASN = 13,
        LB = 14,
        RB = 15,
        LP = 16,
        RP = 17,
        SEMICOLON = 18,
        COMMA = 19,
        LTE = 20,
        LT = 21,
        GT = 22,
        GTE = 23,
        EQ = 24,
        NEQ = 25,
        ID = 26,
        NUM = 27,
        COMMENT = 28,
        WS = 29
    };

    explicit CminusLexer(antlr4::CharStream* input);
    ~CminusLexer();

    virtual std::string getGrammarFileName() const override;
    virtual const std::vector<std::string>& getRuleNames() const override;

    virtual const std::vector<std::string>& getChannelNames() const override;
    virtual const std::vector<std::string>& getModeNames() const override;
    virtual const std::vector<std::string>&
    getTokenNames() const override; // deprecated, use vocabulary instead
    virtual antlr4::dfa::Vocabulary& getVocabulary() const override;

    virtual const std::vector<uint16_t> getSerializedATN() const override;
    virtual const antlr4::atn::ATN& getATN() const override;

private:
    static std::vector<antlr4::dfa::DFA> _decisionToDFA;
    static antlr4::atn::PredictionContextCache _sharedContextCache;
    static std::vector<std::string> _ruleNames;
    static std::vector<std::string> _tokenNames;
    static std::vector<std::string> _channelNames;
    static std::vector<std::string> _modeNames;

    static std::vector<std::string> _literalNames;
    static std::vector<std::string> _symbolicNames;
    static antlr4::dfa::Vocabulary _vocabulary;
    static antlr4::atn::ATN _atn;
    static std::vector<uint16_t> _serializedATN;

    // Individual action functions triggered by action() above.

    // Individual semantic predicate functions triggered by sempred() above.

    struct Initializer {
        Initializer();
    };
    static Initializer _init;
};
