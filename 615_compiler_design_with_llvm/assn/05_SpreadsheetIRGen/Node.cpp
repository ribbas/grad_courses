// Node
// Allyn Shell
// July 2019
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#include "Node.h"
#include "ID_List.h"
#include "SS_Cell.h"
#include <iostream>
using namespace std;

Node::~Node() {
    delete left;
    delete tok;
    delete right;
}

void Node::walkTreeAddIDs(SS_Cell* cell) {
    if (tok && tok->getKind() == ID) {
        cell->newControllers.addID(tok->getLexeme());
    }
    if (left) {
        left->walkTreeAddIDs(cell);
    }
    if (right) {
        right->walkTreeAddIDs(cell);
    }
}

void Node::walkTreeCalculateValue(SS_Cell* cell) {
    walkTreeCalculateValue(cell->getTOC());
}

void Node::walkCodeGen(SS_Cell* cell) {
    if (cell->id.length()) {
        vector<llvm::Type*> argList(cell->controllers.size(),
                                    llvm::Type::getInt32Ty(*irContext));
        llvm::FunctionType* FT = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(*irContext), argList, false);
        llvm::Function* Func =
            llvm::Function::Create(FT, llvm::Function::ExternalLinkage,
                                   (cell->id + "_exp"), cell->module.get());
        llvm::BasicBlock* BB =
            llvm::BasicBlock::Create(*irContext, "Entry", Func);
        irBuilder->SetInsertPoint(BB);
    }
    walkCodeGen(cell->getTOC(), cell);
}

void Node::walkCodeGen(TableOfCells* TOC, SS_Cell* cell) {

    // check if this has children
    if (left) {
        left->walkCodeGen(TOC, cell);
        if (left->error) {
            return;
        }
    }

    if (right) {
        right->walkCodeGen(TOC, cell);
        if (right->error) {
            return;
        }
    }

    if (!tok) {
        return;
    }

    // SS_Cell* cell;
    bool errVal;

    llvm::Value* lhs = nullptr;
    llvm::Value* rhs = nullptr;
    llvm::Value* exp = nullptr;

    switch (tok->getKind()) {
        case ID: {
            // cell = TOC->getCell(tok->getLexeme());
            // errVal = cell->getError();
            // if (errVal) {
            //     return;
            // }
            return;
        }
        case NUM: {
            exp = llvm::ConstantInt::get(*irContext,
                                         llvm::APInt(32, tok->getValue()));
            break;
        }

        case ADD: {

            if (!left || !right) {
                break;
            }

            lhs = llvm::ConstantInt::get(*irContext,
                                         llvm::APInt(32, left->value));
            rhs = llvm::ConstantInt::get(*irContext, llvm::APInt(32, 10));
            exp = irBuilder->CreateAdd(lhs, rhs, "addtmp");

            break;
        }
        case SUB: {
            if (!left || !right) {
                std::cout << "left or right broken\n";
                break;
            }

            lhs = llvm::ConstantInt::get(*irContext,
                                         llvm::APInt(32, left->value));
            rhs = llvm::ConstantInt::get(*irContext, llvm::APInt(32, 10));
            exp = irBuilder->CreateSub(lhs, rhs, "subtmp");

            break;
        }
        case MULT: {
            if (!left || !right) {
                std::cout << "left or right broken\n";
                break;
            }

            lhs = llvm::ConstantInt::get(*irContext,
                                         llvm::APInt(32, left->value));
            rhs = llvm::ConstantInt::get(*irContext, llvm::APInt(32, 10));
            exp = irBuilder->CreateMul(lhs, rhs, "multmp");

            break;
        }
        case DIV: // integer division
        {
            if (!left || !right) {
                std::cout << "left or right broken\n";
                break;
            }
            // value = left->value / right->value;
            break;
        }
        default: {
            // error = true;
            // value = 0;
            break;
        }
    }

    exp->print(llvm::errs());

    // if (cell->module) {
    //     cell->module->print(llvm::errs(), nullptr);
    // }
    // std::cout << '\n';

    return;
}

void Node::walkTreeCalculateValue(TableOfCells* TOC) {
    // check if this has children
    if (left) {
        left->walkTreeCalculateValue(TOC);
        if (left->error) {
            error = true;
            value = 0;
            return;
        }
    }
    if (right) {
        right->walkTreeCalculateValue(TOC);
        if (right->error) {
            error = true;
            value = 0;
            return;
        }
    }
    error = false;
    if (!tok) {
        error = true;
        value = 0;
        return;
    }
    SS_Cell* cell;
    bool errVal;
    switch (tok->getKind()) {
        case ID: {
            cell = TOC->getCell(tok->getLexeme());
            errVal = cell->getError();
            if (errVal) {
                error = true;
                value = 0;
                return;
            }
            value = cell->getValue();
            return;
        }
        case NUM: {
            value = tok->getValue();
            error = tok->getError();
            return;
        }

        case ADD: {

            if (!left || !right) {
                error = true;
                value = 0;
                return;
            }

            value = left->value + right->value;

            return;
        }
        case SUB: {
            if (!left || !right) {
                error = true;
                value = 0;
                return;
            }

            value = left->value - right->value;
            return;
        }
        case MULT: {
            if (!left || !right) {
                error = true;
                value = 0;
                return;
            }

            value = left->value * right->value;

            return;
        }
        case DIV: // integer division
        {
            if (!left || !right) {
                error = true;
                value = 0;
                return;
            }
            value = left->value / right->value;
            return;
        }
        default: {
            error = true;
            value = 0;
            return;
        }
    }
}

void Node::walkTreePrintAttributes(ostream& os, int indentation) {
    int ind = indentation;
    char tab = '\t';
    os << tab;
    while (ind) {
        os << "|" << tab;
        --ind;
    }
    os << this << endl << flush;
    ind = indentation + 1;
    if (left) {
        left->walkTreePrintAttributes(os, ind);
    }
    if (right) {
        right->walkTreePrintAttributes(os, ind);
    }
    return;
}

ostream& operator<<(ostream& os, Node& n) {
    if (n.tok) {
        if (n.tok->getKind() == ID) {
            os << "ID = " << n.tok->getLexeme() << "; ";
        } else {
            os << n.tok->getKind() << ": ";
        }
    } else {
        os << "No token: ";
    }

    if (n.error) {
        os << "ERROR";
        return os;
    }

    os << "Value = " << n.value;

    return os;
}

ostream& operator<<(ostream& os, Node* n) {
    return os << *n;
}
