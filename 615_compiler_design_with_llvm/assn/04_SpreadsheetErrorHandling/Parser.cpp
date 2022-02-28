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

        for (auto i : firstset.getSynchSet()) {
            std::cout << "<" << i << ">\n";
        }

        ostringstream oss;
        oss << "Error: Unrecognized token " << kind;
        if (kind == ID || kind == NUM) {
            oss << " " << lookahead->getLexeme();
        }
        std::cout << oss.str() << '\n';
        // errorMessage(ch, oss.str());

        firstset.merge(synchset.getSynchSet());
        for (auto i : firstset.getSynchSet()) {
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
    Node* equationNode = equation(ch, FF_List::expFollows);

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

// Node* Parser::expression(char*& ch, FF_List synchset) {
//     checkinput(ch, *FF_List::expFirsts, synchset);
//     Node* node = 0;
//     bool error_in_child = false;
//     if (not synchset.contains(lookahead->getKind())) {
//         node = term(ch, synchset + *FF_List::FF_List::termFollows);
//         if (not node)
//             error_in_child = true;
//         while (nextIs(ADD) or nextIs(SUB)) {
//             Node* temp = new Node();
//             if (temp) {
//                 temp->left = node;
//                 node = temp;
//                 node->tok = lookahead;
//                 lookahead = getToken(ch);
//                 node->right =
//                     term(ch, synchset + *FF_List::FF_List::termFollows);
//                 if (not node->right or error_in_child)
//                     delete node;
//             }
//         }
//         checkfollows(ch, synchset);
//     }
//     return node;
// }

// <equation> => <term> { <add-op> <term> }
Node* Parser::equation(char*& ch, FF_List synchset) {

    checkinput(ch, FF_List::expFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {

        node = term(ch, FF_List::termFollows);
        if (!node) {
            errorInChild = true;
        }
        // if next token is '+' or '-'
        while (nextIs(ADD) || nextIs(SUB)) {

            // rotate nodes
            Node* temp = addOp(ch, FF_List::addOpFollows);
            temp->left = node;
            temp->right = term(ch, FF_List::termFollows);
            if (!temp->right || errorInChild) {
                delete node;
            }
            node = temp;
        }
        checkfollows(ch, synchset);
    }

    return node;
}

// <add-op> => '+' | '-'
Node* Parser::addOp(char*& ch, FF_List synchset) {

    checkinput(ch, FF_List::addOpFirsts, synchset);
    Node* node = nullptr;
    if (!synchset.contains(lookahead->getKind())) {

        node = new Node();
        TokenKind nodeKind = T_ERROR;

        switch (lookahead->getKind()) {

            case ADD: {
                nodeKind = ADD;
                break;
            }

            case SUB: {
                nodeKind = SUB;
                break;
            }

            default: {
                break;
            }
        }

        node->tok = match(ch, nodeKind);
        checkfollows(ch, synchset);
    }

    return node;
}

// <term> => <factor> { <mult-op> <factor> }
Node* Parser::term(char*& ch, FF_List synchset) {

    checkinput(ch, FF_List::termFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {
        node = factor(ch, FF_List::factorFollows);

        // if next token is '*' or '/'
        while (nextIs(MULT) || nextIs(DIV)) {

            // rotate nodes
            Node* temp = mulOp(ch, FF_List::mulOpFollows);
            temp->left = node;
            temp->right = factor(ch, FF_List::factorFollows);
            if (!temp->right || errorInChild) {
                delete node;
            }
            node = temp;
        }
        checkfollows(ch, synchset);
    }
    return node;
}

// <mult-op> => '*' | '/'
Node* Parser::mulOp(char*& ch, FF_List synchset) {

    checkinput(ch, FF_List::mulOpFirsts, synchset);
    Node* node = nullptr;
    if (!synchset.contains(lookahead->getKind())) {

        node = new Node();
        TokenKind nodeKind = T_ERROR;

        switch (lookahead->getKind()) {

            case MULT: {
                nodeKind = MULT;
                break;
            }

            case DIV: {
                nodeKind = DIV;
                break;
            }

            default: {
                break;
            }
        }

        node->tok = match(ch, nodeKind);
        checkfollows(ch, synchset);
    }
    return node;
}

// <factor> => <NUM> | <ID> | <paren-exp>
Node* Parser::factor(char*& ch, FF_List synchset) {

    checkinput(ch, FF_List::factorFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {

        node = new Node();

        // if next token is '(' or ')'
        if (nextIs(LPAREN) || nextIs(RPAREN)) {

            node = parenExp(ch, FF_List::factorFollows);

            // if next token is 'NUM' or 'ID'
        } else if (nextIs(NUM) || nextIs(ID)) {

            node->tok = match(ch, lookahead->getKind());
        }
        checkfollows(ch, synchset);
    }
    return node;
}

// <paren-exp> => '(' <equation> ')'
Node* Parser::parenExp(char*& ch, FF_List synchset) {

    checkinput(ch, FF_List::parenExpFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {

        node = new Node();

        // if next token is '('
        if (nextIs(LPAREN)) {

            Token* lparen = match(ch, LPAREN);
            if (lparen) {

                node = equation(ch, FF_List::expFollows);

                // if next token is ')'
                if (nextIs(RPAREN)) {

                    Token* rparen = match(ch, RPAREN);
                    if (!rparen) {
                        errorInChild = true;
                        std::cerr << "Invalid token after right parenthesis\n";
                    }

                    delete rparen;
                }

            } else {
                errorInChild = true;
                std::cerr << "Invalid token after left parenthesis\n";
            }

            delete lparen;
        }
    }

    return node;
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
