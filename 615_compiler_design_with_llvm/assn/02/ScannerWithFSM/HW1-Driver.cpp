// HW1-Driver.cpp
//
// by Allyn Shell
// 1/2018
// This routine tests the scanner

#include "Token.h"
#include "getToken.h"
#include <iostream>
#include <fstream>
using namespace std;


int main() {
	// open output tile
	ofstream ofs;
	ofs.open("HW1-Output.txt");
	if (! ofs) {
		cout << "Failed to open: HW1-Output.txt" << endl << flush;
		return 1;
	}
	ofs << "Start of HW1" << endl << endl << flush;

	// open input file
	ifstream ifs;
	ifs.open("HW1-Input.txt");
	if (! ifs) {
		cout << "Failed to open: HW1-Input.txt" << endl;
		ofs << "Failed to open: HW1-Input.txt" << endl;
		ofs << "Execution Stopped." << endl << flush;
		ofs.close();
		return 1;
	}

	// new input line
	// read then close input
	const int size = 48;
	char* input = new char[size];
	ifs.read(input,size);
	ifs.close();
	input[size-1] = 0;
//	input = (char*)"if (ed = 10) then return; else ED = ed+1; end;\n";
	ofs << "Input:" << endl;
	ofs << input << endl;

	// scan input line and write output
	ofs << "Output:" << endl << flush;
	char* ch = input;
	while (true) {
		Token* token = getToken(input, ch, ch);
		token->display(ofs);
		char* st = token->start;
		delete token;
		if ( ! *st) break;
	}
	ofs << endl;
	ofs << "Tests:" << endl << flush;
    printTests(ofs);
	ofs << endl;
	ofs << "End of HW1" << endl << flush;

	// delete input line
	delete[](input);
	return 0;
}


