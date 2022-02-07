// getToken.cpp
//
// by Allyn Shell
// 1/2018
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
        if (ASCII[*ch] == 2) {
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
        }
        return getID(input, ch, startCh);

        // while (++SYMtests && ASCII[*ch] == 2) {

        //     int index = SYM_Index[*ch];
        //     int state = SYM_State[1][index];
        //     ++ch;
        //     std::cout << ch << '\n';
        //     std::cout << " | ix " << index << " st " << state << '\n';
        //     while (++SYMtests && ASCII[*ch] == 2 && state && index) {
        //         accept = SYM_Accept[state];
        //         ++ch;
        //         index = SYM_Index[*ch];
        //         state = SYM_State[state][index];
        //     }
        //     if (++SYMtests && accept) {
        //         return new Token(startCh, ch, SYM);
        //     }
        // }
        // std::cout << "done\n";
        // return new Token(startCh, ch, SYM);
    } catch (...) {
        ++catches;
        if (++SYMtests and accept)
            return new Token(startCh, ch, SYM);
        ch = startCh;
        return getID(input, ch, startCh);
    }
}
