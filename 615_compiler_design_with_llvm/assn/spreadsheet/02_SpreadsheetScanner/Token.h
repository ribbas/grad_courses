// Token.h
// Allyn Shell
// Feb 2018
// Modified by:
// TBD ... This is to be filled in for HW2 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW2

#ifndef TOKEN_H_
#define TOKEN_H_

#include "SS_ASCII.h"
#include <string>
using namespace std;


enum TokenKind { T_ERROR, ID, NUM, ADD, SUB, MULT, DIV };

class Token {
public:
    Token(string lex, TokenKind k) : lexeme(lex), kind(k) {}
   ~Token() {}

   friend Token* getToken(char*& ch); // in Scanner.cpp

   string getLexeme() {return lexeme;}
   TokenKind getKind() {return kind;}

private:
    string lexeme;
    TokenKind kind;
};

#endif /* TOKEN_H_ */
