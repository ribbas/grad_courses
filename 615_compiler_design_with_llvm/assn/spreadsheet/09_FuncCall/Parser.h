// Parser.h
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef PARSER_H
#define PARSER_H

#include "FF_List.h"
#include "Node.h"
#include "SS_Cell.h"
#include "Token.h"

Token* getToken(char*& ch); // in Scanner.cpp

class Parser {
    static SS_Cell* cell;
    static Token* lookahead;
    static unsigned int cursor;
    static std::string equationName;
    static int parsedLParen;
    static int parsedRParen;

public:
    // the following methods are implemented in Parser_Util.cpp
    static void updateCursor();
    static char* stripWS(char* input);

    static void scanTo(char*& ch, FF_List synchset);
    static void checkInput(char*& ch, FF_List firstset, FF_List synchset);
    static void checkFollows(char*& ch, FF_List synchset);

    static bool nextIs(TokenKind expectedToken);
    static Token* match(char*& ch, TokenKind expected);
    friend Token* getToken(char*& ch); // in Scanner.cpp

    // the following methods are implemented in Parser.cpp
    static void parseEquation(char*& ch, SS_Cell* cell);

    static Node* equation(char*& ch, FF_List synchset);
    static Node* addOp(char*& ch, FF_List synchset);
    static Node* mulOp(char*& ch, FF_List synchset);
    static Node* term(char*& ch, FF_List synchset);
    static Node* factor(char*& ch, FF_List synchset);
    static Node* parenExp(char*& ch, FF_List synchset);
};

#endif // PARSER_H
