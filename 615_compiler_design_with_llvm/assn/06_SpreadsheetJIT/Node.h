//
// Node.h
//
// Allyn Shell
// July 2019
//
// Modified by:
// Sabbir Ahmed
// 3/10/2022
//
// Node of AST
//

#ifndef NODE_H
#define NODE_H

#include "IR_Gen.h"
#include "Token.h"
#include <iostream>

class SS_Cell;
class TableOfCells;

class Node {
public:
    Node();
    virtual ~Node();

    int value;
    bool error;

    Node* left;
    Token* tok;
    Node* right;
    llvm::Value* irValue;
    llvm::IntrusiveRefCntPtr<llvm::orc::ResourceTracker> RT;

    // add all the IDs to the Controllers list
    void walkTreeAddIDs(SS_Cell* cell);

    // calculate value
    void walkTreeCalculateValue(SS_Cell* cell);
    llvm::Value* codeGen(SS_Cell* cell);

    // display attributes
    void walkTreePrintAttributes(ostream& os, int indentation = 0);
    friend ostream& operator<<(ostream& os, Node& n);
    friend ostream& operator<<(ostream& os, Node* n);

private:
    void walkTreeCalculateValue(TableOfCells* TOC);
    void walkCodeGen(TableOfCells* TOC, SS_Cell* cell);
};

#endif // NODE_H
