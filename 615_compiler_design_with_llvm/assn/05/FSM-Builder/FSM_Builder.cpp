// FSM_Builder.cpp
// by Allyn Shell
// May 2020

// Example output for ScanGen

#include "FSM_Builder.h"
#include "ScanGen.h"
#include "scanner.h"
#include "ParseAndAct.h"
#include "PPTokenKind.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;
// #define and &&

char FSM_Builder::line[255] = { 0 };
//int FSM_Builder::lineNumber = 0;
//int FSM_Builder::len = 0;
//char* FSM_Builder::pos = 0;
Token* FSM_Builder::nextToken = 0;


bool FSM_Builder::setScanGenFromInput(string scanGenInput) {
cout << " in setScanGenFromInput(\"" << scanGenInput << "\")" << endl;
    ifstream ifs;
    ifs.open(scanGenInput);
    if ( ! ifs) {
        cout << "ERROR: could not open " << scanGenInput << " for input." << endl;
    }
    setScanner(ifs);
    
    while (ifs.eof() == 0) {
        bool failed = ParseInputsAndAct();
        if (failed) {
            ifs.close();
            return 1;
        }
    }

    ifs.close();
    return 0;
}

// The buildTables routine uses the following three routines:
// buildIndex, buildFSM and buildAccept to create the tables
// for a Finite State Machine to identify specified keywords.
bool FSM_Builder::buildTables() {
//cout << " in buildTables()" << endl;
    bool failed = buildIndex();
    if (failed) {
        cout << "ERROR - BuildTables failed to buildIndex." << endl;
        return 1;
    }

    failed = buildState();
    if (failed) {
        cout << "ERROR - BuildTables failed to buildFSM." << endl;
        return 1;
    }

    failed = buildAccept();
    if (failed) {
        cout << "ERROR - BuildTables failed to buildAccept." << endl;
        return 1;
    }
    return 0;
}

// build Index table
bool FSM_Builder::buildIndex() {
//cout << "  in buildIndex()" << endl;
    ScanGen& scanGen = ScanGen::getInstance();
    for (int i=0; i<128; ++i) BuildIndex[i] = 0;
    
    // mark the characters used
    for (int i=0; i<scanGen.numWords; ++i) {
        int len = scanGen.word[i].length();
        for (int j=0; j<len; ++j) {
            char ch = scanGen.word[i][j];
            BuildIndex[ch] = 1;
        }            
    }
    if ( ! scanGen.caseSensitive) {
        for (char ch='A'; ch<='Z'; ++ch) {
            BuildIndex[ch+0x20] |= BuildIndex[ch];
            BuildIndex[ch] = BuildIndex[ch+0x20];
        }
        // at this point all upper and lower case
        // alphabetic characters have the same mark
    }
    
    IndexCount = 0;
    if (scanGen.caseSensitive) {
        for (char ch=0; ch<127; ++ch) {
            if (BuildIndex[ch]) {
                BuildIndexChar[IndexCount] = ch;
                ++IndexCount;
                BuildIndex[ch] = IndexCount;
//cout << "    debug  BuildIndex[" << ch << "] = " << IndexCount << endl;
            }
        }
    } else {
        for (char ch=0; ch<'a'; ++ch) {
            if (BuildIndex[ch]) {
                BuildIndexChar[IndexCount] = ch;
                ++IndexCount;
                BuildIndex[ch] = IndexCount;
            }
        }
        for (char ch='a'; ch<='z'; ++ch) {
            BuildIndex[ch] = BuildIndex[ch-0x20];
        }
        for (char ch='{'; ch<127; ++ch) {
            if (BuildIndex[ch]) {
                BuildIndexChar[IndexCount] = ch;
                ++IndexCount;
                BuildIndex[ch] = IndexCount;
            }
        }
    }
    if (IndexCount > 63) {
        cout << "Error: Number of different ASCII characters used in " << endl;
        cout << "       keywords exceeds 64. Which is my current limit!" << endl;
        cout << "       Sorry!" << endl;
        return 1;
    }
    return 0;
}

