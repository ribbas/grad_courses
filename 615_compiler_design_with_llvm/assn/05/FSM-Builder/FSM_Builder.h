// FSM_Builder.h
// by Allyn Shell
// May 2020

// Example output for ScanGen

#ifndef FSM_BUILDER_H
#define FSM_BUILDER_H

#include "Token.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


// FSM-Builder creates the tables and FSM specified
// by the flags in ScanGen
class FSM_Builder {
    static char line[255];
    static Token* nextToken;
public:
    FSM_Builder() {}

    // to be called by main routine
    bool setScanGenFromInput(string scanGenInput); // returns 0 on success
    bool buildTables(); // returns 0 on success
    void printFSMtablesFile(ostream& os, string date, int n, string word[], string prefix);
    void printFSMcode(ostream& os, string date, string prefix,  bool csens,
                        bool lexCont, string cont, bool pnt);
private:
    char BuildIndex[128];
    int IndexCount;
    char BuildIndexChar[64];
    char BuildState[256][64];
    int StateCount;
    stringstream StateComment[256];
    char BuildAccept[256];
    int AcceptWord[64];

    // called by buildTables()
    bool buildIndex();  // returns 0 on success
    bool buildState();  // returns 0 on success
    bool buildAccept(); // returns 0 on success

    // called by printHeaderFile(...)
    void printFSMfileHeader(ostream& os, string date, int n, string word[], string prefix);
    void printIndex(ostream& os, string prefix);
    void printState(ostream& os, string prefix);
    void printAccept(ostream& os, string prefix);
    void printFSMfileFooter(ostream& os, string prefix);
};

#endif // FSM_BUILDER_H
