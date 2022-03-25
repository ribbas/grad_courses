/* SS-Driver.cpp
 * Allyn Shell
 *
 * July 2019
 * Modified by
 * Sabbir Ahmed
 * March 2022
 */

#include "SS_Cell.h"
#include "Scanner.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

std::unique_ptr<llvm::LLVMContext> irContext;
std::unique_ptr<llvm::IRBuilder<>> irBuilder;

std::unique_ptr<llvm::Module> module;
std::unique_ptr<llvm::orc::KaleidoscopeJIT> JIT;
std::map<std::string, llvm::Value*> namedValues;

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
        if (cmd == QUIT) {
            break;
        }
    }

    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();
    initJIT();

    // generate IR for all the valid expression cells
    symTab.generateIR();
    symTab.printTable(ofs);

    // print cell attributes to stdout and to file
    symTab.printAllCells(cout);
    symTab.printAllCells(ofs);

    // invoke destructors for global LLVM objects
    llvm::llvm_shutdown();

    ofs.close();

    return 0;
}
