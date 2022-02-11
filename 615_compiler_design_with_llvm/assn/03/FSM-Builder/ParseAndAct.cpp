// // ParseAndAct.cpp
// by Allyn Shell
// November 2020

#include "ParseAndAct.h"
#include "scanner.h"
#include "NAMELIST_Support.h"
#include "Token.h"
#include <iostream>
#include <string>
using namespace std;
// #define and &&
// #define or ||

// BNF for Builder input.
// Notes: Any error should be reported. If an error
// occures, the run should continue to the <END_FILE>.
// Scanner must recognize CR and END_FILE as tokens.
//
//enum TokenKinds { UNK, END_FILE, CR, STARTCOM, EQUAL, DQUOTE, LFGRK, RTBRK, SEMI,
//    LFSQBKT, RTSQBKT, NMLST, DEFAULTS, TRUE, FALSE, ID, NUM, TXT, ERROR };
//
//<ScanFile> => <ScannLine>* END_FILE
//
//<ScannLine> => <NamelistCommand>
//            | <inactiveLine>
//
//<inactiveLine> => <endLine>
//
//<endLine> => CR | END_FILE
//
//<NamelistCommand> => NAMELIST <StructName> <NamelistAction>
//
//<StructName> => ID   # must match name of Namelist Structure in application.
//
//<NamelistAction> => EQUAL DEFALUTS <endLine>   # reset defaults if DEFAULTS is specified.
//                 | LFBRK CR <NameValueList> RTBRK <endLine>
//
//<NameValueList> => <NameValueLine>*
//
//<NameValueLine> => <MemberName> EQUAL <Value> CR  # Set member to value specified if valid.
//                | CR
//
//<MemberName> => ID [ LFSQBKT NUM RTSQBKT ]   # ID must match name of member in <StructName> structure.
//                                             # Member will have a type and array size.
//                                             # If array size is greater than zero, subscript
//                                             # is required and NUM must be within array size.
//
//<Value> => <booleanValue>  # Type of value must match type of member.
//        | <integerValue>
//        | <stringValue>
//
//<booleanValue> => TRUE | FALSE
//
//<integerValue> => NUM
//
//<stringValue> => TEXT


bool parseError = false;
string currStruct = "NONE"; // name of NAMELIST struct being modified

// forward declarations
void NamelistCommand(Token& token);
void NameValueList(Token& token);
void NameValueLine(Token& token);

//<ScanFile> => <ScannLine>* END_FILE
//<ScannLine> => <NamelistCommand>
//            | <inactiveLine>
//<inactiveLine> => <endLine>
//<endLine> => CR | END_FILE
bool ParseInputsAndAct() {
//cout << "    in ParseAndAct()" << endl;
    parseError = false;

    Token token = getToken();
    while (token.getKind() != END_FILE) {
        if (token.getKind() != CR) NamelistCommand(token);
        token = getToken();
    }
//cout << token << endl;
    return parseError;
}

