// getToken.h
//
// by Allyn Shell
// 1/2018
// These routines help scan the input stream

#ifndef GETTOKEN_H_
#define GETTOKEN_H_

#include "Token.h"
#include <fstream>
using namespace std;


Token* getToken(char* input, char*& ch, char* startCh);
void printTests(ofstream& ofs);

Token* getWhiteSpace(char* input, char*& ch, char* startCh);	// 0

Token* inputError(char* input, char*& ch, char* startCh);		// 1

Token* getSymbol(char* input, char*& ch, char* startCh);		// 2

Token* getNumber(char* input, char*& ch, char* startCh);		// 3

Token* getKeyword(char* input, char*& ch, char* startCh);		// 4 & 5

Token* getID(char* input, char*& ch, char* startCh);			// (5)

#endif // GETTOKEN_H_
