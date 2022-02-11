// scanner.cpp
// Allyn Shell
// November 2020

#include "ASCII.h"
#include "ASCII_KW.h"
#include "scanner.h"
#include "Token.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
// #define and &&

ifstream* ifsp = 0;
static int fileStatus = 0;
// fileStatus = 0 == no file;
// fileStatus = 1 == file open needs line read
// fileStatus = 2 == line read ready for scan and file good
// fileStatus = 3 == line read ready for scan and file bad
// fileStatus = 4 == end of file
static char line[128] = { 0 };
static int lineSize = 128;
static char* nextPnt;

// initialize the scanner for a new file
void setScanner(ifstream& ifs) {
cout << "  in setScanner(ifstream& ifs)" << endl;
    fileStatus = 4;
    if (ifs) {
        ifsp = &ifs;
        fileStatus = 1;
    }
}

// forward declarations
Token getToken(char* start, char*& curr);
void getLine();

// scanner starting point
// getToken() controls the acquisition of lines with getLine()
// and calls the getToken(start,curr) to scan for tokens.
Token getToken() {
//cout << "  in getToken()" << endl;
    Token token(END_FILE);
    while (true) {
//cout << "    switch to case " << fileStatus << " :" << endl;
        switch (fileStatus) {
          case 0 : // no file
            return Token(END_FILE);
          case 1 : // file open needs line read
            getLine();
            break;
          case 2 : // line read ready for scan and file good
          case 3 : // line read ready for scan and file bad
            while ( ! ASCtok[*nextPnt]) ++nextPnt; // discard whitespace
            token = getToken(nextPnt,nextPnt);
            if (token.getKind() == CR) fileStatus = 1; // needs line read
            if (token.getKind() == END_FILE) fileStatus = 4;
            return token;
          case 4 : // end of file
          default : // unknown
            return Token(END_FILE);
        }
    }
}

// getLine retrieves the input to be scanned up to a CR or END_FILE
void getLine() {
//cout << "  in getLine()" << endl;
    if ( ! *ifsp) {
        cout << "ERROR: Trying to getLine past end of file." << endl << flush;
        exit(1);
    }
    int size = 0;
    bool file_conts = true;
    while ( ! size) {
        int before = ifsp->tellg();
//        cout << endl;
        ifsp->getline(line,lineSize);
//        cout << endl;
        cout << "  got line >>>" << line << "<<<" << endl;
//        cout << endl;
        nextPnt = line;
        if (*ifsp) fileStatus = 3;
        else fileStatus = 4;
        int after = ifsp->tellg();
        size = after - before -2;
//        cout << "size = " << size << endl;
    }
    if (size > 0) {
        char* pnt = line + size;
        *pnt = '\r'; // CR
        *(pnt+1) = 0;
        return;
    }
    if (size < 0) {
        for (int i=0; i<10; ++i) {
            if (!line[i]) {
//                cout << "line[" << i << "] = null" << endl;
                line[i] = (char)4; // END_FILE
                line[i+1] = 0;
                break;
            }
        }
    }
}

// forward declarations for use by getToken(start,curr)
Token inputError(char* start, char*& curr);
Token getSymbol(char* start, char*& curr);
Token getNumber(char* start, char*& curr);
Token getID(char* start, char*& curr);
Token getNAMELIST(char* start, char*& curr);
Token getKeyword(char* start, char*& curr);

// Input scanner token list:
//    enum TokenKind { UNK, END_FILE, CR, STARTCOM, EQUAL, DQUOTE, LFBRK, RTBRK, SEMI,
//        LFSCBKT, RTSCBKT, NMLST, DEFAULTS, TRUE, FALSE, ID, NUM, TXT, ERROR };

