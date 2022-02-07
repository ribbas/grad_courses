// getToken.cpp
//
// by Allyn Shell
// 1/2018
// Modified by:
// Sabbir Ahmed
// 2/2022
// These routines help scan the input stream

#include "ASCII.h"
#include "ASCII_SYM.h"
#include "getToken.h"

extern int SYMtests;
extern int catches;

// HW2 Symbol list:
// + – * / < <= == >= > = ( ) # ” // /* */
Token* getSymbol(char* input, char*& ch, char* startCh) {

    int accept = 0;

    try {

        int index = SYM_Index[*ch];
        int state = SYM_State[1][index];
        while (++SYMtests && ASCII[*ch] == 2 && state && index) {
            accept = SYM_Accept[state];
            ++ch;
            index = SYM_Index[*ch];
            state = SYM_State[state][index];
        }
        if (++SYMtests && accept) {
            return new Token(startCh, ch, SYM);
        }
        return getID(input, ch, startCh);

    } catch (...) {
        ++catches;
        if (++SYMtests && accept)
            return new Token(startCh, ch, SYM);
        ch = startCh;
        return getID(input, ch, startCh);
    }
}
