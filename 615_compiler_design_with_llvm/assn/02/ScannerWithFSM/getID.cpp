// getID.cpp
//
// by Allyn Shell
// 1/2018
// This routine supports the scanner

#include "getToken.h"
#include "ASCII.h"
//#define and &&

extern int IDtests;
extern int catches;


Token* getID(char* input, char*& ch, char* startCh) {
	try {
		while (++IDtests and ASCII[*ch] > 3) {
			*ch = (char)(*ch | ' '); // change to lower case
			++ch;
		}
		return new Token(startCh, ch, ID);
	} catch ( ... ) {
        ++catches;
		return new Token(startCh, ch, ID);
	}
}
