// inputError.cpp
//
// by Allyn Shell
// 1/2018
// This routine supports the scanner

#include "getToken.h"
#include "ASCII.h"


Token* inputError(char* input, char*& ch, char* startCh)  {
	//  report something ... TBD
	return new Token(startCh, ch, UNKNOWN);
}
