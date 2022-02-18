// PPTokenKind.h
// by Allyn Shell
// May 2020

#ifndef PPTOKENKIND_H
#define PPTOKENKIND_H

#include <iostream>
using namespace std;


enum PPTokenKind { 
    UNKNOWN, NAMELIST, INCLUDE, DEFINE, UNDEF, 
    IFNDEF, ENDIF, QUOTE, TEXT,
    STATIC, PRIVATE, PUBLIC,
    LFSCRPBRKT, RTSCRPBRKT
};

ostream& operator << (ostream& os, PPTokenKind tk);

#endif // PPTOKENKIND_H