//<NamelistCommand> => NAMELIST <StructName> <NamelistAction>
//<StructName> => ID   # must match name of Namelist Structure in application.
//<NamelistAction> => EQUAL DEFALUTS <endLine>   # reset defaults if DEFAULTS is specified.
//                 | LFBRK CR <NameValueList> RTBRK <endLine>
void NamelistCommand(Token& token) {
//cout << "      in NamelistCommand( " << token << " )" << endl;
    if (token.getKind() != NMLST) {
        parseError = true;
        cout << "Parse ERROR: Expected NAMELIST token but encountered " << token << endl;
        while (true) {
            if (token.getKind() == CR) return; // scanned to end of line
            if (token.getKind() == END_FILE) return;
            if (token.getKind() == NMLST) break; // found start of NAMELIST command
            if (token.getKind() == LFBRK) { 
                getToken();
                if (token.getKind() == CR) {
                    // found possible start of group of name value lines
                    // set error flag and continue scan as if in name value lines
                    NameValueLine(token);
                    return;
                }
            }
            token = getToken();
        }
    }

    token = getToken();
    // check for struct name
    if (token.getKind() != ID) {
        parseError = true;
        cout << "Parse ERROR: Expected to find name of struct after NAMELIST token, but encountered " << token << endl;
        while (true) { // scan to end of line
            if (token.getKind() == CR) return;
            if (token.getKind() == END_FILE) return;
            token = getToken();
        }
    }
    // verify ID matches a struct name
    bool failed = verifyStruct(token.getLexeme());
    if (failed) {
        parseError = true;
        cout << "Parse ERROR: " << token << " does not match a struct name." << endl;
    } 
    currStruct = token.getLexeme();

    token = getToken();
    // check for desired action
    if (token.getKind() == EQUAL) { // found possible reset defaults action
//cout << token << " ";
        token = getToken();
        if (token.getKind() == DEFAULTS) {
//cout << token << endl;
            // call reset defaults routine for currStruct
            string NLstruct = currStruct;
            bool failed = setNLdefault (NLstruct);
            if (failed) {
                parseError = true;
                cout << "Parse ERROR: " << token << " struct cannot reset defaults." << endl;
                while (true) { // scan to end of line
                    token = getToken();
                    if (token.getKind() == CR) return;
                    if (token.getKind() == END_FILE) return;
                }
            }
            token = getToken();
            if (token.getKind() == CR) return;
            if (token.getKind() == END_FILE) return;
            parseError = true;
            cout << "Parse ERROR: Expected CR, but encountered " << token << endl;
            while (true) { // scan to end of line
                token = getToken();
                if (token.getKind() == CR) return;
                if (token.getKind() == END_FILE) return;
            }
        }
    } else if (token.getKind() == LFSCBKT) {
        NameValueList(token);
//cout << token << endl;
        if (token.getKind() == RTSCBKT) token = getToken();
        while (true) { // scan to end of line
            if (token.getKind() == CR) return;
            if (token.getKind() == END_FILE) return;
            token = getToken();
        }
    } else {
        parseError = true;
        cout << "Parse ERROR: Expected to find start of NAMELIST action command, but encountered " << token << endl;
        while (true) {
            if (token.getKind() == CR) return;
            if (token.getKind() == END_FILE) return;
            token = getToken();
        }
    }
    currStruct = "NONE";
    return;
}

//<NamelistAction> => LFBRK CR <NameValueList> RTBRK <endLine>
//<NameValueList> => <NameValueLine>*
void NameValueList(Token& token) {
//cout << "      in NameValueList( " << token << " )" << endl;
    if (token.getKind() != LFSCBKT) {
        // imposible error
    }
    token = getToken();
    while (true) {
        if (token.getKind() != CR) {
            if (token.getKind() == RTSCBKT) return;
            if (token.getKind() == ID) NameValueLine(token);
            else {
                parseError = true;
                cout << "Parse ERROR: Expected to find name value pair, but encountered " << token << endl;
                while (true) {
                    if (token.getKind() == CR) break;
                    if (token.getKind() == END_FILE) return;
                    token = getToken();
                }
            }
        }
        token = getToken();
    }
}

