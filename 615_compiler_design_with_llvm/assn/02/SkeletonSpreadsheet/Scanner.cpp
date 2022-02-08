// Scanner.cpp
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW2
// Modified date:
// TBD ... This is to be filled in for HW2

#include "Scanner.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// ASCII translation table for HW2
// clang-format off
const char HW2_Index[128] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 5, 3, 0, 4, 0, 6, // *, +, -, /
    2, 2, 2, 2, 2, 2, 2, 2, // 0, 1, 2, 3, 4, 5, 6, 7
    2, 2, 0, 0, 0, 0, 0, 0, // 8, 9

    0, 1, 1, 1, 1, 1, 1, 0, // A, B, C, D, E, F
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};
// clang-format on

Token* getToken(char*& ch);
Token* getToken(char* line, char*& ch);

// this routine is called by readInputFile and
// by readCommandLine, one line at a time.
// The newline will be missing. This routine
// and those below must be filled in for HW2.
void scanLine(char* line, TableOfCells& symTab) {
    // TBD ... This is to be filled in for HW2
    cout << line << '\n';
    return;
}

// This routine should be called by scanLine
// to parse the equation part of an equation
// line. This routine will be updated in HW3.
void parseEquation(char*& ch, SS_Cell* cell) {

    Token* left = getToken(ch);
    if (left->getKind() == ID) {
        cell->setLeft(left->getLexeme());
    } else {
        cout << "Error: unrecognized left ID token" << endl << flush;
    }
    delete left;

    Token* op = getToken(ch);
    int kind = op->getKind();
    if (kind == ADD) {
        cell->setOp(op_ADD);
    } else if (kind == SUB) {
        cell->setOp(op_SUB);
    } else if (kind == MULT) {
        cell->setOp(op_MULT);
    } else {
        cout << "Error: unrecognized operator token" << endl << flush;
    }
    delete op;

    Token* right = getToken(ch);
    if (right->getKind() == ID) {
        cell->setRight(right->getLexeme());
    } else {
        cout << "Error: unrecognized right ID token" << endl << flush;
    }
    delete right;

    return;
}

Token* getToken(char*& ch) {}

// Put your scanner tables here if any others are necessary.

// The getToken routine is called by the
// parseEquation routine and any of its
// future subordinate routines.
Token* getToken(char* line, char*& ch) {
    string lexeme = "";
    TokenKind kind = T_ERROR;
    try {
        // TBD ... This is be filled in for HW2
        return new Token(lexeme, kind); // temp ?
    } catch (...) {
        return new Token(lexeme, kind); // temp ?
    }
}
