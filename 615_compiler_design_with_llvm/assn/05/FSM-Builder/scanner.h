// scanner.h
// by Allyn Shell
// October 2020

#ifndef SCANNER_H
#define SCANNER_H

#include "Token.h"
#include <fstream>
using namespace std;

// public scanner routines
void setScanner(ifstream& ifs);
Token getToken();

#endif // SCANNER_H
