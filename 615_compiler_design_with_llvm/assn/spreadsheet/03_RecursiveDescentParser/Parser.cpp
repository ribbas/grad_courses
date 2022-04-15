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

// This routine should be called by scanLine
// to parse the equation part of an equation
// line. This routine and the others below
// should be (re)written in HW3 to parse any
// spreadsheet equation according to the
// grammar rules given in the HW3 handout.
void Parser::parseEquation(char*& ch, SS_Cell* cell) {

    // strip all whitespace from equation
    ch = stripWS(ch);
    cell->setEquation(ch);

    // get first token
    lookahead = getToken(ch);

    if (lookahead->getKind() == T_ERROR) {
        std::cerr << "Error: invalid token in " << cell->getID() << '\n';
        cell->setError(true);
        return;
    }

    // start parsing equation
    Node* equationNode = equation(ch);

    if (!equationNode || equationNode->error) {
        std::cerr << "Error: invalid equation in " << cell->getID() << '\n';
        cell->setError(true);
        return;
    }

    // set equation node to the current cell
    cell->setExpNode(equationNode);

    // propagate equation throughout the table by updating their controllers
    // and users
    cell->identifyControllers(equationNode);
    cell->updateControllerUsers();
    cell->calculateExpression();

    return;
}

/*
 * Check if the TokenKind matches without updating lookahead
 */
bool Parser::peek(TokenKind expectedToken) {
    return lookahead->getKind() == expectedToken;
}

/*
 * Update lookahead token if the TokenKind matches
 */
Token* Parser::match(char*& ch, TokenKind expected) {

    if (peek(expected)) {

        Token* nextToken = lookahead;
        lookahead = getToken(ch);

        // if a non-empty error token
        if ((lookahead->getKind() == T_ERROR) &&
            (lookahead->getLexeme().length())) {
            delete nextToken;
            return nullptr;
        }
        return nextToken;

    } else {

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

    temp->tok = match(ch, tempKind);
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

    temp->tok = match(ch, tempKind);
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

        temp->tok = match(ch, lookahead->getKind());
    }

    return temp;
}

// <paren-exp> => '(' <equation> ')'
Node* Parser::parenExp(char*& ch) {

    Node* temp = new Node();
    bool imbalancedParen = false;

    // if next token is '('
    if (peek(LPAREN)) {

        Token* lparen = match(ch, LPAREN);
        if (lparen) {

            temp = equation(ch);

            // if next token is ')'
            if (peek(RPAREN)) {

                Token* rparen = match(ch, RPAREN);
                if (rparen) {

                    // if next token is ')' again
                    if (peek(RPAREN)) {
                        imbalancedParen = true;
                    }

                } else {
                    std::cerr << "Invalid token after right parenthesis\n";
                }

                delete rparen;

            } else {
                imbalancedParen = true;
            }

        } else {
            std::cerr << "Invalid token after left parenthesis\n";
        }

        delete lparen;
    }

    // if next token is '('
    if (imbalancedParen) {
        temp->error = true;
        std::cerr << "FACTOR: imbalanced parentheses: invalid arithmetic "
                     "expression\n";
    }

    return temp;
}

char* stripWS(char* input) {
    unsigned int i, j;
    char* output = input;
    for (i = 0, j = 0; i < strlen(input); i++, j++) {
        if (ASCII[(int)input[i]]) {
            output[j] = input[i];
        } else {
            j--;
        }
    }
    output[j] = 0;
    return output;
}
