// getToken.cpp
//
// by Allyn Shell
// 1/2018
// These routines help scan the input stream

#include "getToken.h"
#include "ASCII.h"
//#define and &&

extern int SYMtests;
extern int catches;

// HW2 Symbol list:
//      +  –  *  /  <  <=  ==  >=  >  =  (  )  #  “ //  /*  */864761



Token* getSymbol(char* input, char*& ch, char* startCh) {
	try {
		// TBD ... This is be filled in for HW2
		return new Token(startCh, ch, SYM);
	} catch ( ... ) {
        ++catches;
		return new Token(startCh, ch, SYM);
	}
}
