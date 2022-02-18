// NAMELIST_Support.cpp
// by Allyn Shell
// October 2020

#include "NAMELIST_Support.h"
#include <map>
#include <ctime>
#include <iostream>
using namespace std;


map<string,DefaultFunc> defaultJumpTable;

// Use the name of the namelist struct to set the map to
// the setDefaults function to be called
void initNLdefaultJumpTable (string NLstruct, DefaultFunc func) {
    defaultJumpTable[NLstruct] = func;
}

// check that NLstruct name is found in map
bool verifyStruct(string NLstruct){ // return 0 on success
//cout << "      in verifyStruct(\"" << NLstruct << "\")" << endl;
    if (defaultJumpTable.find(NLstruct) == defaultJumpTable.end()) return 1;
    return 0;
}

// Reset the namelist to defaults for the struct named by NLstruct
bool setNLdefault (string NLstruct) { // return zero on success
//cout << "      in setNLdefault (\"" << NLstruct << "\")" << endl;
    if (defaultJumpTable.find(NLstruct) == defaultJumpTable.end()) return 1;
    defaultJumpTable[NLstruct]();
    return 0;
}


typedef map<string,StructMemberOrg> mapContent;
const int maxMapOrg = 4;
int MapOrgUse = 0;
map<string,StructMemberOrg> mapOrg[maxMapOrg]; // map from name to value type
map<string, mapContent*> structOrg; // map from struct name to mapContent

// put a name-value pair type into the map 
void initNLstructPairMap (string NLstruct, string name, structType typ, 
                       void* pos, int arrSize) {
//cout << "        in initNLstructPairMap(" << NLstruct << ", " << name << ", ...)" << endl;
    if (structOrg.find(NLstruct) == structOrg.end()) {
        if (MapOrgUse >= maxMapOrg) {
            cout << "ERROR:    Too many structs being used as NAMELISTS." << endl;
            cout << "              (Current max = " << maxMapOrg << ")" << endl;
            return;
        }
        mapOrg[MapOrgUse][name] = StructMemberOrg(typ, pos, arrSize);
        structOrg[NLstruct] = &mapOrg[MapOrgUse];
        ++MapOrgUse;
    } else {
        mapContent& stOrg = *(structOrg[NLstruct]);
        stOrg[name] = StructMemberOrg(typ, pos, arrSize);
    }
}

// get a name-value pair type from the map
StructMemberOrg getNLstructPairMap(string NLstruct, string name) {
//cout << "        in getNLstructPairMap(" << NLstruct << ", " << name << ", ...)" << endl;
    StructMemberOrg voidRetVal; // void return value
    if (structOrg.find(NLstruct) == structOrg.end()) {
        cout << "ERROR: CALLING getNLstructPairMap with invalid NAMELIST Struct Name: " << NLstruct << endl;
        return voidRetVal;
    }
    mapContent& stOrg = *(structOrg[NLstruct]);
    if (stOrg.find(name) == stOrg.end()) {
        cout << "ERROR: CALLING getNLstructPairMap with invalid Member Name: " << name << endl;
        return voidRetVal;
    }
    return stOrg[name];
}

// (not used)
// set a name-value pair
void setNLstructPair (string NLstruct, string name, void* val, int indx) {
    //cout << "    in setNLstructPair(...)" << endl;
    if (structOrg.find(NLstruct) == structOrg.end()) {
        cout << "ERROR:    Requested NAMELIST struct " << NLstruct << " not found." << endl;
        return;
    }
    mapContent& stOrg = *(structOrg[NLstruct]);
    if (stOrg.find(name) == stOrg.end()) {
        cout << "ERROR:    Requested member name " << name << " not found in " << NLstruct << "." << endl;
        return;
    }
    StructMemberOrg valOrg = stOrg[name];
    if (indx > valOrg.arrSize) {
        cout << "ERROR:    Array position " << indx << " out of range for " << name << "." << endl;
        return;
    }

    int size = 0;
    switch (valOrg.typ) {
        case BOOL:
            {
                bool* Bpnt = (bool*)(valOrg.namePos) + indx;
                *Bpnt = *(bool*)(val);
            }
            break;

        case INT:
            {
                int* Ipnt = (int*)(valOrg.namePos) + indx;
                *Ipnt = *(int*)(val);
            }
            break;

        case FLOAT:
            {
                float* Fpnt = (float*)(valOrg.namePos) + indx;
                *Fpnt = *(float*)(val);
            }
            break;

        case DOUBLE:
            {
                double* Dpnt = (double*)(valOrg.namePos) + indx;
                *Dpnt = *(double*)(val);
            }
            break;

        case STRING:
            {
                string* Spnt = (string*)(valOrg.namePos) + indx;
                *Spnt = *(string*)(val);
            }
            break;

        case VOID:
            cout << "ERROR:    Type for " << name << " is VOID." << endl;
            break;
    };
}
