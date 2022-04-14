// Node
// Allyn Shell
// July 2019
// Modified by:
// Sabbir Ahmed
// Modified date:
// TBD ... This is to be filled in for HW3

#include "Node.h"
#include "ID_List.h"
#include "SS_Cell.h"

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

void Node::codeGen(SS_Cell* cell) {

    argVals.clear();

    std::vector<llvm::Type*> argList = {llvm::Type::getInt32Ty(*irContext)};
    llvm::FunctionType* outputFuncType = llvm::FunctionType::get(
        llvm::Type::getVoidTy(*irContext), argList, false);
    llvm::Function* printdFunc =
        llvm::Function::Create(outputFuncType, llvm::Function::ExternalLinkage,
                               "printd", *cell->module);

    std::vector<std::string> args = cell->controllers.getList();
    std::vector<llvm::Type*> funcArgs(args.size(),
                                      llvm::Type::getInt32Ty(*irContext));
    llvm::FunctionType* funcType = llvm::FunctionType::get(
        llvm::Type::getInt32Ty(*irContext), funcArgs, false);
    llvm::Function* func =
        llvm::Function::Create(funcType, llvm::Function::ExternalLinkage,
                               cell->id + "_exp", cell->module.get());

    // set names for all arguments
    unsigned argIx = 0;
    std::string namedArg = "";
    for (llvm::Argument& arg : func->args()) {
        namedArg = args[argIx++];
        argVals.push_back(cell->getTOC()->getCell(namedArg)->value);
        arg.setName(namedArg);
        cell->namedValues[namedArg] = &arg;
    }

    llvm::BasicBlock* basicBlock =
        llvm::BasicBlock::Create(*irContext, "entry", func);
    irBuilder->SetInsertPoint(basicBlock);
    walkCodeGen(cell->getTOC(), cell);

    std::vector<llvm::Value*> heh = {irValue};
    irBuilder->CreateCall(printdFunc, heh, "lol");

    irBuilder->CreateRet(irValue);
}

void Node::evaluate(llvm::Expected<llvm::JITEvaluatedSymbol> exprSym) {

    switch (argVals.size()) {

        case 0: {
            value = ((int (*)())(intptr_t)exprSym->getAddress())();
            return;
        }

        case 1: {
            value = ((int (*)(int))(intptr_t)exprSym->getAddress())(argVals[0]);
            return;
        }

        case 2: {
            value = ((int (*)(int, int))(intptr_t)exprSym->getAddress())(
                argVals[0], argVals[1]);
            return;
        }

        case 3: {
            value = ((int (*)(int, int, int))(intptr_t)exprSym->getAddress())(
                argVals[0], argVals[1], argVals[2]);
            return;
        }

        case 4: {
            value =
                ((int (*)(int, int, int, int))(intptr_t)exprSym->getAddress())(
                    argVals[0], argVals[1], argVals[2], argVals[3]);
            return;
        }

        case 5: {
            value = ((int (*)(int, int, int, int, int))(
                         intptr_t)exprSym->getAddress())(
                argVals[0], argVals[1], argVals[2], argVals[3], argVals[4]);
            return;
        }

        case 6: {
            value = ((int (*)(int, int, int, int, int, int))(
                         intptr_t)exprSym->getAddress())(
                argVals[0], argVals[1], argVals[2], argVals[3], argVals[4],
                argVals[5]);
            return;
        }

        case 7: {
            value = ((int (*)(int, int, int, int, int, int, int))(
                         intptr_t)exprSym->getAddress())(
                argVals[0], argVals[1], argVals[2], argVals[3], argVals[4],
                argVals[5], argVals[6]);
            return;
        }

        case 8: {
            value = ((int (*)(int, int, int, int, int, int, int, int))(
                         intptr_t)exprSym->getAddress())(
                argVals[0], argVals[1], argVals[2], argVals[3], argVals[4],
                argVals[5], argVals[6], argVals[7]);
            return;
        }

        default: {
            value = 0;
            error = true;
            std::cerr << "Function exceeded maximum number of arguments "
                         "allowed\n";
            return;
        }
    }
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

    error = false;
    if (!tok) {
        error = true;
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
            irValue = llvm::ConstantInt::get(*irContext,
                                             llvm::APInt(32, tok->getValue()));
            return;
        }

        case ADD: {

            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateAdd(left->irValue, right->irValue, "addtmp");
            return;
        }

        case SUB: {
            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateSub(left->irValue, right->irValue, "subtmp");
            return;
        }

        case MULT: {
            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateMul(left->irValue, right->irValue, "multmp");

            return;
        }

        case DIV: {
            if (!left || !right) {
                irValue = nullptr;
                return;
            }
            irValue =
                irBuilder->CreateUDiv(left->irValue, right->irValue, "divtmp");
            return;
        }

        default: {
            irValue = nullptr;
            return;
        }
    }
}

void Node::walkTreePrintAttributes(std::ostream& os, int indentation) {
    int ind = indentation;
    char tab = '\t';
    os << tab;
    while (ind) {
        os << "|" << tab;
        --ind;
    }
    os << this << std::endl << std::flush;
    ind = indentation + 1;
    if (left) {
        left->walkTreePrintAttributes(os, ind);
    }
    if (right) {
        right->walkTreePrintAttributes(os, ind);
    }
    return;
}

std::ostream& operator<<(std::ostream& os, Node& n) {
    if (n.tok) {
        if (n.tok->getKind() == ID) {
            std::cout << "ids are ";
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

std::ostream& operator<<(std::ostream& os, Node* n) {
    return os << *n;
}
