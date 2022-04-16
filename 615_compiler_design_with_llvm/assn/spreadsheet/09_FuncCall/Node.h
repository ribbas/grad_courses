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

#include "LLVM_Util.h"
#include "Token.h"

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
    std::vector<int> argVals;

    // add all the IDs to the Controllers list
    void walkTreeAddIDs(SS_Cell* cell);

    // calculate value
    void codeGen(SS_Cell* cell);
    void evaluate(llvm::Expected<llvm::JITEvaluatedSymbol> exprSym);

    // display attributes
    void walkTreePrintAttributes(std::ostream& os, int indentation = 0);
    friend std::ostream& operator<<(std::ostream& os, Node& n);
    friend std::ostream& operator<<(std::ostream& os, Node* n);

  private:
    void walkCodeGen(TableOfCells* TOC, SS_Cell* cell);
};

#endif // NODE_H
