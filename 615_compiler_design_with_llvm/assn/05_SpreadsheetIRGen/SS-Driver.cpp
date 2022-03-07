// SS-Driver.cpp
// Allyn Shell
// July 2019

#include "SS_Cell.h"
#include "Scanner.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

// open a new context and module
std::unique_ptr<llvm::LLVMContext> llvmContext =
    std::make_unique<llvm::LLVMContext>();

// create a new builder for the module
std::unique_ptr<llvm::IRBuilder<>> irBuilder =
    std::make_unique<llvm::IRBuilder<>>(*llvmContext);

std::string lol = "hehe";

int main(int argc, const char* argv[]) {
    cout << "Welcome to mySpreadsheet" << endl << endl;
    string pathName = argv[0];
    size_t pos = pathName.find_last_of("\\/");
    string exeName = pathName.erase(0, pos + 1);
    printUsage(exeName);

    ifstream ifs;
    if (argc == 2) {
        // open input file
        ifs.open(argv[1]);
        if (!ifs.is_open()) {
            cout << "ERROR: Input file " << argv[1] << " not found." << endl;
            return 1;
        }
    }

    // open output file
    ofstream ofs("HW-out.txt");
    if (!ofs.is_open()) {
        cout << "ERROR: Output file HW-out.txt could not be opened." << endl;
        if (ifs)
            ifs.close();
        return 1;
    }

    // open spreadsheet cell table
    TableOfCells symTab;

    // fill in Spreadsheet from input file
    if (ifs.is_open()) {
        cout << "*** " << argv[1] << " input ***" << endl;
        readInputFile(ifs, symTab);
        cout << "*** End of file input ***" << endl << endl;
        ifs.close();
    }

    // print output
    while (true) {
        symTab.printTable(cout);
        command cmd = readCommandLine(symTab);
        if (cmd == QUIT)
            break;
    }

    symTab.printTable(ofs);
    symTab.printAllCells(ofs);
    ofs.close();
    return 0;
}
