// Parser.h
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef PARSER_H
#define PARSER_H

#include "Token.h"
#include "Node.h"
#include "SS_Cell.h"
#include <string>
using namespace std;


class Parser {
public:

	static void parseEquation(char*& ch, SS_Cell* cell);
	static Node* equation(char*& ch);
	static Node* term(char*& ch);
	static Node* factor(char*& ch);
	static Node* parenExp(char*& ch);
	
	static Token* match(char*& ch, TokenKind expected);
	friend Token* getToken(char*& ch); // in Scanner.cpp

};

#endif // PARSER_H