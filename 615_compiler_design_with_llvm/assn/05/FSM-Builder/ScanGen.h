// ScanGen.h
// by Allyn Shell
// May 2020

// Example output for ScanGen

#ifndef SCANGEN_H
#define SCANGEN_H

#include <string>
using namespace std;

// ScanGen used as global NAMELIST input target and
// provides the control flags used to create a FSM.
struct ScanGen {
    static ScanGen& getInstance();

    string date = "";
    
    bool caseSensitive = true;
    string prefix = "XXX";

    int numWords = 0;
    int firstWordOffset = 0;
    string word[64] = { "" };

    bool createTokenPointers = true;
    bool lexemeContinues = false;
    string continuationPrefix = "";

    string nextInputFilename = "";

private:
    ScanGen() {}
    static ScanGen* ScanGen_singleton;
    static void setDefaults();
    static void initMap();
};

#endif // SCANGEN_H
