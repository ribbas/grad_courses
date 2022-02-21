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
        std::cout << "unexpected token \n";
    }
}

Node* Parser::equation(char*& ch) {
    std::cout << "equation\n";
    Node* temp = term(ch);
    std::cout << "back " << temp->tok->getLexeme() << '\n';
    while (lookahead->getLexeme() == "+" || lookahead->getLexeme() == "-") {
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
    if (lookahead->getLexeme() == "+") {
        std::cout << "add\n";
    } else if (lookahead->getLexeme() == "-") {
        std::cout << "sub\n";
    }
    temp->tok = lookahead;
    lookahead = match(ch, lookahead->getKind());
    return temp;
}

Node* Parser::term(char*& ch) {
    std::cout << "term\n";
    Node* temp = factor(ch);
    while (lookahead->getLexeme() == "*" || lookahead->getLexeme() == "/") {

        std::cout << "in loop\n";
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
    if (lookahead->getLexeme() == "*") {
        std::cout << "mul\n";
    } else if (lookahead->getLexeme() == "/") {
        std::cout << "div\n";
    }
    temp->tok = lookahead;
    lookahead = match(ch, lookahead->getKind());
    return temp;
}

Node* Parser::factor(char*& ch) {
    std::cout << "factor\n";
    Node* temp = new Node();
    if (lookahead->getKind() == NUM) {
        temp->tok = lookahead;
        std::cout << "num " << temp->tok->getLexeme() << '\n';
        lookahead = match(ch, lookahead->getKind());
        // lookahead = getToken(ch);
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

// Node* Parser::number(char*& ch) {
//     std::cout << "num\n";
//     return digit(ch); // only parses single digits
// }

// Node* Parser::digit(char*& ch) {
//     std::cout << "digit\n";
//     Node* temp = new Node();
//     if (lookahead->getKind() == NUM) {
//         std::cout << "huh\n";
//         temp->tok = lookahead;
//         std::cout << "token added " << lookahead->getLexeme() << '\n';
//         lookahead = getToken(ch);
//         // } else {
//         //     throw std::logic_error(
//         //         "DIGIT: missing operand: invalid arithmetic expression");
//     }
//     std::cout << "done " << temp->tok->getLexeme() << '\n';
//     return temp;
// }