Token getToken(char* start, char*& curr) {
//cout << "  in getToken(char* start, char*& curr)" << endl;
//cout << "     *start = " << *start << "  *curr = " << *curr << endl;
    typedef Token (*getTokenFunctionPointer)(char* start, char*& curr);
    const getTokenFunctionPointer jumpTable[] = {
        inputError,
        inputError,
        getSymbol,
        getNumber,
        getID,
        getID,
        getNAMELIST,
        getKeyword };
    try {
        // jump to designated getToken function
        return jumpTable[ASCtok[*curr]](start, curr);
    }
    catch ( ... ) {
//cout << "***************  in catch of jump table  *************" << endl;
        if ( ! curr ) return Token(END_FILE); // end of input
        return inputError(start, curr); // other error
    }    
    return Token(UNK);
}

int errorCount = 0;
// construct an ERROR token
Token inputError(char* start, char*& curr) {
    //cout << "  in inputError(char* start, char*& curr)" << endl;
    //cout << "    *curr = " << *curr << endl;
    //cout << "    (int)*curr = " << (int)*curr << endl;
    if (++errorCount > 3) exit(1);
    return Token(ERROR);
}

// construct a Symbol token from inputs
Token getSymbol(char* start, char*& curr) {
//cout << "  in getSymbol(char* start, char*& curr)" << endl;
    const char ASCsym[] = {
        0, 0, 0, 0, 1, 0, 0, 0, // END_FILE
        0, 0, 0, 0, 0, 2, 0, 0, // CR
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,

        0, 0, 5, 0, 0, 0, 0, 0, // "
        0, 0, 0, 0, 0, 0, 0, 2, // / (start of comment treated like CR)
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 2, 0, 4, 0, 0, // ; = (semicolon treated like CR)

        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 6, 0, 7, 0, 0, // [ ]

        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 9, 0,10, 0, 0  // { }
    };
    char sym = ASCsym[*(curr++)];
    if (sym == 5) { //  5 = '\"'
        char* startTxt = curr;
        while (*curr and ASCsym[*curr] != 5) { // 5 = '\"'
            if (*curr == 92) ++curr; // 92 = '\\'
            ++curr;
        }
        Token token(TXT, startTxt, curr);
        token.setLexeme();
        if (*curr and ASCsym[*curr] == 5) ++curr;
        return token;
    }
    return Token((TokenKind)sym);
}

// construct a NUM token from inputs
Token getNumber(char* start, char*& curr) {
    //cout << "  in getNumber(char* start, char*& curr)" << endl;
    ++curr;
    if (ASCtok[*curr] == 3) ++curr; // add numeric digits
    Token token(NUM, start, curr);
    token.setValue();
    return token;
}

// construct an ID token from inputs
Token getID(char* start, char*& curr) {
    //cout << "  in getID(char* start, char*& curr)" << endl;
    while (ASCII[*curr] > 3) ++curr; // add alphas
    Token token(ID, start, curr);
    token.setLexeme();
    return token;
}

// construct a NAMELIST token from inputs
Token getNAMELIST(char* start, char*& curr) {
//cout << "  in getNAMELIST(char* start, char*& curr)" << endl;
    string lexeme = string(curr, 8);
    if (lexeme == "NAMELIST") {
        curr += 8;
        return Token(NMLST);
    }
    return getID(start, curr);
}

// construct a Keyword token from inputs
Token getKeyword(char* start, char*& curr) {
//cout << endl << "  in getKeyword(char* start, char*& curr)" << endl;
    int accept = 0;
    try {
        int index = KW_Index[*curr];
        int state = KW_State[1][index];
        while (state and index) {
            accept = KW_Accept[state];
            ++curr;
            index = KW_Index[*curr]; // overflow exception possible
            state = KW_State[state][index];
        }
        if (ASCII[*curr] < 4 and accept) return Token((TokenKind)accept);
        --curr;
        return getID(start, curr);
    } catch ( ... ) {
        if (accept) return Token((TokenKind)accept);
        curr = start;
        return getID(start, curr);
    }
}
