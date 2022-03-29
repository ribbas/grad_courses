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

Node::Node()
    : value(0), error(false), left(nullptr), tok(nullptr), right(nullptr),
      irValue(nullptr) {}

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

void Node::codeGen(SS_Cell* cell) {

    std::vector<std::string> args = cell->controllers.getList();
    std::vector<llvm::Type*> argList(args.size(),
                                     llvm::Type::getInt32Ty(*cell->irContext));
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*cell->irContext), argList, false);
    llvm::Function* func =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                               cell->id + "_exp", cell->module.get());

    // Set names for all arguments.
    unsigned argIx = 0;
    std::string namedArg = "";
    for (llvm::Argument& arg : func->args()) {
        namedArg = args[argIx++];
        std::cout << namedArg << "|" << cell->getTOC()->getCell(namedArg)->value
                  << "\n";
        cell->argVals.push_back(cell->getTOC()->getCell(namedArg)->value);
        arg.setName(namedArg);
        cell->namedValues[namedArg] = &arg;
    }

    llvm::BasicBlock* BB =
        llvm::BasicBlock::Create(*cell->irContext, "entry", func);
    cell->irBuilder->SetInsertPoint(BB);
    walkCodeGen(cell->getTOC(), cell);
    cell->irBuilder->CreateRet(irValue);

    cell->module->print(cell->irStdout, nullptr);
}

void Node::walkCodeGen(TableOfCells* TOC, SS_Cell* cell) {

    if (left) {
        left->walkCodeGen(TOC, cell);
        if (left->error) {
            irValue = nullptr;
            return;
        }
    }
    if (right) {
        right->walkCodeGen(TOC, cell);
        if (right->error) {
            irValue = nullptr;
            return;
        }
    }
    if (!tok) {
        irValue = nullptr;
        return;
    }
    SS_Cell* refCell;
    bool errVal;
    switch (tok->getKind()) {
        case ID: {
            refCell = TOC->getCell(tok->getLexeme());
            errVal = refCell->getError();
            if (errVal) {
                irValue = nullptr;
                return;
            }
            std::string refCellName = tok->getLexeme();
            irValue = cell->namedValues[refCellName];
            return;
        }
        case NUM: {
            irValue = llvm::ConstantInt::get(*cell->irContext,
                                             llvm::APInt(32, tok->getValue()));
            return;
        }

        case ADD: {

            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue = cell->irBuilder->CreateAdd(left->irValue, right->irValue,
                                                 "addtmp");
            return;
        }
        case SUB: {
            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue = cell->irBuilder->CreateSub(left->irValue, right->irValue,
                                                 "subtmp");
            return;
        }
        case MULT: {
            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue = cell->irBuilder->CreateMul(left->irValue, right->irValue,
                                                 "multmp");

            return;
        }
        case DIV: // integer division
        {
            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue = cell->irBuilder->CreateUDiv(left->irValue, right->irValue,
                                                  "divtmp");
            return;
        }
        default: {
            irValue = nullptr;
            return;
        }
    }
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
