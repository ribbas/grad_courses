// getNumber.cpp
//
// by Allyn Shell
// 1/2018
// This routine supports the scanner

#include "getToken.h"
#include "ASCII.h"
//#define and &&

extern int NUMtests;
extern int catches;


Token* getNumber(char* input, char*& ch, char* startCh) {
	try {
		while (++NUMtests and ASCII[*ch] == 3) ++ch;
		return new Token(startCh, ch, NUM);
	} catch ( ... ) {
        ++catches;
		return new Token(startCh, ch, NUM);
	}
}
