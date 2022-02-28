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

#include <iostream>
#include <string>

using namespace std;

// this routine is called by readInputFile and
// by readCommandLine, one line at a time.
// The newline will be missing. This routine
// and those below must be filled in for HW2.
void scanLine(char* line, TableOfCells& symTab) {

    // strip whitespace before ID
    stripLeadingWS(line);
    lineKind validLine = getLineKind(line);

    // if first char is a valid col char and line consists of at least 3 chars
    if (validLine == VALIDLINE || validLine == BLANKLINE) {

        SS_Cell* cell = symTab.getCell({line[0], line[1]});

        // clear cell
        if (validLine == BLANKLINE) {

            cell->setError(false);
            if (cell->getKind() == EXPRESSION) {
                cell->clearCell();
                // replace the Node with an empty Node to clear controllers and
                // users
                cell->identifyControllers(new Node());
                cell->updateControllerUsers();
            } else {
                cell->clearCell();
            }

        } else {

            // move pointer to after ID
            for (unsigned int i = 0; i < 3; i++) {
                ++line;
            }

            // strip whitespace after ID
            stripLeadingWS(line);

            // if beginning of text
            if (*line == '"') {

                parseText(line, cell);

                // if beginning of number
            } else if (isIdNum(line) || *line == '-') {

                parseNumber(line, cell);

                // if beginning of equation
            } else if (*line == '=') {

                ++line;
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
            cell->calculateUserExpressions();
        }
    }

    if (validLine == INVALIDLINE) {
        cerr << "Error: Invalid cell: " << line << '\n';
    }

    return;
}

Token* getToken(char*& ch) {

    string lexeme = "";
    TokenKind kind = T_ERROR;

    bool scanned = false;
    while (*ch && !scanned) {

        lexeme += *ch;
        switch (*ch) {

            // if 'ID'
            case 'A' ... 'F': {

                // if next character is NUM
                if (isIdNum(ch + 1)) {
                    ch++;
                    lexeme += *ch;
                    kind = ID;
                    scanned = true;
                }

                break;
            }

            // if 'NUM'
            case '0' ... '9': {
                kind = NUM;

                // if next character is not NUM
                if (!isIdNum(ch + 1)) {
                    scanned = true;
                }

                break;
            }

            case '+': {
                kind = ADD;
                scanned = true;
                break;
            }

            case '-': {
                kind = SUB;
                scanned = true;
                break;
            }

            case '*': {
                kind = MULT;
                scanned = true;
                break;
            }

            case '/': {
                kind = DIV;
                scanned = true;
                break;
            }

            case '(': {
                kind = LPAREN;
                scanned = true;
                break;
            }

            case ')': {
                kind = RPAREN;
                scanned = true;
                break;
            }

            // unsupported token - create an error token with the rest of the
            // equation as the lexeme
            default: {
                lexeme = ch;
                scanned = true;
                break;
            }
        }

        ch++;
    }

    return new Token(lexeme, kind);
}

void parseText(char*& ch, SS_Cell* cell) {

    string value = "";
    // move pointer of line past the first quote
    while (*ch != '"') {
        ch++;
    }
    ch++;

    // move ch into value up to the second quote or nullptr
    while (*ch != '"' && *ch != '\r' && *ch != '\n') {
        value += *ch;
        ch++;
    }

    cell->setTXTCell(value);
}

void parseNumber(char*& ch, SS_Cell* cell) {

    string value = "";
    value += *ch;
    bool scannedValue = false;
    while (*++ch) {

        // if char is numeric and value isn't parsed yet
        if (isIdNum(ch) && !scannedValue) {
            value += *ch;

        } else {

            // if trailing chars are non-numeric and non-whitespace
            if (ASCII[(int)*ch]) {
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
    while (line[lineLen]) {
        (lineLen)++;
    }

    // if first char is '#'
    if (*line == '#') {
        // comment line - do not continue parsing
        return NOOPLINE;
    }

    // if column and row indices are valid
    if (isIdNum(line + 1) && line[2] == ' ') {

        // if first char is 'A'-'F'
        if (*line >= 'A' && *line < 'G' && lineLen > 3) {

            return VALIDLINE;

            // if line consists of ID and a single whitespace,
        } else if (lineLen == 3) {
            return BLANKLINE;
        }
    }

    if (ASCII[(int)*line] && lineLen) {
        return INVALIDLINE;
    } else {
        return NOOPLINE;
    }
}

void stripLeadingWS(char*& ch) {
    while (*ch == ' ') {
        ch++;
    }
}

bool isIdNum(char* ch) {
    // if next character is NUM
    switch (*ch) {
        case '0' ... '9': {
            return true;
        }
        default: {
            return false;
        }
    }
}
