// SS_Cell.h
// Allyn Shell
// Feb 2018
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef SS_CELL_H_
#define SS_CELL_H_

#include "ID_List.h"
#include "IR_Gen.h"

#include <iostream>
#include <string>

class Node;

enum Op { op_NONE, op_ADD, op_SUB, op_MULT, op_DIV };    // Expression operator
enum CellKind { BLANK, TEXT, NUMBER, EXPRESSION, DEAD }; // Cell kind
enum CellArrayColumn { A, B, C, D, E, F };
enum CellStatusAction { EMPTY, CALC, READY, ERROR };

class TableOfCells;

class SS_Cell {
    friend class Parser;
    friend class Node;
    friend class TableOfCells;

    static TableOfCells* TOC;

    string id;
    int col;
    int row;

    CellKind kind;
    CellStatusAction state;
    bool error;

    string display;
    int value;

    ID_List users;
    ID_List controllers;
    ID_List newControllers;

    // expression root
    string equation;
    Node* expNode = nullptr;

    std::unique_ptr<llvm::Module> module;
    std::map<std::string, llvm::Value*> namedValues;

public:
    SS_Cell();
    ~SS_Cell();

    TableOfCells* getTOC();
    string getID();
    CellArrayColumn getCellArrayColumn();
    char getColChar();
    int getCol();
    int getRow();

    void setTXTCell(const string txt);
    void setNUMCell(const int num, int sign = 1);
    void setNUMCell(const string num);
    void clearCell();

    void setExpNode(Node* node);

    Node* getExpNode();

    void setKind(CellKind k);
    CellKind getKind();

    void setStatusAction(CellStatusAction s);
    CellStatusAction getStatusAction();

    void setError(bool t);
    bool getError();

    void setValue(int v);
    int getValue();

    void setDisplay(int val);
    void setDisplay(string d);
    string getDisplay();

    void setEquation(string eq);
    string getEquation();

    void addUser(const int row, const int col);
    void dropUser(const int row, const int col);

    void calculateExpression(SS_Cell* root = 0, bool err = false);
    void generateIR();

    void identifyControllers(Node* node);
    void updateControllerUsers();
    void calculateUserExpressions(SS_Cell* root = 0, bool err = false);

    void printCellAttributes(ostream& os);
    friend ostream& operator<<(ostream& os, const SS_Cell& c);
    friend ostream& operator<<(ostream& os, const SS_Cell* c);

private:
    void setID(int i, int j);
};

class TableOfCells {
    SS_Cell cell[10][6];
    SS_Cell badCell;

public:
    TableOfCells(); // initializes cell IDs
    ~TableOfCells() {}

    void printAllCells(ostream& os);
    void generateIR();

    void printTable(ostream& os);

    SS_Cell* getCell(string id);
    SS_Cell* getCell(CellArrayColumn ac, int row);
    SS_Cell* getCell(char ch, int row);
    SS_Cell* getCell(int col, int row);
};

#endif // SS_CELL_H_