// build State table
bool FSM_Builder::buildState() {
//cout << "  in buildState()" << endl;
    ScanGen& scanGen = ScanGen::getInstance();
    StateCount = 2;
    
    for (int i=0; i<scanGen.numWords; ++i) {
        int len = scanGen.word[i].length();
        StateCount += len;
    }

    for (int i=0; i<StateCount; ++i) {
        StateComment[i] = stringstream();
        StateComment[i] << " // ";
        if (i< 10) StateComment[i] << " ";
        StateComment[i] << i;
        StateComment[i] << " state";
        for (int j=0; j<=IndexCount; ++j) {
            BuildState[i][j] = 0;
        }
    }

    int nextState = 2;
    for (int i=0; i<scanGen.numWords; ++i) {
        int len = scanGen.word[i].length();
        int currState = 1;
        for (int j=0; j<=len; ++j) {
            char ch = scanGen.word[i][j];
            int index = BuildIndex[ch];
            string sub = scanGen.word[i].substr(0,j+1);
            
            if (BuildState[currState][index]) {
                if (j < len) {
                    currState = BuildState[currState][index];
                    --StateCount;
                } else {
                    StateComment[currState] << " *";
                    AcceptWord[i] = currState;
                }
            } else {
                if (j < len) {
                    BuildState[currState][index] = nextState;
                    StateComment[currState] << " " << sub;
                    currState = nextState;
                    ++nextState;
                } else {
                    StateComment[currState] << " " << sub << " *";
                    AcceptWord[i] = currState;
                }
            }
        }
    }
    return 0;
}

// build Accept table 
bool FSM_Builder::buildAccept() {
//cout << "  in buildAccept()" << endl;
    ScanGen& scanGen = ScanGen::getInstance();

    for (int i=0; i<StateCount; ++i) {
        BuildAccept[i] = 0;
    }
    for (int i=0; i<scanGen.numWords; ++i) {
        BuildAccept[AcceptWord[i]] = i+scanGen.firstWordOffset;
    }
    return 0;
}

// The printFSMtablesFile routine uses following five routines: 
// printFSMfileHeader, printIndex, printState, printAccept and 
// printFSMfileFooter to create a header file or command line output
// containing the FSM tables for the specified keywords.
void FSM_Builder::printFSMtablesFile(ostream& os, string date, int n, 
                                  string word[], string prefix) {
//cout << "  in printFSMtablesFile(...)" << endl;
    bool errorSet = false;
    if (prefix == "") {
        errorSet = true;
        cout << "ERROR in input parameters. ScanGen.prefix is not specified." << endl;
        os   << "ERROR in input parameters. ScanGen.prefix is not specified." << endl;
    }
    if (n < 1) {
        errorSet = true;
        cout << "ERROR in input parameters. ScanGen.numWords is zero or negative." << endl;
        os   << "ERROR in input parameters. ScanGen.numWords is zero or negative." << endl;
    } else {
        bool firstTime = true;
        for (int i=0; i<n; ++i) {
            if (word[i] == "") {
                errorSet = true;
                if (firstTime) {
                    cout << "ERROR in input parameters. ScanGen.numWords = " << n << ", but" << endl;
                    os   << "ERROR in input parameters. ScanGen.numWords = " << n << ", but" << endl;
                    firstTime = false;
                }
                cout << "     ScanGen.word[" << i << "] is not set" << endl;
                os   << "     ScanGen.word[" << i << "] is not set" << endl;
            }
        }
    }
    if (errorSet) return;

    printFSMfileHeader(os, date, n, word, prefix);
    printIndex(os, prefix);
    printState(os, prefix);
    printAccept(os, prefix);
    printFSMfileFooter(os, prefix);
}

