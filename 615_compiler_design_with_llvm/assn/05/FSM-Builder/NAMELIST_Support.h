// NAMELIST_Support.h
// by Allyn Shell
// October 2020

// NAMELIST Example 

#ifndef NAMELIST_SUPPORT_H
#define NAMELIST_SUPPORT_H

#include <string>
using namespace std;

typedef void (*DefaultFunc) ();
void initNLdefaultJumpTable (string NLstruct, DefaultFunc func);
bool verifyStruct(string NLstruct);
bool setNLdefault (string NLstruct); // reinitializes the specified namelist

enum structType { VOID, BOOL, INT, FLOAT, DOUBLE, STRING };

// StructMemberOrg contains the name-value pair type which includes the 
// data type (structType), the array size and the location of the data.
class StructMemberOrg {
public:
    StructMemberOrg() : typ(VOID), namePos(0), arrSize(0) {}
    StructMemberOrg(structType typ, void* namePos, int arrSize)
        : typ(typ), namePos(namePos), arrSize(arrSize) {}

    structType typ;
    void* namePos;
    int arrSize;
};

// put a name-value pair type into the map
void initNLstructPairMap (string NLstruct, string name, structType typ,
                          void* pos, int arrSize = 0);
// get a name-value pair type from the map
StructMemberOrg getNLstructPairMap(string NLstruct, string name);

// set a name-value pair
void setNLstructPair (string NLstruct, string name, void* val, int indx = 0);

#endif // NAMELIST_SUPPORT_H
