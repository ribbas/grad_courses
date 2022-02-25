// getToken.cpp
//
// by Allyn Shell
// 1/2018
// This routine supports the scanner

#include "getToken.h"
#include "ASCII.h"
#include <iostream>
using namespace std;
//#define and &&

int tests = 0;
int catches = 0;
int WStests = 0;
int SYMtests = 0;
int NUMtests = 0;
int KWtests = 0;
int IDtests = 0;
int tokens = 0;
int UNKtok = 0;
int WStok = 0;
int SYMtok = 0;
int NUMtok = 0;
int KWtok = 0;
int IDtok = 0;


Token* getToken(char* input, char*& ch, char* startCh) {

	typedef Token* (*getTokenFunctionPointer)(char* input, char*& ch, char* startCh);
	const getTokenFunctionPointer jumpTable[] = {
			getWhiteSpace,
			inputError,
			getSymbol,
			getNumber,
			getKeyword,
			getKeyword };

	try {
		// while ( ! ASCII[*ch]) ++ch; // discard whitespace
		// jump to designated getToken function
        ++tests;
		return jumpTable[ASCII[*ch]](input, ch, ch);
	}
	catch ( ... ) {
		++catches;
        if ( ! ch ) return 0; // end of input
		return inputError(input, ch, ch); // other error
	}
}

void printTests(ofstream& ofs) {
    ofs << "    Initial Jumps   = " << tests << endl;
    ofs << "    Initial catches =  " << catches << endl;
    ofs << endl;

    int total = 0;
    total += WStests;
    ofs << "    WS  tokens = " << WStok << " tests = " << WStests << endl;
    total += SYMtests;
    ofs << "    SYM tokens =  " << SYMtok << " tests = " << SYMtests << endl;
    total += KWtests;
    ofs << "    KW  tokens =  " << KWtok << " tests = " << KWtests << endl;
    total += IDtests;
    ofs << "    ID  tokens =  " << IDtok << " tests =  " << IDtests << endl;
    total += NUMtests;
    ofs << "    NUM tokens =  " << NUMtok << " tests =  " << NUMtests << endl;
    ofs << "    Unk tokens =  " << UNKtok << endl;
    ofs << "    --------------------------" << endl;
    ofs << "    total toks = " << tokens << " tests = " << total << endl;
}
