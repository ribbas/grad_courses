// Scanner.h
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef SCANNER_H_
#define SCANNER_H_

#include "SS_Cell.h"
#include "Token.h"

#include <fstream>
#include <string>

using namespace std;

enum command { CONTINUE, QUIT };

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

// These routines are in SS_Scanner_Support.cpp
void readInputFile(ifstream& ifs, TableOfCells& symTab);
command readCommandLine(TableOfCells& symTab);
void cellTests(TableOfCells& symTab);
void printUsage(const string name);
void printEntryOptions();

// These routines are defined in Scanner.cpp
void scanLine(char* line, TableOfCells& symTab);

void parseText(char*& ch, SS_Cell* cell);
void parseNumber(char*& ch, SS_Cell* cell);

int getHwIndex(char ch);
void lstrip(char*& ch);

#endif /* SCANNER_H_ */
