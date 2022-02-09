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

Token* getToken(char*& ch);

int getHwIndex(char ch) {
    return (int)HW2_Index[int(ch)];
}

void lstrip(char*&);

void lstrip(char*& ch) {
    while (*ch == ' ') {
        *ch++;
    }
}

// this routine is called by readInputFile and
// by readCommandLine, one line at a time.
// The newline will be missing. This routine
// and those below must be filled in for HW2.
void scanLine(char* line, TableOfCells& symTab) {

    lstrip(line);
    unsigned int line_len = 0;
    while (line[line_len]) {
        line_len++;
    }

    int col_ix = getHwIndex(line[0]);
    // if first character is '#'
    if (col_ix == 7) {
        // comment line - do not continue parsing
        return;
    }

    if (col_ix == 1 && line_len >= 3) {

        int row_ix = getHwIndex(line[1]);
        string row_id{line[0], line[1]};

        // if column and row indices are valid
        if (row_ix == 2) {

            if (line[2] == ' ') {

                if (line_len == 3) {

                    symTab.getCell(row_id)->setError(false);
                    symTab.getCell(row_id)->clearCell();
                    cout << "CLEARED\n";

                } else {

                    unsigned int i = 3;
                    string value = "";
                    while (line[i] == ' ') {
                        i++;
                    }

                    // if beginning of text
                    if (line[i] == '"') {

                        // move pointer of line up to the first quote
                        while (*line != '"') {
                            *line++;
                        }
                        *line++;
                        // move line into value up to the second quote or
                        // nullptr
                        while (*line && *line != '"') {
                            value += *line;
                            *line++;
                        }

                        if (*line == '"') {

                            while (*++line) {
                                if (ASCII[*line]) {
                                    symTab.getCell(row_id)->setTXTCell("ERROR");
                                    symTab.getCell(row_id)->setError(true);
                                    return;
                                }
                            }

                            symTab.getCell(row_id)->setTXTCell(value);

                        } else {

                            symTab.getCell(row_id)->setTXTCell("ERROR");
                            symTab.getCell(row_id)->setError(true);
                        }

                        // if beginning of number
                    } else if (getHwIndex(line[i]) == 2 ||
                               getHwIndex(line[i]) == 4) {

                        value += line[i];
                        lstrip(line);
                        bool scannedValue = false;
                        while (line[++i]) {
                            // if char is numeric and value isn't parsed yet
                            if (getHwIndex(line[i]) == 2 && !scannedValue) {
                                value += line[i];

                            } else {

                                // if trailing chars are non-numeric and
                                // non-whitespace
                                if (ASCII[line[i]]) {
                                    // label cell as an error cell
                                    symTab.getCell(row_id)->setTXTCell("ERROR");
                                    symTab.getCell(row_id)->setError(true);
                                    return;

                                    // if whitespace is found after the value
                                    // was scanned
                                } else {
                                    // any chars, numeric or not, after this
                                    // results in a parse error
                                    scannedValue = true;
                                }
                            }
                        }

                        symTab.getCell(row_id)->setNUMCell(value);

                        // if beginning of equation
                    } else if (line[i] == '=') {

                        char* test = line;
                        i++;
                        memcpy(test, &line[i], line_len + 1);

                        auto cell = symTab.getCell(row_id);
                        parseEquation(line, cell);
                        cell->setKind(EXPRESSION);
                        cell->calculateExpression();

                        // if cell is of any other type, it is an error cell
                    } else {
                        symTab.getCell(row_id)->setTXTCell("ERROR");
                        symTab.getCell(row_id)->setError(true);
                    }
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

Token* getToken(char*& ch) {
    string lexeme = "";
    TokenKind kind = T_ERROR;

    // std::cout << "A |" << ch << '\n';
    lstrip(ch);
    // std::cout << "B |" << ch << '\n';

    unsigned int i = 0;
    bool scanned = false;
    while (getHwIndex(*ch) && !scanned) {

        if (getHwIndex(*ch) == 3) {
            kind = ADD;
            lexeme = *ch;
            // cout << "ADD|" << lexeme << "|\n";
            scanned = true;
        } else if (getHwIndex(*ch) == 4) {
            kind = SUB;
            lexeme = *ch;
            // cout << "SUB|" << lexeme << "|\n";
            scanned = true;
        } else if (getHwIndex(*ch) == 5) {
            kind = MULT;
            lexeme = *ch;
            // cout << "MULT|" << lexeme << "|\n";
            scanned = true;
        } else if (getHwIndex(*ch) == 6) {
            kind = DIV;
            lexeme = *ch;
            // cout << "DIV|" << lexeme << "|\n";
            scanned = true;
        } else if (getHwIndex(*ch) == 1 || getHwIndex(*ch) == 2) {
            lexeme += *ch;
            if (getHwIndex(*ch) == 2) {
                kind = ID;
                // cout << "ID|" << lexeme << "|\n";
                scanned = true;
            }
        }

        *ch++;
        i++;
    }
    // cout << "LEX|" << lexeme << "|\n";

    return new Token(lexeme, kind); // temp ?
}

// Put your scanner tables here if any others are necessary.

// The getToken routine is called by the
// parseEquation routine and any of its
// future subordinate routines.
Token* getToken(char* line, char*& ch) {}
