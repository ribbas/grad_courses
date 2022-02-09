// Scanner.cpp
// Allyn Shell
// July 2019
// Modified by:
// Sabbir Ahmed
// Modified date:
// 2/2022

#include "Scanner.h"
#include <fstream>
#include <iostream>
#include <string.h>
#include <string>

using namespace std;

// ASCII translation table for HW2
// clang-format off
const char HW2_Index[128] = {
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,

    0, 0, 0, 7, 0, 0, 0, 0, // #
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

int getHwIndex(char);
void lstrip(char*&);

Token* getToken(char*& ch);
void parseText(char*&, SS_Cell*);
void parseNumber(char*&, SS_Cell*);

// this routine is called by readInputFile and
// by readCommandLine, one line at a time.
// The newline will be missing. This routine
// and those below must be filled in for HW2.
void scanLine(char* line, TableOfCells& symTab) {

    // strip whitespace before ID
    lstrip(line);
    unsigned int line_len = 0;
    while (line[line_len]) {
        line_len++;
    }

    int col_ix = getHwIndex(line[0]);

    // if first char is '#'
    if (col_ix == 7) {
        // comment line - do not continue parsing
        return;
    }

    // if first char is a valid col char and line consists of at least 3 chars
    if (col_ix == 1 && line_len >= 3) {

        int row_ix = getHwIndex(line[1]);
        string row_id{line[0], line[1]};

        // if column and row indices are valid
        if (row_ix == 2) {

            SS_Cell* cell = symTab.getCell(row_id);

            if (line[2] == ' ') {

                // if line consists of ID and a single whitespace, clear the
                // cell
                if (line_len == 3) {

                    cell->setError(false);
                    cell->clearCell();

                } else {

                    // move pointer to after ID
                    for (unsigned int i = 0; i < 3; i++) {
                        *++line;
                    }
                    // strip whitespace after ID
                    lstrip(line);

                    // if beginning of text
                    if (*line == '"') {

                        parseText(line, cell);

                        // if beginning of number
                    } else if (getHwIndex(*line) == 2 ||
                               getHwIndex(*line) == 4) {

                        parseNumber(line, cell);

                        // if beginning of equation
                    } else if (*line == '=') {

                        *++line;
                        parseEquation(line, cell);
                        cell->setKind(EXPRESSION);
                        cell->calculateExpression();

                        // if cell is of any other type, it is an error cell
                    } else {
                        cell->setError(true);
                    }
                }
            }

            if (cell->isError()) {
                cell->setTXTCell("ERROR");
            }
        }
    } else if (ASCII[*line] && line_len) {
        cout << "Error: Invalid ID" << endl << flush;
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

Token* getToken(char*& ch) {
    string lexeme = "";
    TokenKind kind = T_ERROR;

    lstrip(ch);
    bool scanned = false;
    while (getHwIndex(*ch) && !scanned) {

        if (getHwIndex(*ch) == 3) {
            kind = ADD;
            lexeme = *ch;
            scanned = true;
        } else if (getHwIndex(*ch) == 4) {
            kind = SUB;
            lexeme = *ch;
            scanned = true;
        } else if (getHwIndex(*ch) == 5) {
            kind = MULT;
            lexeme = *ch;
            scanned = true;
        } else if (getHwIndex(*ch) == 6) {
            kind = DIV;
            lexeme = *ch;
            scanned = true;
        } else if (getHwIndex(*ch) == 1 || getHwIndex(*ch) == 2) {
            lexeme += *ch;
            if (getHwIndex(*ch) == 2) {
                kind = ID;
                scanned = true;
            }
        }

        *ch++;
    }

    return new Token(lexeme, kind);
}

void parseText(char*& ch, SS_Cell* cell) {

    string value = "";
    // move pointer of line up to the first quote
    while (*ch != '"') {
        *ch++;
    }
    *ch++;

    // move ch into value up to the second quote or nullptr
    while (*ch && *ch != '"') {
        value += *ch;
        *ch++;
    }

    if (*ch == '"') {

        // if more chars present after second quote
        while (*++ch) {
            // if non-whitespace char, label as an error cell
            if (ASCII[*ch]) {
                cell->setError(true);
                return;
            }
        }

        cell->setTXTCell(value);

    } else {

        cell->setError(true);
    }
}

void parseNumber(char*& ch, SS_Cell* cell) {

    string value = "";
    value += *ch;
    bool scannedValue = false;
    while (*++ch) {

        // if char is numeric and value isn't parsed yet
        if (getHwIndex(*ch) == 2 && !scannedValue) {
            value += *ch;

        } else {

            // if trailing chars are non-numeric and non-whitespace
            if (ASCII[*ch]) {
                // label cell as an error cell
                cell->setError(true);
                return;

                // if whitespace is found after the value was scanned
            } else {
                // any chars, numeric or not, after this results in a parse
                // error
                scannedValue = true;
            }
        }
    }

    cell->setNUMCell(value);
}

int getHwIndex(char ch) {
    return (int)HW2_Index[int(ch)];
}

void lstrip(char*& ch) {
    while (*ch == ' ') {
        *ch++;
    }
}

// Put your scanner tables here if any others are necessary.

// The getToken routine is called by the
// parseEquation routine and any of its
// future subordinate routines.
Token* getToken(char* line, char*& ch) {}