//<NameValueLine> => <MemberName> EQUAL <Value> CR  # Set member to value specified if valid.
//                | CR
//<MemberName> => ID [ LFSQBKT NUM RTSQBKT ]   # ID must match name of member in <StructName> structure.
//                                             # Member will have a type and array size.
//                                             # If array size is greater than zero, subscript
//                                             # is required and NUM must be within array size.
//<Value> => <booleanValue>  # Type of value must match type of member.
//        | <integerValue>
//        | <stringValue>
//<booleanValue> => TRUE | FALSE
//<integerValue> => NUM
//<stringValue> => TEXT
void NameValueLine(Token& token) {
//cout << "      in NameValueLine( " << token << " )" << endl;
    string member = token.getLexeme();
    // check that ID is name of member in currStruct
    StructMemberOrg nameValueOrg = getNLstructPairMap(currStruct, member);
    if (nameValueOrg.typ == VOID) {
        parseError = true;
        cout << "Parse ERROR: Member Type for " << member <<" not found in " << currStruct << endl;
        while (true) {
            if (token.getKind() == CR) return;
            if (token.getKind() == END_FILE) return;
            token = getToken();
        }
    }
    int index = 0;
    bool hasSubscript = false;
    token = getToken();
    if (token.getKind() == LFBRK) {
        if (nameValueOrg.arrSize == 0) {
            parseError = true;
            cout << "Parse ERROR: Array subscript not expected for " << member <<" of " << currStruct << endl;
            while (true) {
                if (token.getKind() == CR) return;
                if (token.getKind() == END_FILE) return;
                token = getToken();
            }
        }
        token = getToken();
        if (token.getKind() != NUM) {
            parseError = true;
            cout << "Parse ERROR: Array subscript must be integer NUM for " << member <<" of " << currStruct << endl;
            while (true) {
                if (token.getKind() == CR) return;
                if (token.getKind() == END_FILE) return;
                token = getToken();
            }
        } 
        index = token.getValue();
        hasSubscript = true;
        token = getToken();
        if (token.getKind() != RTBRK) {
            parseError = true;
            cout << "Parse ERROR: Expected RTBRK but got " << token << endl;
            while (true) {
                if (token.getKind() == CR) return;
                if (token.getKind() == END_FILE) return;
                token = getToken();
            }
        }
        token = getToken();
    }
    if (token.getKind() != EQUAL) {
        parseError = true;
        cout << "Parse ERROR: Expected EQUAL but got " << token << endl;
        while (true) {
            if (token.getKind() == CR) return;
            if (token.getKind() == END_FILE) return;
            token = getToken();
        }
    }
    token = getToken();
    // setNLstructPair(string NLstruct, string name, void* val, int indx);
    // with expanded error messages. (bool, int, string and arrays of string only)
    switch (nameValueOrg.typ) { 
        case BOOL : 
            if (token.getKind() != TRUE and token.getKind() != FALSE) {
                parseError = true;
                cout << "Parse ERROR: Expected Boolean value but got " << token << endl;
                while (true) {
                    if (token.getKind() == CR) return;
                    if (token.getKind() == END_FILE) return;
                    token = getToken();
                }
            }
            cout << "    Setting " << currStruct << '.' << member;
            cout << " = " << token.getKind() << endl << flush;
            if (token.getKind() == TRUE)
                 *(bool*)(nameValueOrg.namePos) = true;
            else *(bool*)(nameValueOrg.namePos) = false;
            break;
        case INT : 
            if (token.getKind() != NUM) {
                parseError = true;
                cout << "Parse ERROR: Expected Integer value but got " << token << endl;
                while (true) {
                    if (token.getKind() == CR) return;
                    if (token.getKind() == END_FILE) return;
                    token = getToken();
                }
            }
            cout << "    Setting " << currStruct << '.' << member;
            cout << " = " << token.getValue() << endl << flush;
            *(int*)(nameValueOrg.namePos) = token.getValue();
            break;
        case STRING : 
            if (token.getKind() != TXT) {
                parseError = true;
                cout << "Parse ERROR: Expected String value but got " << token << endl;
                while (true) {
                    if (token.getKind() == CR) return;
                    if (token.getKind() == END_FILE) return;
                    token = getToken();
                }
            }
            if (hasSubscript) {
                cout << "    Setting " << currStruct << '.' << member << "[" << index << "]";
                cout << " = \"" << token.getLexeme() << '\"'  << endl << flush;
                string* pnt = (string*)(nameValueOrg.namePos);
                *(pnt+index) = token.getLexeme();
            } else {
                cout << "    Setting " << currStruct << '.' << member;
                cout << " = \"" << token.getLexeme() << '\"'  << endl << flush;
                *(string*)(nameValueOrg.namePos) = token.getLexeme();
            }            
            break;
        default : 
            //error message 
            break;
    }
    token = getToken();
    if (token.getKind() != CR) {
        parseError = true;
        cout << "Parse ERROR: Expected CR but got " << token << endl;
        while (true) {
            if (token.getKind() == CR) return;
            if (token.getKind() == END_FILE) return;
            token = getToken();
        }
    }
}

