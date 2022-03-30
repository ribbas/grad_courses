// SS_Cell.cpp
// Allyn Shell
// Feb 2018
// Modified by:
// Modified date:

#include "SS_Cell.h"
#include "Node.h"
#include "Token.h"

#include <sstream>
#include <string>

TableOfCells* SS_Cell::TOC = 0;

std::string itos(int value);

SS_Cell::SS_Cell()
    : id(""), kind(BLANK), error(false), display("    "), value(0),
      expNode(nullptr), irStdout(irCode) {}

SS_Cell::~SS_Cell() {
    if (expNode) {
        delete expNode;
        expNode = nullptr;
    }
    namedValues.clear();
    controllers.clear();
    users.clear();
}

TableOfCells* SS_Cell::getTOC() {
    return SS_Cell::TOC;
}
std::string SS_Cell::getID() {
    return id;
}
CellArrayColumn SS_Cell::getCellArrayColumn() {
    return (CellArrayColumn)col;
}
char SS_Cell::getColChar() {
    return (char)('A' + col);
}
int SS_Cell::getCol() {
    return col;
}
int SS_Cell::getRow() {
    return row;
}

void SS_Cell::setExpNode(Node* node) {
    expNode = node;
}

Node* SS_Cell::getExpNode() {
    return expNode;
}

void SS_Cell::setKind(CellKind k) {
    kind = k;
}

CellKind SS_Cell::getKind() {
    return kind;
}

void SS_Cell::setStatusAction(CellStatusAction s) {
    state = s;
}

CellStatusAction SS_Cell::getStatusAction() {
    return state;
}

void SS_Cell::setError(bool t) {
    error = t;
}

bool SS_Cell::getError() {
    return error;
}

void SS_Cell::setValue(int v) {
    value = v;
}

int SS_Cell::getValue() {
    return value;
}

// Cell set ID
void SS_Cell::setID(int i, int j) {
    char name[3];
    name[0] = 'A' + j;
    name[1] = '0' + i;
    name[2] = 0;
    id = name;
    col = j;
    row = i;
}

void SS_Cell::setDisplay(int val) {
    if (val < -999999)
        display = "-******";
    else if (val < 0)
        display = itos(value);
    else if (val < 999999)
        display = " " + itos(value);
    else if (val < 9999999)
        display = itos(value);
    else
        display = "*******";
}

void SS_Cell::setDisplay(std::string d) {
    if (d.size() < 8)
        display = d;
    else
        display = d.substr(0, 7);
}

std::string SS_Cell::getDisplay() {
    return display;
}

void SS_Cell::setEquation(std::string eq) {
    equation = eq;
}

std::string SS_Cell::getEquation() {
    return equation;
}

void SS_Cell::addUser(const int row, const int col) {
    users.addID(row, col);
}

void SS_Cell::dropUser(const int row, const int col) {
    users.dropID(row, col);
}

void SS_Cell::generateIR() {

    argVals.clear();
    namedValues.clear();
    irStdout.str().clear();

    cellJIT = ExitOnErr(JIT::Create());
    module = std::make_unique<llvm::Module>(id + "_module", *irContext);
    module->setDataLayout(cellJIT->getDataLayout());

    expNode->codeGen(this);
    module->print(irStdout, nullptr);

    ExitOnErr(cellJIT->addModule(
        llvm::orc::ThreadSafeModule(std::move(module), std::move(irContext))));

    llvm::Expected<llvm::JITEvaluatedSymbol> exprSym =
        cellJIT->lookup(id + "_exp");

    if (!exprSym) {
        std::cerr << "Function not found\n";
    }

    evaluate(std::move(exprSym));
    initLLVMContext();
}

