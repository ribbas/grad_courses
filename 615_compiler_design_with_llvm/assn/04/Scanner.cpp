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

    lineKind validLine = getLineKind(line);

    // if first char is a valid col char and line consists of at least 3 chars
    if (validLine == VALIDLINE || validLine == BLANKLINE) {

        // int rowIndex = getAsciiIndex(line[1]);
        string rowId{line[0], line[1]};
        SS_Cell* cell = symTab.getCell(rowId);

        // clear cell
        if (validLine == BLANKLINE) {

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
            } else if (getAsciiIndex(*line) == 2 || getAsciiIndex(*line) == 4) {

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

        if (cell->getError()) {
            cell->setDisplay("ERROR");
        } else {
            std::cout << "recalc\n";
            cell->calculateUserExpressions();
        }
    }

    if (validLine == INVALIDLINE) {
        cout << "Error: Invalid cell: " << line << '\n';
    }

    return;
}

Token* getToken(char*& ch) {

    string lexeme = "";
    TokenKind kind = T_ERROR;

    lstrip(ch);
    bool scanned = false;
    while (getAsciiIndex(*ch) && !scanned) {

        lexeme += *ch;
        switch (getAsciiIndex(*ch)) {

            // if 'ID'
            case 1: {
                // if next character is NUM
                if (getAsciiIndex(*(ch + 1)) == 2) {
                    *ch++;
                    lexeme += *ch;
                    kind = ID;
                    scanned = true;
                }
                break;
            }

            // if 'NUM'
            case 2: {
                kind = NUM;
                // if next character is not NUM
                if (!(getAsciiIndex(*(ch + 1)) == 2)) {
                    scanned = true;
                }
                break;
            }

            // if '+'
            case 3: {
                kind = ADD;
                scanned = true;
                break;
            }

            // if '-'
            case 4: {
                kind = SUB;
                scanned = true;
                break;
            }

            // if '*'
            case 5: {
                kind = MULT;
                scanned = true;
                break;
            }

            // if '/'
            case 6: {
                kind = DIV;
                scanned = true;
                break;
            }

            // if '('
            case 8: {
                kind = LPAREN;
                scanned = true;
                break;
            }

            // if ')'
            case 9: {
                kind = RPAREN;
                scanned = true;
                break;
            }

            default: {
                break;
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
        if (getAsciiIndex(*ch) == 2 && !scannedValue) {
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

lineKind getLineKind(char* line) {

    unsigned int lineLen = 0;
    // strip whitespace before ID
    lstrip(line);
    while (line[lineLen]) {
        (lineLen)++;
    }

    int colIndex = getAsciiIndex(line[0]);
    int rowIndex = getAsciiIndex(line[1]);

    // if first char is '#'
    if (colIndex == 7) {
        // comment line - do not continue parsing
        return NOOPLINE;
    }

    // if column and row indices are valid
    if (rowIndex == 2 && line[2] == ' ') {

        // if first char is 'A'-'F'
        if (colIndex == 1 && lineLen > 3) {

            return VALIDLINE;

            // if line consists of ID and a single whitespace,
        } else if (lineLen == 3) {
            return BLANKLINE;
        }
    }

    if (ASCII[*line] && lineLen) {
        return INVALIDLINE;
    } else {
        return NOOPLINE;
    }
}

int getAsciiIndex(char ch) {
    return (int)ASCII_Index[int(ch)];
}

void lstrip(char*& ch) {
    while (*ch == ' ') {
        *ch++;
    }
}
