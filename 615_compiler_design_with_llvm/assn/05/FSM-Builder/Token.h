// Token.h
// by Allyn Shell
// May 2020

#ifndef TOKEN_H
#define TOKEN_H

#include "TokenKind.h"


// Input scanner tokens
class Token {
    TokenKind kind;
    char* startCh;
    char* endCh;
    string lexeme;
    int value;
public:
    Token(TokenKind k) : kind(k), startCh(0), endCh(0),
                        lexeme(""), value(0) {}
    Token(TokenKind k, char* st, char* en) : kind(k),
                        startCh(st), endCh(en), lexeme(""), value(0) {}

    bool setLexeme(); // returns 0 on success
    string getLexeme() { return lexeme; }
    bool setValue(); // returns 0 on success
    int getValue() { return value; }
    TokenKind getKind() { return kind; }
    int getSize() { return (int)(endCh-startCh); }
    char* getStartCh() { return startCh; }
};

ostream& operator << (ostream& os, Token& tok);

#endif // TOKEN_H
