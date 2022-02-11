// TokenKind.cpp
// by Allyn Shell
// November 2020

#include "TokenKind.h"
#include <iostream>
using namespace std;

//    enum TokenKinds { UNK, END_FILE, CR, STARTCOM, EQUAL, DQUOTE, LFBRK, RTBRK, SEMI,
//        LFSCBKT, RTSCBKT, NMLST, DEFAULTS, TRUE, FALSE, ID, NUM, TXT, ERROR };

ostream& operator << (ostream& os, TokenKind tk) {
    switch (tk) {
        case UNK : os << "UNKNOWN"; break;
        case END_FILE : os << "EOF"; break;
        case CR : os << "CR"; break;
        case STARTCOM : os << "STARTCOM"; break;
        case EQUAL : os << "EQUAL"; break;
        case DQUOTE : os << "DQUOTE"; break;
        case LFBRK : os << "LFBRK"; break;
        case RTBRK : os << "RTBRK"; break;
        case SEMI : os << "SEMI"; break;
        case LFSCBKT : os << "LFSCBKT"; break;
        case RTSCBKT : os << "RTSCBKT"; break;
        case NMLST : os << "NAMELIST"; break;
        case DEFAULTS : os << "DEFAULTS"; break;
        case TRUE : os << "TRUE"; break;
        case FALSE : os << "FALSE"; break;
        case ID : os << "ID"; break;
        case NUM : os << "NUM"; break;
        case TXT : os << "TEXT"; break;
        case ERROR : os << "ERROR"; break;
    }
    return os;
}
