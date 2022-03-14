// SS_Cell.cpp
// Allyn Shell
// Feb 2018
// Modified by:
// Modified date:

#include "SS_Cell.h"
#include "Node.h"
#include "Token.h"

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

TableOfCells* SS_Cell::TOC = 0;

string itos(int value);

SS_Cell::SS_Cell()
    : id(""), kind(BLANK), error(false), display("    "), value(0),
      module(nullptr) {}

SS_Cell::~SS_Cell() {
    if (expNode) {
        // module->getFunction(id + "_exp")->eraseFromParent();
        // module->dropAllReferences();
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
string SS_Cell::getID() {
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

void SS_Cell::setDisplay(string d) {
    if (d.size() < 8)
        display = d;
    else
        display = d.substr(0, 7);
}

string SS_Cell::getDisplay() {
    return display;
}

void SS_Cell::setEquation(string eq) {
    equation = eq;
}

string SS_Cell::getEquation() {
    return equation;
}

void SS_Cell::addUser(const int row, const int col) {
    users.addID(row, col);
}

void SS_Cell::dropUser(const int row, const int col) {
    users.dropID(row, col);
}

void SS_Cell::generateIR() {
    if (expNode) {
        irBuilder->CreateRet(expNode->codeGen(this));
    }
}

void SS_Cell::calculateExpression(SS_Cell* root, bool err) {

    // this set of tests prevent an infinite loop of users
    if (err && error)
        return;                // this prevents the infinite loop
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

    if (kind != EXPRESSION || expNode == 0) {
        value = 0;
        error = true;
        setDisplay("ERROR");
        calculateUserExpressions(root, true);
        return;
    }

    expNode->walkTreeCalculateValue(this);

    // move value to cell
    value = expNode->value;
    error = expNode->error;
    setDisplay(value);
    calculateUserExpressions(root, err);
}

// int to string
string itos(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

void SS_Cell::setTXTCell(const string txt) {
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

void SS_Cell::setNUMCell(const string num) {
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
    // walk AST && add all IDs in AST to list
    node->walkTreeAddIDs(this);
}

void SS_Cell::updateControllerUsers() {
    // row, col identify *this
    ID_List dropCont = controllers - newControllers;
    for (int r = 0; r < 10; ++r)
        for (int c = 0; c < 6; ++c)
            if (dropCont.contains(r, c))
                SS_Cell::TOC->getCell(c, r)->dropUser(row, col);
    ID_List addCont = newControllers - controllers;
    for (int r = 0; r < 10; ++r)
        for (int c = 0; c < 6; ++c)
            if (addCont.contains(r, c))
                SS_Cell::TOC->getCell(c, r)->addUser(row, col);
    controllers = newControllers;
}

void SS_Cell::calculateUserExpressions(SS_Cell* root, bool err) {
    for (int r = 0; r < 10; ++r)
        for (int c = 0; c < 6; ++c)
            if (users.contains(r, c))
                SS_Cell::TOC->getCell(c, r)->calculateExpression(root, err);
}

void SS_Cell::printCellAttributes(ostream& os) {
    os << id << ": col = " << col << "; row = " << row << ": kind = " << kind
       << ": " << endl;
    if (error)
        os << "    error = true; display = " << display << ":" << endl;
    else
        os << "    value = " << value << ": display = " << display << ":"
           << endl;

    os << "    users list = " << users << endl;
    os << "    controllers list = " << controllers << endl;
    if (expNode) {
        os << "    AST: of (( " << equation << " ))" << endl;
        expNode->walkTreePrintAttributes(os);

        os << "    IR:" << endl;
        std::string str;
        llvm::raw_string_ostream output(str);
        module->print(output, nullptr);

        os << output.str();
    }
    return;
}

// enum CellKind {BLANK, TXT, NUM, EXP, ERROR}; // Cell kind
ostream& operator<<(ostream& os, const SS_Cell& cell) {
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

ostream& operator<<(ostream& os, const SS_Cell* cell) {
    return os << *cell;
}
