// getWhiteSpace.cpp
//
// by Allyn Shell
// July 2019
// This routine supports the scanner

#include "getToken.h"
#include "ASCII.h"
//#define and &&

extern int WStests;
extern int catches;

Token* getWhiteSpace(char* input, char*& ch, char* startCh) {
	try {
		while (++WStests and ! ASCII[*ch] ) ++ch;
		return new Token(startCh, ch, WS);
	} catch ( ... ) {
        ++catches;
		return new Token(startCh, ch, WS);
	}
}
