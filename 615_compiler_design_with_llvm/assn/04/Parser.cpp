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

// Any global variables for your HW3 parser
// should be placed here.
Token* Parser::lookahead;

// This routine should be called by scanLine
// to parse the equation part of an equation
// line. This routine and the others below
// should be (re)written in HW3 to parse any
// spreadsheet equation according to the
// grammar rules given in the HW3 handout.
void Parser::parseEquation(char*& ch, SS_Cell* cell) {

    string equationStr = std::string(ch);
    cell->setEquation(equationStr.substr(0, equationStr.length() - 1));

    lookahead = getToken(ch);

    if (lookahead->getKind() == T_ERROR) {
        std::cout << "Error: " << cell->getID() << "\n";
        cell->setError(true);
        return;
    }

    Node* equationNode = equation(ch);

    cell->setExpNode(equationNode);
    if (equationNode->error) {
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

    if (peek(expected))

        return getToken(ch);

    else {

        std::cerr << "Unexpected token: " << expected << '\n';
        return nullptr;
    }
}

// <equation> => <term> { <add-op> <term> }
Node* Parser::equation(char*& ch) {

    Node* temp = term(ch);

    while (peek(ADD) || peek(SUB)) {

        Node* op = addOp(ch);
        op->left = temp;
        op->right = term(ch);
        temp = op;
    }

    return temp;
}

// <add-op> => '+' | '-'
Node* Parser::addOp(char*& ch) {

    Node* temp = new Node();
    TokenKind tempKind = T_ERROR;

    switch (lookahead->getKind()) {

        case ADD: {
            tempKind = ADD;
            break;
        }

        case SUB: {
            tempKind = SUB;
            break;
        }

        default: {
            break;
        }
    }

    temp->tok = lookahead;
    lookahead = match(ch, tempKind);
    return temp;
}

// <term> => <factor> { <mult-op> <factor> }
Node* Parser::term(char*& ch) {

    Node* temp = factor(ch);

    while (peek(MULT) || peek(DIV)) {

        Node* op = mulOp(ch);
        op->left = temp;
        op->right = factor(ch);
        temp = op;
    }

    return temp;
}

// <mult-op> => '*' | '/'
Node* Parser::mulOp(char*& ch) {

    Node* temp = new Node();
    TokenKind tempKind = T_ERROR;

    switch (lookahead->getKind()) {

        case MULT: {
            tempKind = MULT;
            break;
        }

        case DIV: {
            tempKind = DIV;
            break;
        }

        default: {
            break;
        }
    }

    temp->tok = lookahead;
    lookahead = match(ch, tempKind);
    return temp;
}

// <factor> => <NUM> | <ID> | <paren-exp>
Node* Parser::factor(char*& ch) {

    Node* temp = new Node();

    if (peek(LPAREN) || peek(RPAREN)) {

        temp = parenExp(ch);

    } else if (peek(NUM) || peek(ID)) {

        temp->tok = lookahead;
        lookahead = match(ch, lookahead->getKind());
    }

    return temp;
}

// <paren-exp> => '(' <equation> ')'
Node* Parser::parenExp(char*& ch) {

    Node* temp = new Node();
    bool unbalancedParen = false;

    if (peek(LPAREN)) {

        lookahead = match(ch, LPAREN);
        temp = equation(ch);

        if (peek(RPAREN)) {

            lookahead = match(ch, RPAREN);

            if (peek(RPAREN)) {
                unbalancedParen = true;
            }

        } else {
            unbalancedParen = true;
        }
    }

    if (unbalancedParen) {
        temp->error = true;
        std::cerr << "FACTOR: unbalanced parentheses: invalid arithmetic "
                     "expression\n";
    }

    return temp;
}
