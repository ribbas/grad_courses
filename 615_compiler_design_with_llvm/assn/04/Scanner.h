// Scanner.h
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef SCANNER_H_
#define SCANNER_H_

#include <string>
#include <fstream>
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

#endif /* SCANNER_H_ */
