// Scanner.cpp
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW2 and HW3
// Modified date:
// TBD ... This is to be filled in for HW2 and HW3


#include "Token.h"
#include "SS_Cell.h"
#include "Scanner.h"
#include "Parser.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

// this routine is called by readInputFile and
// by readCommandLine, one line at a time.
// The newline will be missing. This routine 
// should have been filled in for HW2.
void scanLine(char* line, TableOfCells& symTab) {
	// TBD ... HW2?
	return;
}

// The parseEquation routine has been moved to 
// Parser.cpp for HW3


// Put your scanner tables here if any.

// The getToken routine should be called by
// the parser's routines. This routine 
// should be updated for HW3 according to 
// the REs given in the HW3 handout.
Token* getToken(char* line, char*& ch) {
	string lexeme = "";
	TokenKind kind = T_ERROR;

	try {
		// TBD ... HW2?
		return new Token(lexeme, kind); // temp ?
	}
	catch (...) {
		return new Token(lexeme, kind); // temp ?
	}
}
