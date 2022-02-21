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
//  <equation>  => <term> { <add-op> <term> }
//  <add-op>    => '+' | '-'
//  <term>      => <factor> { <mult-op> <factor> }
//  <mult-op>   => '*' | '/'
//  <factor>    => <NUM> | <ID> | <paren-exp>
//  <paren-exp> => '(' <equation> ')'

// BNF
//  <$>         => <equation>
//  <equation>  => <term> <equation-repr>
//  <equation-repr>  => <add-op> <term> <equation-repr> | e
//  <add-op>    => '+' | '-'
//  <term>      => <factor> <factor-repr>
//  <factor-repr>  => <mult-op> <factor> <factor-repr> | e
//  <mult-op>   => '*' | '/'
//  <factor>    => <NUM> | <ID> | <paren-exp>
//  <paren-exp> => '(' <equation> ')'

Token* Parser::lookahead;

// Any global variables for your HW3 parser
// should be placed here.

// This routine should be called by scanLine
// to parse the equation part of an equation
// line. This routine and the others below
// should be (re)written in HW3 to parse any
// spreadsheet equation according to the
// grammar rules given in the HW3 handout.
void Parser::parseEquation(char*& ch, SS_Cell* cell) {

    lookahead = getToken(ch);
    std::cout << "token " << lookahead->getLexeme() << lookahead->getKind()
              << '\n';

    Node* node = equation(ch);
    cell->setExpNode(node);
    if (!node) {
        std::cout << "Error: " << cell->getID() << "\n";
        cell->setError(true);
        return;
    }

    cell->identifyControllers(cell->getExpNode());
    cell->updateControllerUsers();
    cell->calculateExpression();

    return;
}

bool Parser::peek(TokenKind expectedToken) {
    return lookahead->getKind() == expectedToken;
}

Token* Parser::match(char*& ch, TokenKind expected) {
    if (peek(expected)) {
        return getToken(ch);
    } else {
        return nullptr;
    }
}

Node* Parser::equation(char*& ch) {

    Node* temp = nullptr;
    while (peek(ADD) || peek(SUB)) {
        std::cout << "inside " << '\n';
        Node* op = addOp(ch);
        op->right = temp;
        op->tok = getToken(ch);
        temp = op;
    }
    std::cout << "here " << '\n';
    return temp;
}

Node* Parser::addOp(char*& ch) {

    Node* op = nullptr;
    Token* temp = nullptr;

    switch (lookahead->getKind()) {
        case ADD: {
            temp = match(ch, ADD);
            break;
        }
        case SUB: {
            temp = match(ch, SUB);
            break;
        }
        default: {
            return 0;
            break;
        }
    }
    op->tok = temp;
    return op;
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
