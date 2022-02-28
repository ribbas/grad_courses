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

#include "Parser.h"
#include <cstring>
#include <iostream>
#include <sstream>

using namespace std;

// Any global variables for your HW3 parser
// should be placed here.
Token* Parser::lookahead;

// scanto(synchset) throws away tokens until
// a synchronizing token is found in the sync_set.
void Parser::scanTo(char*& ch, FF_List synchset) {

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
}

// checkinput(firstset, synchset) verifies that the input token
// matches the state of the parser at the start of a function.
// If not, it produces an error message and calls scanto(synchset).
void Parser::checkInput(char*& ch, FF_List firstset, FF_List synchset) {

    TokenKind kind = lookahead->getKind();
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

        for (auto i : (firstset + synchset).getSynchSet()) {
            std::cout << "<" << i << ">\n";
        }
        scanTo(ch, (firstset + synchset));
    }
}

// checkfollows(synchset) verifies that the input token
// matches the state of the parser at the end of a function.
// If not, it produces an error message and calls scanto(synchset).
void Parser::checkFollows(char*& ch, FF_List synchset) {
    TokenKind kind = lookahead->getKind();
    if (!synchset.contains(kind)) {
        ostringstream oss;
        oss << "Error: Unrecognized token " << kind;
        if (kind == ID || kind == NUM) {
            oss << " " << lookahead->getLexeme();
        }
        // errorMessage(ch, oss.str());

        scanTo(ch, synchset);
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

// <equation> => <term> { <add-op> <term> }
Node* Parser::equation(char*& ch, FF_List synchset) {

    checkInput(ch, FF_List::expFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {

        node = term(ch, (FF_List::termFollows));
        if (!node) {
            errorInChild = true;
        }
        // if next token is '+' or '-'
        while (nextIs(ADD) || nextIs(SUB)) {

            // rotate nodes
            Node* temp = addOp(ch, (FF_List::addOpFollows));
            temp->left = node;
            temp->right = term(ch, (FF_List::termFollows));
            node = temp;
            if (!node->right || errorInChild) {
                delete node;
            }
        }
        checkFollows(ch, synchset);
    }

    return node;
}

// <add-op> => '+' | '-'
Node* Parser::addOp(char*& ch, FF_List synchset) {

    checkInput(ch, FF_List::addOpFirsts, synchset);
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
        checkFollows(ch, synchset);
    }

    return node;
}

// <term> => <factor> { <mult-op> <factor> }
Node* Parser::term(char*& ch, FF_List synchset) {

    checkInput(ch, FF_List::termFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {
        node = factor(ch, (FF_List::factorFollows));

        // if next token is '*' or '/'
        while (nextIs(MULT) || nextIs(DIV)) {

            // rotate nodes
            Node* temp = mulOp(ch, (FF_List::mulOpFollows));
            temp->left = node;
            temp->right = factor(ch, (FF_List::factorFollows));
            node = temp;
            if (!node->right || errorInChild) {
                delete node;
            }
        }
        checkFollows(ch, synchset);
    }
    return node;
}

// <mult-op> => '*' | '/'
Node* Parser::mulOp(char*& ch, FF_List synchset) {

    checkInput(ch, FF_List::mulOpFirsts, synchset);
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
        checkFollows(ch, synchset);
    }
    return node;
}

// <factor> => <NUM> | <ID> | <paren-exp>
Node* Parser::factor(char*& ch, FF_List synchset) {

    checkInput(ch, FF_List::factorFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {

        node = new Node();

        // if next token is '(' or ')'
        if (nextIs(LPAREN) || nextIs(RPAREN)) {

            node = parenExp(ch, (FF_List::parenExpFollows));
            if (!node) {
                errorInChild = true;
            }

            // if next token is 'NUM' or 'ID'
        } else if (nextIs(NUM) || nextIs(ID)) {

            node->tok = match(ch, lookahead->getKind());
        }
        checkFollows(ch, synchset);
    }
    return node;
}

// <paren-exp> => '(' <equation> ')'
Node* Parser::parenExp(char*& ch, FF_List synchset) {

    checkInput(ch, FF_List::parenExpFirsts, synchset);
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
                if (node && nextIs(RPAREN)) {

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
        checkFollows(ch, synchset);
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