void SS_Cell::evaluate(llvm::Expected<llvm::JITEvaluatedSymbol> exprSym) {

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

void SS_Cell::calculateExpression(SS_Cell* root, bool err) {

    // this set of tests prevent an infinite loop of users
    // this prevents the infinite loop
    if (err && error) {
        return;
    }

    if (err && root != this) { // everything in loop is set to error
        err = true;
        error = true;
        setDisplay("ERROR");
        calculateUserExpressions(root, err);
        return;
    }

    if (root == this) { // this identifies a loop
        err = true;
        error = true;
        setDisplay("ERROR");
        calculateUserExpressions(root, err);
        return;
    }

    if (!root) {
        root = this; // first time through
    }

    if (!expNode) {
        value = 0;
        error = true;
        setDisplay("ERROR");
        calculateUserExpressions(root, true);
        return;
    }

    generateIR();

    // move error value to cell
    error = expNode->error;

    setDisplay(value);
    calculateUserExpressions(root, err);
}

// int to std::string
std::string itos(int value) {
    std::stringstream oss;
    oss << value;
    return oss.str();
}

void SS_Cell::setTXTCell(const std::string txt) {
    kind = TEXT;
    value = 0;
    error = false;
    setDisplay(txt);
    if (expNode) {
        delete expNode;
        expNode = nullptr;
    }
}

void SS_Cell::setNUMCell(const int num, int sign) {
    kind = NUMBER;
    value = num * sign;
    error = false;
    setDisplay(num);
    if (expNode) {
        delete expNode;
        expNode = nullptr;
    }
}

void SS_Cell::setNUMCell(const std::string num) {
    kind = NUMBER;
    if (num == "") {
        value = 0;
        error = true;
        setDisplay("ERROR");
    } else {
        value = stoi(num);
        error = false;
        setDisplay(value);
    }
    if (expNode) {
        delete expNode;
        expNode = nullptr;
    }
}

void SS_Cell::clearCell() {
    kind = BLANK;
    value = 0;
    error = false;
    setDisplay("");
    if (expNode) {
        delete expNode;
        expNode = nullptr;
    }
}

void SS_Cell::identifyControllers(Node* node) {
    newControllers.clear();
    if (node) {
        // walk AST && add all IDs in AST to list
        node->walkTreeAddIDs(this);
    }
}

void SS_Cell::updateControllerUsers() {
    // row, col identify *this
    ID_List dropCont = controllers - newControllers;
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 6; ++c) {
            if (dropCont.contains(r, c)) {
                SS_Cell::TOC->getCell(c, r)->dropUser(row, col);
            }
        }
    }
    ID_List addCont = newControllers - controllers;
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 6; ++c) {
            if (addCont.contains(r, c)) {
                SS_Cell::TOC->getCell(c, r)->addUser(row, col);
            }
        }
    }
    controllers = newControllers;
}

void SS_Cell::calculateUserExpressions(SS_Cell* root, bool err) {
    for (int r = 0; r < 10; ++r) {
        for (int c = 0; c < 6; ++c) {
            if (users.contains(r, c)) {
                SS_Cell::TOC->getCell(c, r)->calculateExpression(root, err);
            }
        }
    }
}

void SS_Cell::printCellAttributes(std::ostream& os) {
    os << id << ": col = " << col << "; row = " << row << ": kind = " << kind
       << ": " << std::endl;
    if (error) {
        os << "    error = true; display = " << display << ":" << std::endl;
    } else {
        os << "    value = " << value << ": display = " << display << ":"
           << std::endl;
    }
    os << "    users list = " << users << std::endl;
    os << "    controllers list = " << controllers << std::endl;

    if (expNode) {

        os << "    AST: of (( " << equation << " ))" << std::endl;
        expNode->walkTreePrintAttributes(os);
    }
    return;
}

void SS_Cell::printCellIR(std::ostream& os) {

    os << id << ": (( " << equation << " ))" << std::endl;
    os << irStdout.str();
    irStdout.flush();

    return;
}

// enum CellKind {BLANK, TXT, NUM, EXP, ERROR}; // Cell kind
std::ostream& operator<<(std::ostream& os, const SS_Cell& cell) {
    if (cell.error) {
        os << "ERROR";
        return os;
    }
    switch (cell.kind) {
        case BLANK:
            os << "    ";
            break;
        case TEXT:
            os << cell.display;
            break;
        case NUMBER:
            os << cell.value;
            break;
        case EXPRESSION:
            os << cell.value;
            break;
        case DEAD:
            os << "ERROR";
            break;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const SS_Cell* cell) {
    return os << *cell;
}
