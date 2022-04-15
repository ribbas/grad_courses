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
enum lineKind { BLANKLINE, NOOPLINE, VALIDLINE, INVALIDLINE }; // line kind

// These routines are in SS_Scanner_Support.cpp
void readInputFile(ifstream& ifs, TableOfCells& symTab);
command readCommandLine(TableOfCells& symTab);
void cellTests(TableOfCells& symTab);
void printUsage(const string name);
void printEntryOptions();

lineKind getLineKind(char* line);
void stripLeadingWS(char*& ch);
bool isIdNum(char* ch);

void parseText(char*& ch, SS_Cell* cell);
void parseNumber(char*& ch, SS_Cell* cell);

void scanLine(char* line, TableOfCells& symTab);

#endif /* SCANNER_H_ */
