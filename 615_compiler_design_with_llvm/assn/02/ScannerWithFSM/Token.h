// Token.h
//
// by Allyn Shell
// 1/2018
// This class supports the scanner

#ifndef TOKENS_H_
#define TOKENS_H_

#include <iostream>
using namespace std;


enum Kind { UNKNOWN, ELSE, END, IF, RETURN, THEN, WS, ID, NUM, SYM };

class Token {
public:

	Token(char* s, char* f, Kind k) : start(s), finish(f), kind(k) {}
	~Token() {}

	char* start;
	char* finish;
	Kind  kind;

	void display(ostream& os);
	//  more ... TBD
};

#endif // TOKENS_H_