void FSM_Builder::printFSMfileHeader(ostream& os, string date, int n, 
                                     string word[], string prefix) {
//cout << "  in printFSMfileHeader(...)" << endl;
    os << "// " << prefix << "_FSM.h" << endl;
    os << "// Template by Allyn Shell" << endl;
    os << "// Template created May 2020" << endl;
    os << "// This file was Generated" << endl;
    os << "// " << date << endl;
    os << endl;
    os << "#ifndef " << prefix << "_FSM_H" << endl;
    os << "#define " << prefix << "_FSM_H" << endl;
    os << endl;
    os << "#include \"Token.h\"" << endl;
    os << "#include <iostream>" << endl;
    os << "using namespace std;" << endl;
    os << endl;
    os << endl;
    os << "// This FSM will match the following keywords:";
    for (int i=0; i<n; ++i) {
        if (i%5 == 0) os << endl << "// ";
        os << word[i] << " ";
    }
    os << endl;

    os << "Token* get_" << prefix << "(char* startCh, char*& currCh);" << endl;
    os << endl;
}

void FSM_Builder::printIndex(ostream& os, string prefix) {
//cout << "  in printIndex(...)" << endl;
//cout << "    debug  IndexCount = " << IndexCount << endl;
//cout << "    debug  BuildIndexChar = ";
//for (int i=0; i<IndexCount; ++i) {
//    cout << BuildIndexChar[i] << " ";
//}
//cout << endl;

    os << "// The " << prefix << "_Index table maps the input characters into" << endl;
    os << "// the transitions of " << prefix << "_FSM to the next state." << endl;
    os << "const char " << prefix << "_Index[128] = {" << endl;
    for (int k=0; k<4; ++k) {
        for (int j=0; j<4; ++j) {
            os << "   ";
            bool indexedChar = false;
            for (int i=0; i<8; ++i) {
                int val = BuildIndex[i+8*j+32*k];
                if (val > 0) indexedChar = true;
                if (val < 10) os << " ";
                os << val;
                if (i+8*j+32*k < 127) os << ",";
            }
            if (indexedChar) {
                os << " // ";
                for (int i=0; i<8; ++i) {
                    char ch = i+8*j+32*k;
                    if (BuildIndex[ch]) os << ch << " ";
                }
            }
            os << endl;
        }
        os << endl;
    }
    os << "};" << endl;
    os << endl;
}

void FSM_Builder::printState(ostream& os, string prefix) {
//cout << "  in printState(...)" << endl;
//cout << "    debug  StateCount = " << StateCount << endl;
//cout << "    debug  IndexCount = " << IndexCount << endl;

    os << "// The " << prefix << "_State table maps the next FSM state." << endl;
    os << "// The first index is the current state." << endl;
    os << "// The second index is the index from the" << endl;
    os << "// " << prefix << "_Index table." << endl;
    os << "const char " << prefix << "_State[" << StateCount << "][" 
        << (IndexCount+1) << "] = { // indexed by [state][index]" << endl;
    os << "    // ";
    for (int j=0; j<IndexCount; ++j) {
        os << "  " << BuildIndexChar[j];
    }
    os << endl;
    for (int i=0; i<StateCount; ++i) {
        os << "    {";
        for (int j=0; j<=IndexCount; ++j) {
            if (BuildState[i][j] < 10) os << " ";
            os << (int)BuildState[i][j];
            if (j < IndexCount) os << ",";
        }
        os << " }";
        if (i < StateCount-1) os << ",";
        else os << " ";
        os << StateComment[i].str() << endl;
    }
    os << "};" << endl;
    os << endl;
}

void FSM_Builder::printAccept(ostream& os, string prefix) {
//cout << "  in printAccept(...)" << endl;
    os << "// The " << prefix << "_Accept table identifies which states are" << endl;
    os << "// accepting states and the keyword they produce." << endl;
    os << "const int " << prefix << "_Accept[] = {" << endl;
    for (int i=0; i<StateCount; ++i) {
        os << "    " << (int)BuildAccept[i];
        if (i < StateCount-1) os << ", // ";
        else os << "  // ";
        if (i < 10) os << " ";
        os << i;
        if (BuildAccept[i]) os << " " << (PPTokenKind)BuildAccept[i];
        os << endl;
    }
    os << "};" << endl;
    os << endl;
}

