// Parser.cpp
// Allyn Shell
// July 2019
//
// Modified by:
// Sabbir Ahmed
// 2/22/2022
//
// EBNF for homework parser
//  <$>         => <exp> <eof>
//  <exp>       => <term> { <add-op> <term> }
//  <add-op>    => '+' | '-'
//  <term>      => <factor> { <mult-op> <factor> }
//  <mult-op>   => '*' | '/'
//  <factor>    => <NUM> | <ID> | <paren-exp>
//  <paren-exp> => '(' <exp> ')'
//
// Original Grammar Rules                    |    Firsts      | Follows
//  <$>       =>  <exp> <eof>                | <ID>, <NUM>, ( | <EOF>
//  <exp>     => <term> {exp'}               | <ID>, <NUM>, ( | <EOF>, )
//  {exp'}    => <+-op> <term> {exp'} | e    |    +, ', e     | <EOF>, )
//  <+-op>  => '+' | '-'                     |    +, -        | <ID>, <NUM>, (
//  <term>    =>  <fact> {term'}             | <ID>, <NUM>, ( | +, -, <EOF>, )
//  {term'}   =>  <*-op> <fact> {term'} | e  |    *, /, e     | +, -, <EOF>, )
//  <*-op> =>  '*' | '/'                     |    *, /        | <ID>, <NUM>, (
//  <fact>    =>  <ID> | <NUM> | <paren-exp> | <ID>, <NUM>, ( | *,  /, +, -,
//                                                              <EOF>, )
//  <paren-exp> => '(' <exp> ')'
//

#include "Parser.h"
#include "SS_Cell.h"
#include "Token.h"
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

// Any global variables for your HW3 parser
// should be placed here.
Token* Parser::lookahead;

// scanto(synchset) throws away tokens until
// a synchronizing token is found in the sync_set.
void Parser::scanto(char*& ch, FF_List synchset) {

    while (!synchset.contains(lookahead->getKind())) {
        TokenKind kind = lookahead->getKind();
        ostringstream oss;
        oss << "Panic Mode: Deleting token " << kind;
        if (kind == ID || kind == NUM) {
            oss << " " << lookahead->getLexeme();
        }
        std::cout << oss.str() << '\n';
        // errorMessage(ch, oss.str());

        delete lookahead;
        lookahead = getToken(ch);
    }
    std::cout << "hmm\n";
}

// checkinput(firstset, synchset) verifies that the input token
// matches the state of the parser at the start of a function.
// If not, it produces an error message and calls scanto(synchset).
void Parser::checkinput(char*& ch, FF_List firstset, FF_List synchset) {

    TokenKind kind = lookahead->getKind();
    std::cout << "looking for " << kind << '\n';
    if (!firstset.contains(kind)) {

        for (auto i : firstset.getTokenSet()) {
            std::cout << "<" << i << ">\n";
        }

        ostringstream oss;
        oss << "Error: Unrecognized token " << kind;
        if (kind == ID || kind == NUM) {
            oss << " " << lookahead->getLexeme();
        }
        std::cout << oss.str() << '\n';
        // errorMessage(ch, oss.str());

        firstset.merge(synchset.getTokenSet());
        for (auto i : firstset.getTokenSet()) {
            std::cout << "<" << i << ">\n";
        }
        scanto(ch, firstset);
    } else {
        std::cout << "found\n";
    }
}

// checkfollows(synchset) verifies that the input token
// matches the state of the parser at the end of a function.
// If not, it produces an error message and calls scanto(synchset).
void Parser::checkfollows(char*& ch, FF_List synchset) {
    TokenKind kind = lookahead->getKind();
    if (!synchset.contains(kind)) {
        ostringstream oss;
        oss << "Error: Unrecognized token " << kind;
        if (kind == ID || kind == NUM) {
            oss << " " << lookahead->getLexeme();
        }
        // errorMessage(ch, oss.str());

        scanto(ch, synchset);
    }
}

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
    Node* equationNode = equation(ch, expFollows);

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
bool Parser::nextIs(TokenKind expectedToken) {
    return lookahead->getKind() == expectedToken;
}

/*
 * Update lookahead token if the TokenKind matches
 */
Token* Parser::match(char*& ch, TokenKind expected) {

    if (nextIs(expected)) {

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
Node* Parser::equation(char*& ch, FF_List synchset) {

    checkinput(ch, expFirsts, synchset);
    Node* temp = term(ch, termFollows);

    // if next token is '+' or '-'
    while (nextIs(ADD) || nextIs(SUB)) {

        // rotate nodes
        Node* op = addOp(ch, addOpFollows);
        op->left = temp;
        op->right = term(ch, termFollows);
        temp = op;
    }

    return temp;
}

// <add-op> => '+' | '-'
Node* Parser::addOp(char*& ch, FF_List synchset) {

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
Node* Parser::term(char*& ch, FF_List synchset) {

    Node* temp = factor(ch, factorFollows);

    // if next token is '*' or '/'
    while (nextIs(MULT) || nextIs(DIV)) {

        // rotate nodes
        Node* op = mulOp(ch, mulOpFollows);
        op->left = temp;
        op->right = factor(ch, factorFollows);
        temp = op;
    }

    return temp;
}

// <mult-op> => '*' | '/'
Node* Parser::mulOp(char*& ch, FF_List synchset) {

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
Node* Parser::factor(char*& ch, FF_List synchset) {

    Node* temp = new Node();

    // if next token is '(' or ')'
    if (nextIs(LPAREN) || nextIs(RPAREN)) {

        temp = parenExp(ch, factorFollows);

        // if next token is 'NUM' or 'ID'
    } else if (nextIs(NUM) || nextIs(ID)) {

        temp->tok = match(ch, lookahead->getKind());
    }

    return temp;
}

// <paren-exp> => '(' <equation> ')'
Node* Parser::parenExp(char*& ch, FF_List synchset) {

    Node* temp = new Node();
    bool imbalancedParen = false;

    // if next token is '('
    if (nextIs(LPAREN)) {

        Token* lparen = match(ch, LPAREN);
        if (lparen) {

            temp = equation(ch, expFollows);

            // if next token is ')'
            if (nextIs(RPAREN)) {

                Token* rparen = match(ch, RPAREN);
                if (rparen) {

                    // if next token is ')' again
                    if (nextIs(RPAREN)) {
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
