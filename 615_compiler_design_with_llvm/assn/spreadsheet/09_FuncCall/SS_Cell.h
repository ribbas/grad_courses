// SS_Cell.h
// Allyn Shell
// Feb 2018
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef SS_CELL_H
#define SS_CELL_H

#include "ID_List.h"
#include "JIT.h"
#include "LLVM_Util.h"
#include <iostream>
#include <string>

class Node;

enum Op { op_NONE, op_ADD, op_SUB, op_MULT, op_DIV };    // Expression operator
enum CellKind { BLANK, TEXT, NUMBER, EXPRESSION, DEAD }; // Cell kind
enum CellArrayColumn { A, B, C, D, E, F };
enum CellStatusAction { EMPTY, CALC, READY, ERROR };

class TableOfCells;

class SS_Cell {
  private:
    friend class Parser;
    friend class Node;
    friend class TableOfCells;

    static TableOfCells* TOC;

    std::string id;
    int col;
    int row;

    CellKind kind;
    CellStatusAction state;
    bool error;

    std::string display;
    int value;

    ID_List users;
    ID_List controllers;
    ID_List newControllers;

    // expression root
    std::string equation;
    Node* expNode;
    std::map<std::string, llvm::Value*> namedValues;

    std::string irCode;
    llvm::raw_string_ostream irStdout;
    std::unique_ptr<llvm::Module> module;
    std::unique_ptr<JIT> cellJIT;

    void setID(int i, int j);
    void addIRSymbols();
    void generateIR();

  public:
    SS_Cell();
    ~SS_Cell();

    TableOfCells* getTOC();
    std::string getID();
    CellArrayColumn getCellArrayColumn();
    char getColChar();
    int getCol();
    int getRow();

    void setTXTCell(const std::string txt);
    void setNUMCell(const int num, int sign = 1);
    void setNUMCell(const std::string num);
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
    void setDisplay(std::string d);
    std::string getDisplay();

    void setEquation(std::string eq);
    std::string getEquation();

    void addUser(const int row, const int col);
    void dropUser(const int row, const int col);

    void calculateExpression(SS_Cell* root = 0, bool err = false);

    void identifyControllers(Node* node);
    void updateControllerUsers();
    void calculateUserExpressions(SS_Cell* root = 0, bool err = false);

    void printCellAttributes(std::ostream& os);
    void printCellIR(std::ostream& os);
    friend std::ostream& operator<<(std::ostream& os, const SS_Cell& c);
    friend std::ostream& operator<<(std::ostream& os, const SS_Cell* c);
};

class TableOfCells {
  private:
    SS_Cell cell[10][6];
    SS_Cell badCell;

  public:
    TableOfCells(); // initializes cell IDs
    ~TableOfCells() {}

    void printAllCells(std::ostream& os);
    void printIR(std::ostream& os);
    void printTable(std::ostream& os);

    SS_Cell* getCell(std::string id);
    SS_Cell* getCell(CellArrayColumn ac, int row);
    SS_Cell* getCell(char ch, int row);
    SS_Cell* getCell(int col, int row);
};

inline int getCell(int col, int row) {
    return symTab.getCell(col, row)->getValue();
}

#endif // SS_CELL_H
