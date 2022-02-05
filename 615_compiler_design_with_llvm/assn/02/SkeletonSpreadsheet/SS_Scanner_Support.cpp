// Scanner.cpp
// Allyn Shell
// Feb 2018

#include "Token.h"
#include "SS_Cell.h"
#include "Scanner.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;



// main input processing routine for file input
void readInputFile(ifstream& ifs, TableOfCells& symTab) {
	int size = 256;
	char* input = new char[size];
	while (ifs) {
		ifs.getline(input, size, '\n');
		cout << input << endl << flush;
		scanLine(input, symTab);
	}
	delete[] input;
	return;
}

command readCommandLine(TableOfCells& symTab) {
	int size = 256;
	char* input = new char[size];

	cout << "Enter> " << flush;
	cin.getline(input, size, '\n');
	if (input[0] == 'q') {
		delete[] input;
		return QUIT;
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

// print explaination of how to call Spreadsheet.exe
void printUsage(const string name) {
	const char tab = '\t';
	cout << endl;
	cout << "usage:" << endl;
	cout << "enter> " << name << " [filename]" << endl;
	cout << tab << "May have one argument (optional)." << endl;
	cout << tab << "If no argument is provided," << endl;
	cout << tab << "the input will be taken from" << endl;
	cout << tab << "the command line." << endl;
	cout << endl << flush;
	cout << "Type " << '"' << "quit" << '"' << " to exit the program." << endl;
	cout << "Type " << '"' << '?' << '"' << " for entry options." << endl;
	cout << endl << flush;
}

// print explaination of how to use Spreadsheet.exe
void printEntryOptions() {
	const char tab = '\t';
	cout << endl;
	cout << "This spreadsheet can take the following kinds of lines:" << endl;
	cout << "enter> quit" << endl;
	cout << tab << "This will exit the program." << endl;
	cout << "enter> ?" << endl;
	cout << tab << "This will print this set of entry options." << endl;
	cout << "enter> # ..." << endl;
	cout << tab << "Any line beginning with a " << '"' << '#' << '"' << " will be ignored" << endl;
	cout << tab << "as a comment line." << endl;
	cout << "enter> A1 " << '"' << "Text" << '"' << endl;
	cout << tab << "Any line begining with an ID and a double quote mark will be considered" << endl;
	cout << tab << "a text line. Text in a text line should not exceed 6 characters." << endl;
	cout << tab << "Only the first 6 characters will be displayed." << endl;
	cout << "enter> A2 2345" << endl;
	cout << tab << "Any line beginning with an ID and a numeric digit or a minus sign (" << '"' << '-' << '"' << ')' << endl;
	cout << tab << "will be considered an integer input for the designated cell." << endl;
	cout << tab << "Negative integers must not contain white space after the minus sign." << endl;
	cout << tab << "Integers with more than 6 digits will display as ******" << endl;
	cout << "enter> B3 = B2 + A1" << endl;
	cout << tab << "Any line begining with an ID and an equal sign (" << '"' << "=" << '"' << ")" << endl;
	cout << tab << "will be considered an equation line." << endl;
	cout << tab << "For HW2 the equation line must have an ID, a binary operator and an ID." << endl;
	cout << endl << flush;
}
