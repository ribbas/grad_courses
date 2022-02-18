// ScanGen.cpp
// by Allyn Shell
// May 2020

// Example output for ScanGen

#include "ScanGen.h"
#include "NAMELIST_Support.h"
#include <ctime>
#include <iostream>
using namespace std;

// This is the only instance of the ScanGen struct
ScanGen* ScanGen::ScanGen_singleton = 0;

// provide a address reference to the only instance of the ScanGen struct
// if not yet initialized, initialize the ScanGen struct
ScanGen& ScanGen::getInstance() {
//cout << "    in ScanGen::getInstance()" << endl;
    if (ScanGen_singleton == 0) {
        ScanGen_singleton = new ScanGen();

        time_t now = time(0);
        ScanGen_singleton->date = ctime(&now);

        initNLdefaultJumpTable ("ScanGen", ScanGen::setDefaults);
        initMap();
    }
    return *ScanGen_singleton;
}

// reset the defaults for the ScanGen struct
void ScanGen::setDefaults() {
//cout << "      in ScanGen::setDefaults()" << endl;

    time_t now = time(0);
    ScanGen_singleton->date = ctime(&now);

    cout << "    resetting ScanGen defaults." << endl << flush;
    ScanGen_singleton->caseSensitive = true;
    ScanGen_singleton->prefix = "XXX";

    ScanGen_singleton->numWords = 0;
    ScanGen_singleton->firstWordOffset = 0;
    for (int i=0; i<64; ++i) ScanGen_singleton->word[i] = "";

    ScanGen_singleton->createTokenPointers = true;
    ScanGen_singleton->lexemeContinues = false;
    ScanGen_singleton->continuationPrefix = "";

    ScanGen_singleton->nextInputFilename = "";
}

// initialize the map of name-value types for the ScanGen struct
void ScanGen::initMap() {
//cout << "     in ScanGen::initMap()" << endl;

    initNLstructPairMap ("ScanGen", "caseSensitive", BOOL, 
                     (void*)(&(ScanGen_singleton->caseSensitive)) );
    initNLstructPairMap ("ScanGen", "prefix", STRING,
                     (void*)(&(ScanGen_singleton->prefix)) );

    initNLstructPairMap ("ScanGen", "numWords", INT,
                     (void*)(&(ScanGen_singleton->numWords)) );
    initNLstructPairMap ("ScanGen", "firstWordOffset", INT,
                     (void*)(&(ScanGen_singleton->firstWordOffset)) );
    initNLstructPairMap ("ScanGen", "word", STRING,
                     (void*)(&(ScanGen_singleton->word)), 64);

    initNLstructPairMap ("ScanGen", "createTokenPointers", BOOL,
                     (void*)(&(ScanGen_singleton->createTokenPointers)) );
    initNLstructPairMap ("ScanGen", "lexemeContinues", BOOL,
                     (void*)(&(ScanGen_singleton->lexemeContinues)) );
    initNLstructPairMap ("ScanGen", "continuationPrefix", STRING,
                     (void*)(&(ScanGen_singleton->continuationPrefix)) );

    initNLstructPairMap ("ScanGen", "nextInputFilename", STRING,
                     (void*)(&(ScanGen_singleton->nextInputFilename)) );
}
