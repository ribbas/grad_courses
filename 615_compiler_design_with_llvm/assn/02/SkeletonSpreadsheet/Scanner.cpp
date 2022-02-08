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

    unsigned int line_len = 0;
    while (line[line_len]) {
        line_len++;
    }

    if (line_len >= 2) {

        int col_ix = (int)HW2_Index[int(line[0])];
        int row_ix = (int)HW2_Index[int(line[1])];
        string row_id{line[0], line[1]};

        // if column and row indices are valid
        if (col_ix == 1 && row_ix == 2) {

            if (line_len == 2) {

                symTab.getCell(row_id)->setKind(BLANK);
                symTab.getCell(row_id)->setDisplay("");
                cout << "CLEARED\n";

            } else if (line[2] == ' ' && line_len > 3) {

                cout << line << '\n';

                // if beginning of text
                if (line[3] == '"') {

                    symTab.getCell(row_id)->setKind(TEXT);
                    symTab.getCell(row_id)->setDisplay(line);
                    cout << symTab.getCell(row_id)->getKind() << '\n';

                    // if beginning of number
                } else if ((int)HW2_Index[int(line[3])] == 2 ||
                           (int)HW2_Index[int(line[3])] == 4) {

                    symTab.getCell(row_id)->setKind(NUMBER);
                    symTab.getCell(row_id)->setDisplay(line);
                    cout << symTab.getCell(row_id)->getKind() << '\n';

                } else {
                    cout << "ERROR\n";
                }
            }
        }
    }
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
