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
#include <string>
using namespace std;

class Node;

enum Op { op_NONE, op_ADD, op_SUB, op_MULT, op_DIV }; // Expression operator
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
	Node* expNode = 0;

public:
    SS_Cell();
	~SS_Cell();

	TableOfCells* getTOC() { return SS_Cell::TOC; }
	string getID() { return id; }
	CellArrayColumn getCellArrayColumn() { return (CellArrayColumn)col; }
	char getColChar() { return (char)('A' + col); }
	int getCol() { return col; }
	int getRow() { return row; }

    void setTXTCell(const string txt);
    void setNUMCell(const int num, int sign = 1);
    void setNUMCell(const string num, int sign = 1);
//	void setEXPCell(SS_Cell* lf, Op op, SS_Cell* rt);
	void clearCell();

	//void setLeft(const string id);
	//void setOp(const Op o);
	//void setRight(const string id);
	void setExpNode(Node* node) { expNode = node; }
	Node* getExpNode() { return expNode; }

	void setKind(CellKind k) { kind = k; }
	CellKind getKind() { return kind; }

	void setStatusAction(CellStatusAction s) { state = s; }
	CellStatusAction getStatusAction() { return state; }

	void setError(bool t) { error = t; }
	bool getError() { return error; }

	void setValue(int v) { value = v; }
	int getValue() { return value; }
	
	void setDisplay(int val);
	void setDisplay(string d);
	string getDisplay() {return display;}

	void setEquation(string eq) { equation = eq; }
	string getEquation() { return equation; }

	void addUser(const int row, const int col) { users.addID(row, col); }
	void dropUser(const int row, const int col) { users.dropID(row, col); }

	// HW3 after making an AST call this routine
    void calculateExpression(SS_Cell* root = 0, bool err = false);

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

	void printTable(ostream& os);

	SS_Cell* getCell(string id);
	SS_Cell* getCell(CellArrayColumn ac, int row);
	SS_Cell* getCell(char ch, int row);
	SS_Cell* getCell(int col, int row);
};

#endif // SS_CELL_H_
