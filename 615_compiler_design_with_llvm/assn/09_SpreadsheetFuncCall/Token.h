// Token.h
// Allyn Shell
// Feb 2018
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef TOKEN_H_
#define TOKEN_H_

#include "SS_ASCII.h"
#include <iostream>
#include <string>


enum TokenKind { T_ERROR, ID, NUM, ADD, SUB, MULT, DIV, LPAREN, RPAREN, T_EOF };
std::ostream& operator<<(std::ostream& os,
                         TokenKind kind); // in SS_Scanner_Support.cpp

class Token {
    friend class Parser; // contains:  Token* getToken(char*& ch);
public:
    Token(std::string lex, TokenKind k) : lexeme(lex), kind(k) {
        if (k == NUM)
            value = stoi(lex);
    }
    ~Token() {}

    friend Token* getToken(char*& ch); // in Scanner.cpp

    std::string getLexeme() {
        return lexeme;
    }
    TokenKind getKind() {
        return kind;
    }
    int getValue() {
        return value;
    }
    int getError() {
        return error;
    }

private:
    std::string lexeme;
    TokenKind kind;
    int value = 0;
    bool error = false;
};

#endif /* TOKEN_H_ */
