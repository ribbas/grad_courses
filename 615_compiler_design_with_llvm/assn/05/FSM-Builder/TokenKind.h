// TokenKind.h
// by Allyn Shell
// November 2020

#ifndef TOKENKIND_H
#define TOKENKIND_H

#include <iostream>
using namespace std;

// Input scanner token list:
enum TokenKind {
    UNK,
    END_FILE, CR, STARTCOM, 
    EQUAL, DQUOTE, LFBRK, RTBRK, SEMI, 
    LFSCBKT, RTSCBKT, NMLST, DEFAULTS, 
    TRUE, FALSE, ID, NUM, TXT, ERROR
};

ostream& operator << (ostream& os, TokenKind tk);

#endif // TOKENKIND_H

