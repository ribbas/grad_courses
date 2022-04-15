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
// exp       -> term add-op term | term
// add-op    -> + | -
// term      -> factor mult-op factor | factor
// mult-op   -> * | /
// factor    -> NUM | ID | paren-exp
// paren-exp -> ( exp )
//

#include "Parser.h"

#include <iostream>

using namespace std;

Token* Parser::lookahead = nullptr;
unsigned int Parser::cursor;
std::string Parser::equationName = "";
int Parser::parsedLParen;
int Parser::parsedRParen;

void Parser::parseEquation(char*& ch, SS_Cell* cell) {

    // strip all whitespace from equation
    cursor = 0;
    parsedLParen = 0;
    parsedRParen = 0;

    ch = stripWS(ch);
    equationName = ch;
    cell->setEquation(equationName);

    // get first token
    lookahead = getToken(ch);

    if (lookahead->getKind() == T_ERROR) {
        cell->setError(true);
        return;
    }

    // start parsing equation
    Node* equationNode = equation(ch, FF_List::expFollows);

    if (parsedLParen != parsedRParen) {
        std::cerr << "Error: Unbalanced parentheses\n";
        cell->setError(true);
        return;
    }

    if (!equationNode || equationNode->error) {
        cell->setError(true);
        return;
    }

    // set equation node to the current cell
    cell->setExpNode(equationNode);

    // propagate equation throughout the table by updating their
    // controllers and users
    cell->identifyControllers(equationNode);
    cell->updateControllerUsers();
    cell->calculateExpression();

    return;
}

// <equation> => <term> { <add-op> <term> }
Node* Parser::equation(char*& ch, FF_List synchset) {

    checkInput(ch, FF_List::expFirsts, synchset);
    Node* node = nullptr;
    bool errorInChild = false;
    if (!synchset.contains(lookahead->getKind())) {

        node = term(ch, (synchset + FF_List::termFollows));
        if (!node) {
            errorInChild = true;
        }
        // if next token is '+' or '-'
        while (nextIs(ADD) || nextIs(SUB)) {

            // rotate nodes
            Node* temp = addOp(ch, FF_List::addOpFollows);
            temp->left = node;
            temp->right = term(ch, (synchset + FF_List::termFollows));
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
        node = factor(ch, (synchset + FF_List::factorFollows));

        // if next token is '*' or '/'
        while (nextIs(MULT) || nextIs(DIV)) {

            // rotate nodes
            Node* temp = mulOp(ch, FF_List::mulOpFollows);
            temp->left = node;
            temp->right = factor(ch, (synchset + FF_List::factorFollows));
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
    if (!synchset.contains(lookahead->getKind())) {

        node = new Node();

        // if next token is '(' or ')'
        if (nextIs(LPAREN) || nextIs(RPAREN)) {

            node = parenExp(ch, (synchset + FF_List::parenExpFollows));
            if (!node) {
                delete node;
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

    bool errorInChild = false;
    checkInput(ch, FF_List::parenExpFirsts, synchset);
    Node* node = new Node();

    if (!synchset.contains(lookahead->getKind())) {

        // if next token is '('
        if (nextIs(LPAREN)) {

            Token* lparen = match(ch, LPAREN);
            parsedLParen++;
            if (lparen) {

                node = equation(ch, (synchset + FF_List::expFollows));
                if (!node) {
                    errorInChild = true;
                    delete node;
                }

                // if next token is ')'
                if (nextIs(RPAREN)) {
                    parsedRParen++;

                    Token* rparen = match(ch, RPAREN);
                    if (rparen) {

                        // if next token is ')' again
                        while (nextIs(RPAREN)) {
                            rparen = match(ch, RPAREN);
                            parsedRParen++;
                        }
                    }

                    delete rparen;
                }
            }

            delete lparen;
        } else {
            errorInChild = true;
        }

        checkFollows(ch, synchset);
    }

    if (errorInChild) {
        if (node) {
            node->error = true;
            delete node;
        }
    }

    return node;
}
