// FSM_Builder_main.cpp
// by Allyn Shell
// May 2020

// Example output for ScanGen

#include "FSM_Builder.h"
#include "scanner.h"
#include "ScanGen.h"
#include <iostream>
#include <sstream>
#include <fstream>
using namespace std;

// this is the driver for the Builder application which uses
// NAMELIST input into the ScanGen struct (a global input)
// to build Finite State Machines (FSMs).
int main(int argc, char** argv) {
    ScanGen& scanGen = ScanGen::getInstance();
    FSM_Builder Builder;

    // Verify Input
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <first_scanGen_input_filename>" << endl;
        return 1;
    }

    // set first input filename
    string scanGenInput = argv[1];

    // loop on multiple input files
    // (to produce multiple FSMs)
    while (scanGenInput != "") {
        cout << "for " << scanGenInput << " input file:" << endl;
        bool failure = Builder.setScanGenFromInput(scanGenInput);
        if (failure) return 1;

        failure = Builder.buildTables();
        if (failure) return 1;
    
        ofstream ofs;
        string filename = scanGen.prefix + "_FSM.h";
        ofs.open(filename);
        cout << "Generating the " << filename << " header file." << endl;
        Builder.printFSMtablesFile(ofs, scanGen.date, scanGen.numWords,
                        scanGen.word, scanGen.prefix);
        ofs.close();

        filename = scanGen.prefix + "_FSM.cpp";
        ofs.open(filename);
        cout << "Generating the " << filename << " code file." << endl;
        Builder.printFSMcode(ofs, scanGen.date, scanGen.prefix,  scanGen.caseSensitive,
                             scanGen.lexemeContinues, scanGen.continuationPrefix,
                             scanGen.createTokenPointers);
        ofs.close();

        // set next input filename
        scanGenInput = scanGen.nextInputFilename;
    }
    return 0;
}

