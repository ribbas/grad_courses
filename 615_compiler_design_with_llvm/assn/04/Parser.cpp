// Parser.cpp
// Allyn Shell
// July 2019
//
// Modified by:
// Sabbir Ahmed
// 2/22/2022
//
// EBNF for homework parser
//  <$>         => <equation>
//  <equation>  => <term> { <add-op> <term> }
//  <add-op>    => '+' | '-'
//  <term>      => <factor> { <mult-op> <factor> }
//  <mult-op>   => '*' | '/'
//  <factor>    => <NUM> | <ID> | <paren-exp>
//  <paren-exp> => '(' <equation> ')'

#include "Parser.h"
#include "SS_Cell.h"
#include "Token.h"
#include <cstring>
#include <iostream>

using namespace std;

// Any global variables for your HW3 parser
// should be placed here.
Token* Parser::lookahead;

char* stripWS(char* input) {
    int i, j;
    char* output = input;
    for (i = 0, j = 0; i < strlen(input); i++, j++) {
        if (input[i] != ' ' && input[i] != '\n' && input[i] != '\r') {
            output[j] = input[i];
        } else {
            j--;
        }
    }
    output[j] = 0;
    return output;
}

// This routine should be called by scanLine
// to parse the equation part of an equation
// line. This routine and the others below
// should be (re)written in HW3 to parse any
// spreadsheet equation according to the
// grammar rules given in the HW3 handout.
void Parser::parseEquation(char*& ch, SS_Cell* cell) {

    cell->setEquation(stripWS(ch));

    lookahead = getToken(ch);

    if (lookahead->getKind() == T_ERROR) {
        std::cerr << "Error: invalid token in " << cell->getID() << '\n';
        cell->setError(true);
        return;
    }

    Node* equationNode = equation(ch);
    cell->setExpNode(equationNode);
    if (equationNode->error) {
        std::cerr << "Error: invalid equation in " << cell->getID() << '\n';
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

    // if next token is '+' or '-'
    while (peek(ADD) || peek(SUB)) {

        // rotate nodes
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

    // if next token is '*' or '/'
    while (peek(MULT) || peek(DIV)) {

        // rotate nodes
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

    // if next token is '(' or ')'
    if (peek(LPAREN) || peek(RPAREN)) {

        temp = parenExp(ch);

        // if next token is 'NUM' or 'ID'
    } else if (peek(NUM) || peek(ID)) {

        temp->tok = lookahead;
        lookahead = match(ch, lookahead->getKind());
    }

    return temp;
}

// <paren-exp> => '(' <equation> ')'
Node* Parser::parenExp(char*& ch) {

    Node* temp = new Node();
    bool imbalancedParen = false;

    // if next token is '('
    if (peek(LPAREN)) {

        lookahead = match(ch, LPAREN);
        temp = equation(ch);

        // if next token is ')'
        if (peek(RPAREN)) {

            lookahead = match(ch, RPAREN);

            // if next token is ')' again
            if (peek(RPAREN)) {
                imbalancedParen = true;
            }

        } else {
            imbalancedParen = true;
        }
    }

    // if next token is '('
    if (imbalancedParen) {
        temp->error = true;
        std::cerr << "FACTOR: imbalanced parentheses: invalid arithmetic "
                     "expression\n";
    }

    return temp;
}
