// SS_Scanner_Support.cpp
// Allyn Shell
// Feb 2018

#include "SS_Cell.h"
#include "Scanner.h"
#include "Token.h"
#include <fstream>
#include <iostream>
#include <string>

// main input processing routine for file input
void readInputFile(std::ifstream& ifs, TableOfCells& symTab) {
    int size = 256;
    char* input = new char[size];
    while (ifs) {
        ifs.getline(input, size, '\n');
        std::cout << input << std::endl << std::flush;
        scanLine(input, symTab);
    }
    delete[] input;
    return;
}

command readCommandLine(TableOfCells& symTab) {
    int size = 256;
    char* input = new char[size];

    std::cout << "Enter> " << std::flush;
    std::cin.getline(input, size, '\n');
    if (input[0] == 'q') {
        delete[] input;
        return QUIT;
    }
    if (input[0] == 'p') {
        symTab.printAllCells(std::cout);
        delete[] input;
        return CONTINUE;
    }
    if (input[0] == '?') {
        printEntryOptions();
        delete[] input;
        return CONTINUE;
    }
    scanLine(input, symTab);
    delete[] input;
    return CONTINUE;
}

void cellTests(TableOfCells& symTab) {
    SS_Cell* A0 = symTab.getCell("A0");
    A0->setTXTCell("  A0");

    SS_Cell* B0 = symTab.getCell("B0");
    B0->setTXTCell("Too Long");

    SS_Cell* B1 = symTab.getCell("B1");
    B1->setNUMCell(3456);

    SS_Cell* C1 = symTab.getCell("C1");
    C1->setNUMCell(34567890);

    SS_Cell* D1 = symTab.getCell("D1");
    D1->setNUMCell(3456, -1);

    SS_Cell* E1 = symTab.getCell("E1");
    E1->setNUMCell(-23456);

    SS_Cell* F1 = symTab.getCell("F1");
    F1->setNUMCell(-3456789);
    return;
}

std::ostream& operator<<(std::ostream& os, TokenKind kind) {
    switch (kind) {
        case T_EOF:
            os << "T_EOF";
            break;
        case T_ERROR:
            os << "T_ERROR";
            break;
        case ID:
            os << "ID";
            break;
        case NUM:
            os << "NUM";
            break;
        case ADD:
            os << "ADD";
            break;
        case SUB:
            os << "SUB";
            break;
        case MULT:
            os << "MULT";
            break;
        case DIV:
            os << "DIV";
            break;
        case LPAREN:
            os << "LPAREN";
            break;
        case RPAREN:
            os << "RPAREN";
            break;
    }
    return os;
}

void TableOfCells::printAllCells(std::ostream& os) {
    os << std::endl;
    os << "Cell Attributes:" << std::endl;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 6; ++j) {
            cell[i][j].printCellAttributes(os);
            os << std::endl;
        }
    return;
}

void TableOfCells::printIR(std::ostream& os) {
    os << std::endl;
    os << "IR generated from cells:" << std::endl;
    for (int i = 0; i < 10; ++i)
        for (int j = 0; j < 6; ++j) {
            if (cell[i][j].expNode) {
                for (int j = 0; j < 80; j++) {
                    os << "*";
                }
                os << std::endl;
                cell[i][j].printCellIR(os);
                for (int j = 0; j < 80; j++) {
                    os << "*";
                }
                os << std::endl;
            }
        }
    return;
}

// print explaination of how to call Spreadsheet.exe
void printUsage(const std::string name) {
    const char tab = '\t';
    std::cout << std::endl;
    std::cout << "usage:" << std::endl;
    std::cout << "enter> " << name << " [filename]" << std::endl;
    std::cout << tab << "May have one argument (optional)." << std::endl;
    std::cout << tab << "If no argument is provided," << std::endl;
    std::cout << tab << "the input will be taken from" << std::endl;
    std::cout << tab << "the command line." << std::endl;
    std::cout << std::endl << std::flush;
    std::cout << "Type " << '"' << "quit" << '"' << " to exit the program."
              << std::endl;
    std::cout << "Type " << '"' << '?' << '"' << " for entry options."
              << std::endl;
    std::cout << std::endl << std::flush;
}

// print explaination of how to use Spreadsheet.exe
void printEntryOptions() {
    const char tab = '\t';
    std::cout << std::endl;
    std::cout << "This spreadsheet can take the following kinds of lines:"
              << std::endl;
    std::cout << "enter> q or quit" << std::endl;
    std::cout << tab << "This will exit the program." << std::endl;
    std::cout << "enter> p or print" << std::endl;
    std::cout << tab << "This will print the attributes of all of the cells."
              << std::endl;
    std::cout << "enter> ?" << std::endl;
    std::cout << tab << "This will print this set of entry options."
              << std::endl;
    std::cout << "enter> # ..." << std::endl;
    std::cout << tab << "Any line beginning with a " << '"' << '#' << '"'
              << " will be ignored" << std::endl;
    std::cout << tab << "as a comment line." << std::endl;
    std::cout << "enter> A1 " << '"' << "Text" << '"' << std::endl;
    std::cout << tab
              << "Any line begining with an ID and a double quote mark will be "
                 "considered"
              << std::endl;
    std::cout
        << tab
        << "a text line. Text in a text line should not exceed 6 characters."
        << std::endl;
    std::cout << tab << "Only the first 6 characters will be displayed."
              << std::endl;
    std::cout << "enter> A2 2345" << std::endl;
    std::cout
        << tab
        << "Any line beginning with an ID and a numeric digit or a minus sign ("
        << '"' << '-' << '"' << ')' << std::endl;
    std::cout << tab
              << "will be considered an integer input for the designated cell."
              << std::endl;
    std::cout
        << tab
        << "Negative integers must not contain white space after the minus "
           "sign."
        << std::endl;
    std::cout << tab
              << "Integers with more than 7 digits will display as ******"
              << std::endl;
    std::cout << "enter> B3 = B2 + A1" << std::endl;
    std::cout << tab << "Any line begining with an ID and an equal sign ("
              << '"' << "=" << '"' << ")" << std::endl;
    std::cout << tab << "will be considered an equation line." << std::endl;
    std::cout
        << tab
        << "For HW2 the equation line must have an ID, a binary operator and "
           "an ID."
        << std::endl;
    std::cout << std::endl << std::flush;
}
