// getKeyword.cpp
//
// by Allyn Shell
// 1/2018
// This routine supports the scanner

#include "getToken.h"
#include "ASCII.h"
#include "ASCII_KW.h"
#include "Token.h"
//#define and &&

extern int KWtests;
extern int catches;


Token* getKeyword(char* input, char*& ch, char* startCh) {
	int accept = 0;
	try {
        int index = KW_Index[*ch];
	    int state = KW_State[1][index];
		while (++KWtests and state and index) {
			accept = KW_Accept[state];
			++ch;
			index = KW_Index[*ch];
			state = KW_State[state][index];
		}
		if (++KWtests and ASCII[*ch] < 4 and accept) {
            return new Token(startCh, ch, (Kind)accept);
        }            
		return getID(input, ch, startCh);
	} catch ( ... ) {
        ++catches;
		if (++KWtests and accept) return new Token(startCh, ch, (Kind)accept);
		ch = startCh;
        return getID(input, ch, startCh);
	}
}
