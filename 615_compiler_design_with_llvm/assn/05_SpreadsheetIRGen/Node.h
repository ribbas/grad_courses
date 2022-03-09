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
    void walkCodeGen(SS_Cell* cell);

    // display attributes
    void walkTreePrintAttributes(ostream& os, int indentation = 0);
    friend ostream& operator<<(ostream& os, Node& n);
    friend ostream& operator<<(ostream& os, Node* n);

    llvm::Value* codeGen() {

        if (tok) {
            switch (tok->getKind()) {
                case NUM: {
                    double val = std::stoi(tok->getLexeme());
                    std::cout << val << " here\n";
                    llvm::Value* v1 = llvm::ConstantInt::get(
                        *irContext, llvm::APInt(64, left->value));
                    llvm::Value* v2 =
                        llvm::ConstantInt::get(*irContext, llvm::APInt(64, 2));
                    return irBuilder->CreateAdd(v1, v2, "addtmp");
                }

                case ID: {

                    std::cout << "not doing anything yet\n";
                    return nullptr;
                }

                default: {
                    return nullptr;
                }
            };
        }
    }

private:
    void walkTreeCalculateValue(TableOfCells* TOC);
    void walkCodeGen(TableOfCells* TOC, SS_Cell* cell);
};

#endif // NODE_H
