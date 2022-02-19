// Parser.cpp
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW3
// Modified date:
// TBD ... This is to be filled in for HW3

#include "Parser.h"
#include "SS_Cell.h"
#include "Token.h"
#include <iostream>

using namespace std;

// EBNF for homework parser
//  <$>         => <equation>
//  <equation>  => <term> { <add-op> <term> }        // remember rotation
//  <add-op>    => '+' | '-'
//  <term>      => <factor> { < mult-op> <factor> }  // remember rotation
//  <mult-op>   => '*' | '/'  		    (note this is integer division)
//  <factor>    => <NUM> | <ID> | <paren-exp>
//  <paren-exp> => '(' <equation> ')'

Token* Parser::token;
Token* getToken(char*& ch); // in Scanner.cpp

// Any global variables for your HW3 parser
// should be placed here.

// This routine should be called by scanLine
// to parse the equation part of an equation
// line. This routine and the others below
// should be (re)written in HW3 to parse any
// spreadsheet equation according to the
// grammar rules given in the HW3 handout.
void Parser::parseEquation(char*& ch, SS_Cell* cell) {

    token = getToken(ch);

    Node* node = equation(ch);
    cell->setExpNode(node);

    cell->identifyControllers(cell->getExpNode());
    cell->updateControllerUsers();
    cell->calculateExpression();

    return;
}

bool Parser::nextIs(TokenKind expectedToken) {
    return token->getKind() == expectedToken;
}

Token* Parser::match(char*& ch, TokenKind expected) {
    // TBD ... This is to be filled in for HW3
    return 0;
}

Node* Parser::equation(char*& ch) {
    // TBD ... This is to be filled in for HW3
    return 0;
}

Node* Parser::term(char*& ch) {
    // TBD ... This is to be filled in for HW3
    return 0;
}

Node* Parser::factor(char*& ch) {
    // TBD ... This is to be filled in for HW3
    return 0;
}

Node* Parser::parenExp(char*& ch) {
    // TBD ... This is to be filled in for HW3
    return 0;
}
