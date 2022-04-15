// Token.cpp
//
// by Allyn Shell
// 1/2018
// This routine helps test the scanner

#include "Token.h"

extern int tokens;
extern int UNKtok;
extern int WStok;
extern int SYMtok;
extern int NUMtok;
extern int KWtok;
extern int IDtok;

// display outputs the token member values in a
// format similar to: ("ed", ID),
void Token::display(ostream& os) {
    ++tokens;
    os << '(' << '"';
    char* st = start;
    char* fn = finish;
    for (char* c = st; c < fn; ++c) {
        if (*c == '\n' || *c == '\r') {
            os << "\\n";
        } else {
            os.put(*c);
        }
    }
    os << '"' << ", ";
    switch (kind) {
        case UNKNOWN:
            os << "UNKNOWN";
            ++UNKtok;
            break;
        case ELSE:   // os << "ELSE"; break;
        case END:    // os << "END"; break;
        case IF:     // os << "IF"; break;
        case RETURN: // os << "RETURN"; break;
        case THEN:   // os << "THEN"; break;
            os << "KW";
            ++KWtok;
            break;
        case WS:
            os << "WS";
            ++WStok;
            break;
        case ID:
            os << "ID";
            ++IDtok;
            break;
        case NUM:
            os << "NUM";
            ++NUMtok;
            break;
        case SYM:
            os << "SYM";
            ++SYMtok;
            break;
    }
    os << "), ";

    // only print 5 tokens per line
    static int count = 0;
    if (++count == 5) {
        os << endl << flush;
        count = 0;
    }
}
