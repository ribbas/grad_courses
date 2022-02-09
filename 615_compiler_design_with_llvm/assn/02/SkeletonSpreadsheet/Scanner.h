// Scanner.h
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW2 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW2

#ifndef SCANNER_H_
#define SCANNER_H_

#include <fstream>
#include <string>

#include "SS_Cell.h"
#include "Token.h"

using namespace std;

enum command { CONTINUE, QUIT };

// These routines are in SS_Scanner_Support.cpp
void readInputFile(ifstream& ifs, TableOfCells& symTab);
command readCommandLine(TableOfCells& symTab);
void cellTests(TableOfCells& symTab);
void printUsage(const string name);
void printEntryOptions();

// These routines are defined in Scanner.cpp
void scanLine(char* line, TableOfCells& symTab);

// for HW2 Only:
void parseEquation(char*& ch, SS_Cell* cell);
void parseText(char*& ch, SS_Cell* cell);
void parseNumber(char*& ch, SS_Cell* cell);

// helper functions
int getHwIndex(char ch);
void lstrip(char*& ch);

Token* getToken(char*& ch);
// Token* getToken(char* line, char*& ch); // friend in class Token

#endif /* SCANNER_H_ */
