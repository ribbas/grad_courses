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

class SS_Cell;
class TableOfCells;

class Node {
public:
    Node() {}
    virtual ~Node();

    int value = 0;
    bool error = false;

    Node* left = 0;
    Token* tok = 0;
    Node* right = 0;

    // add all the IDs to the Controllers list
    void walkTreeAddIDs(SS_Cell* cell);

    // calculate value
    void walkTreeCalculateValue(SS_Cell* cell);

    // display attributes
    void walkTreePrintAttributes(ostream& os, int indentation = 0);
    friend ostream& operator<<(ostream& os, Node& n);
    friend ostream& operator<<(ostream& os, Node* n);

    llvm::Value* codeGen() {
        if (tok->getKind() == NUM) {
            double val = std::stof(tok->getLexeme());
            return llvm::ConstantFP::get(*llvmContext, llvm::APFloat(val));
        }
        return nullptr;
    }

private:
    void walkTreeCalculateValue(TableOfCells* TOC);
};

#endif // NODE_H