void FSM_Builder::printFSMfileFooter(ostream& os, string prefix) {
//cout << "  in printFSMfileFooter(...)" << endl;
    os << "#endif // " << prefix << "_FSM_H" << endl;
    os << endl;
}

void FSM_Builder::printFSMcode(ostream& os, string date, string prefix, bool csens,
                               bool lexCont, string cont, bool pnt) {
//cout << "  in printFSMcode(...)" << endl;
    bool errorSet = false;
    if (prefix == "") {
        errorSet = true;
        cout << "ERROR in input parameters. ScanGen.prefix is not specified." << endl;
        os   << "ERROR in input parameters. ScanGen.prefix is not specified." << endl;
        os   << endl;
    }
    if (lexCont and cont == "") {
        errorSet = true;
        cout << "ERROR in input parameters. ScanGen.lexemeContinues is \"true\"," << endl;
        os   << "ERROR in input parameters. ScanGen.lexemeContinues is \"true\"," << endl;
        cout << "      but ScanGen.continuationPrefix name is not specified." << endl;
        os   << "      but ScanGen.continuationPrefix name is not specified." << endl;
        os   << endl;
    }
    if (errorSet) return;

    os << "// " << prefix << "_FSM.cpp" << endl;
    os << "// Template by Allyn Shell" << endl;
    os << "// Template created May 2020" << endl;
    os << "// Updated November 2020" << endl;
    if (prefix == "XXX") {
        cout << "WARNING Input parameter ScanGen.prefix is set to default \"XXX\"." << endl;
        os << endl;
        os << "//      ******************************************************************" << endl;
        os << "//      * WARNING Input parameter ScanGen.prefix is set to default \"XXX\" *" << endl;
        os << "//      ******************************************************************" << endl;
        os << endl;
    }
    os << "// This file was Generated" << endl;
    os << "// " << date << endl;
    os << endl;
    os << "#include \"" << prefix << "_FSM.h\"" << endl;
    if (lexCont)
        os << "#include \"" << cont << "_FSM.h\"" << endl;
    os << "#include \"ASCII.h\"" << endl;
    os << "#include \"TokenKind.h\"" << endl;
    os << endl;
    os << endl;
    os << "// The FSM in this routine will match the specified" << endl;
    os << "// keywords";
    if (lexCont) os << " or it will switch to the get_" << cont << " FSM";
    os << "." << endl;
    os << "Token";
    if (pnt) os << "*";
    os << " get_" << prefix << "(char* start, char*& curr) {" << endl;
    os << "    int accept = 0;" << endl;
    os << "    try {" << endl;
    os << "        int index = " << prefix << "_Index[*curr];" << endl;
    os << "        int state = " << prefix << "_State[1][index];" << endl;
    os << "        while (state and index) {" << endl;
    os << "            accept = " << prefix << "_Accept[state];" << endl;
    os << "            ++curr;" << endl;
    os << "            index = " << prefix << "_Index[*curr]; // overflow exception possible" << endl;
    os << "            state = " << prefix << "_State[state][index];" << endl;
    os << "        }" << endl;
    os << "        if (ASCII[*curr] < 4 and accept) return ";
    if (pnt) os << "new ";
    os << "Token((TokenKind)accept);" << endl;
    os << "        --curr;" << endl;
    if (lexCont)
        os << "        return get_" << cont << "(start, curr);" << endl;
    else {
        os << "        return ";
        if (pnt) os << "new ";
        os << "Token(UNKNOWN);" << endl;
    }
    os << "    } catch ( ... ) {" << endl;
    os << "        if (accept) return ";
    if (pnt) os << "new ";
    os << "Token((TokenKind)accept);" << endl;
    if (lexCont) {
        os << "        curr = start;" << endl;
        os << "        return get_" << cont << "(start, curr);" << endl;
    } else {
        os << "        return ";
        if (pnt) os << "new ";
        os << "Token(UNKNOWN);" << endl;
    }
    os << "    }" << endl;
    os << "}" << endl;
}