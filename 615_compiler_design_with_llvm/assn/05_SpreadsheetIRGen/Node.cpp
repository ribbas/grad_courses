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
    std::string expName = cell->id + "_exp";
    if (!cell->module->getFunction(expName)) {
        std::vector<std::string> args = cell->controllers.getList();
        vector<llvm::Type*> argList(args.size(),
                                    llvm::Type::getInt32Ty(*irContext));
        llvm::FunctionType* funcType = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(*irContext), argList, false);
        llvm::Function* func =
            llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                                   expName, cell->module.get());

        // Set names for all arguments.
        unsigned Idx = 0;
        std::string arg = "";
        SS_Cell* refCell = nullptr;
        for (auto& Arg : func->args()) {
            arg = args[Idx++];
            Arg.setName(arg);
            cell->namedValues[arg] = &Arg;
            std::cout << "arg val" << cell->namedValues[arg] << '\n';
        }

        llvm::BasicBlock* BB =
            llvm::BasicBlock::Create(*irContext, "Entry", func);
        irBuilder->SetInsertPoint(BB);
    }

    walkCodeGen(cell->getTOC(), cell);

    if (irValue) {
        irValue->print(llvm::errs());
        irBuilder->CreateRet(irValue);
    }

    std::cout << "\n-------------- DONE WALKING ----------\n";
}

// llvm::Value* Node::walkCodeGen(TableOfCells* TOC, SS_Cell* cell) {

//     llvm::Value* v;
//     // check if this has children
//     if (left) {
//         v = left->walkCodeGen(TOC, cell);
//         if (left->error) {
//             return nullptr;
//         }
//     }

//     if (right) {
//         v = right->walkCodeGen(TOC, cell);
//         if (right->error) {
//             return nullptr;
//         }
//     }

//     if (!tok) {
//         return nullptr;
//     }

//     // SS_Cell* cell;
//     bool errVal;

//     // llvm::Value* lhs = nullptr;
//     // llvm::Value* rhs = nullptr;
//     SS_Cell* refCell;

//     switch (tok->getKind()) {
//         case ID: {
//             std::string refCellName = tok->getLexeme();
//             std::cout << "2got cell name: " << refCellName << '\n';
//             refCell = TOC->getCell(refCellName);
//             errVal = refCell->getError();
//             if (errVal) {
//                 return nullptr;
//             }
//             std::cout << "2got cell: " << refCell->getValue() << '\n';
//             v = cell->namedValues[refCellName];
//             v = irBuilder->CreateAdd(v, v, "addtooooo");
//             break;
//         }

//         case NUM: {
//             v = llvm::ConstantInt::get(*irContext,
//                                        llvm::APInt(32, tok->getValue()));
//             break;
//         }

//         case ADD: {

//             if (!left || !right) {
//                 break;
//             }

//             v = llvm::ConstantInt::get(*irContext,
//                                        llvm::APInt(32, left->value));
//             v = irBuilder->CreateAdd(v, v, "addtmp");

//             break;
//         }
//         case SUB: {
//             if (!left || !right) {
//                 break;
//             }

//             v = llvm::ConstantInt::get(*irContext,
//                                        llvm::APInt(32, left->value));
//             // v = llvm::ConstantInt::get(*irContext, llvm::APInt(32, 10));
//             v = irBuilder->CreateSub(v, v, "subtmp");

//             break;
//         }
//         case MULT: {
//             if (!left || !right) {
//                 break;
//             }

//             v = llvm::ConstantInt::get(*irContext,
//                                        llvm::APInt(32, left->value));
//             // v = llvm::ConstantInt::get(*irContext, llvm::APInt(32, 10));
//             v = irBuilder->CreateMul(v, v, "multmp");

//             break;
//         }
//         case DIV: // integer division
//         {
//             if (!left || !right) {
//                 break;
//             }
//             // value = left->value / right->value;
//             break;
//         }
//         default: {
//             // error = true;
//             // value = 0;
//             break;
//         }
//     }

//     return v;
// }

void Node::walkCodeGen(TableOfCells* TOC, SS_Cell* cell) {

    // check if this has children
    if (left) {
        left->walkCodeGen(TOC, cell);
        if (left->error) {
            // error = true;
            irValue = nullptr;
            return;
        }
    }
    if (right) {
        right->walkCodeGen(TOC, cell);
        if (right->error) {
            // error = true;
            irValue = nullptr;
            return;
        }
    }
    // error = false;
    if (!tok) {
        // error = true;
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
                // error = true;
                irValue = nullptr;
                return;
            }
            std::string refCellName = tok->getLexeme();
            irValue = cell->namedValues[refCellName];
            // irValue = cell->getValue();
            return;
        }
        case NUM: {
            irValue = llvm::ConstantInt::get(*irContext,
                                             llvm::APInt(32, tok->getValue()));
            // irValue = tok->getValue();
            // // error = tok->getError();
            return;
        }

        case ADD: {

            if (!left || !right) {
                // error = true;
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateAdd(left->irValue, right->irValue, "addtmp");

            // irValue = left->value + right->value;

            return;
        }
        case SUB: {
            if (!left || !right) {
                // error = true;
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateSub(left->irValue, right->irValue, "subtmp");

            // irValue = left->value - right->value;
            return;
        }
        case MULT: {
            if (!left || !right) {
                // error = true;
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateMul(left->irValue, right->irValue, "multmp");

            // irValue = left->value * right->value;

            return;
        }
        case DIV: // integer division
        {
            if (!left || !right) {
                // error = true;
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateUDiv(left->irValue, right->irValue, "divtmp");
            // irValue = left->value / right->value;
            return;
        }
        default: {
            // error = true;
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
