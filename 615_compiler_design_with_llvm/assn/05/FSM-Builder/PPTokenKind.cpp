// PPTokenKind.cpp
// by Allyn Shell
// May 2020

#include "PPTokenKind.h"
#include <iostream>
using namespace std;


ostream& operator << (ostream& os, PPTokenKind tk) {
    switch (tk) {
        case UNKNOWN : os << "UNKNOWN"; break;
        case DEFINE : os << "DEFINE"; break;
        case INCLUDE : os << "INCLUDE"; break;
        case UNDEF : os << "UNDEF"; break;
        case NAMELIST : os << "NAMELIST"; break;
        case IFNDEF : os << "IFNDEF"; break;
        case ENDIF : os << "ENDIF"; break;
        case QUOTE : os << "QUOTE"; break;
        case TEXT : os << "TEXT"; break;
        case STATIC : os << "STATIC"; break;
        case PRIVATE : os << "PRIVATE"; break;
        case PUBLIC : os << "PUBLIC"; break;
        case LFSCRPBRKT : os << "LFSCRPBRKT"; break;
        case RTSCRPBRKT : os << "RTSCRPBRKT"; break;
    }
    return os;
}
