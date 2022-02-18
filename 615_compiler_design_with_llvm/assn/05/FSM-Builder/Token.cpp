// Token.cpp
// by Allyn Shell
// May 2020

#include "Token.h"
#include <string>
using namespace std;


bool Token::setLexeme() {
    // returns 0 on success
    int len = getSize();
    if (len == 0) return 0;
    lexeme = string((char*)startCh, len);
    return 0;
}

bool Token::setValue() {
    // returns 0 on success
    setLexeme();
    value = stoi(lexeme);
    return 0;
}

ostream& operator << (ostream& os, Token& tok) {
    os << "{";
    os << tok.getKind();
    if (tok.getKind() == ID)  os << ", " << tok.getLexeme();
    if (tok.getKind() == TXT) os << ", \"" << tok.getLexeme() << "\"";
    if (tok.getKind() == NUM) os << ", " << tok.getValue();
    os << "}";
    return os;
}

