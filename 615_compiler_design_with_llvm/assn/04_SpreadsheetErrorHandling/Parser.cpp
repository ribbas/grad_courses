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

void Parser::parseEquation(char*& ch, SS_Cell* cell) {

    // strip all whitespace from equation
    cursor = 0;
    ch = stripWS(ch);
    equationName = ch;
    cell->setEquation(equationName);

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

    Node* temp = new Node();
    bool imbalancedParen = false;

    // if next token is '('
    if (nextIs(LPAREN)) {

        Token* lparen = match(ch, LPAREN);
        if (lparen) {

            temp = equation(ch, FF_List::expFollows);

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
