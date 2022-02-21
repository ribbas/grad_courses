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

    if (peek(expected))
        return getToken(ch);
    else {
        std::cerr << "Unexpected token: " << expected << '\n';
        return nullptr;
    }
}

Node* Parser::equation(char*& ch) {
    std::cout << "equation\n";
    Node* temp = term(ch);
    std::cout << "back " << temp->tok->getLexeme() << '\n';
    while (lookahead->getKind() == ADD || lookahead->getKind() == SUB) {
        std::cout << "in loop\n";
        Node* op = addOp(ch);
        op->left = temp;
        op->right = term(ch);
        temp = op;
    }
    std::cout << "out of loop " << lookahead->getLexeme() << '\n';
    return temp;
}

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

Node* Parser::term(char*& ch) {
    std::cout << "term\n";
    Node* temp = factor(ch);
    while (lookahead->getKind() == MULT || lookahead->getKind() == DIV) {
        Node* op = mulOp(ch);
        op->left = temp;
        op->right = factor(ch);
        temp = op;
    }
    std::cout << "/term\n";
    return temp;
}

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

Node* Parser::factor(char*& ch) {
    std::cout << "factor\n";
    Node* temp = new Node();
    if (lookahead->getKind() == NUM || lookahead->getKind() == ID) {
        temp->tok = lookahead;
        std::cout << "num " << temp->tok->getLexeme() << '\n';
        lookahead = match(ch, lookahead->getKind());
    } else {
        std::cout << "WOT " << lookahead->getKind() << '\n';
    }
    std::cout << "/factor\n";
    return temp;

    // if (lookahead->getLexeme() == "(") {
    //     lookahead = getToken(ch);
    //     temp = equation(ch);
    //     if (lookahead->getLexeme() == ")") {
    //         lookahead = getToken(ch);
    //     } else {
    //         throw std::logic_error("FACTOR: unbalanced parentheses: invalid "
    //                                "arithmetic expression");
    //     }
    // } else {
    //     temp = number(ch);
    // }
    // std::cout << "back " << temp->tok->getLexeme() << '\n';
    // return temp;
}
