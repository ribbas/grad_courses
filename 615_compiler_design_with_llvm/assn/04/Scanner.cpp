// Scanner.cpp
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW2 and HW3
// Modified date:
// TBD ... This is to be filled in for HW2 and HW3

#include "Scanner.h"
#include "Parser.h"
#include "SS_Cell.h"
#include "Token.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

                // if line consists of ID and a single whitespace, clear cell
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
                        Parser::parseEquation(line, cell);
                        cell->setKind(EXPRESSION);
                        cell->calculateExpression();

                        // if cell is of any other type, it is an error cell
                    } else {
                        cell->setError(true);
                    }
                }
            }

            if (cell->getError()) {
                cell->setTXTCell("ERROR");
            }
        }
    } else if (ASCII[*line] && line_len) {
        cout << "Error: Invalid ID" << endl << flush;
    }

    return;
}

Token* getToken(char*& ch) {
    string lexeme = "";
    TokenKind kind = T_ERROR;

    lstrip(ch);
    while (*ch == ' ') {
        lexeme += *ch;
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
