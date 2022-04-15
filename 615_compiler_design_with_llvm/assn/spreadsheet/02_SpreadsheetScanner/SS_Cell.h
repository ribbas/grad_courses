// SS_Cell.h
// Allyn Shell
// Feb 2018

#ifndef SS_CELL_H_
#define SS_CELL_H_

#include <string>
using namespace std;


enum Op { op_NONE, op_ADD, op_SUB, op_MULT, op_DIV }; // Expression operator
enum CellKind { BLANK, TEXT, NUMBER, EXPRESSION, DEAD }; // Cell kind
enum CellArrayColumn { A, B, C, D, E, F };
enum CellStatusAction { EMPTY, CALC, READY, ERROR };

class TableOfCells;

class SS_Cell {
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

	// expression
	// Note: these pointers do not own the cells
	// (do not delete)
	SS_Cell* left;
	Op op;
	SS_Cell* right;

public:
    SS_Cell();
	~SS_Cell() {}

	string getID() { return id; }
	CellArrayColumn getCellArrayColumn() { return (CellArrayColumn)col; }
	char getColChar() { return (char)('A' + col); }
	int getCol() { return col; }
	int getRow() { return row; }

    void setTXTCell(const string txt);
    void setNUMCell(const int num, int sign = 1);
    void setNUMCell(const string num, int sign = 1);
	void setEXPCell(SS_Cell* lf, Op op, SS_Cell* rt);
	void clearCell();

	void setLeft(const string id);
	void setOp(const Op o);
	void setRight(const string id);

	void setKind(CellKind k) { kind = k; }
	CellKind getKind() { return kind; }

	void setStatusAction(CellStatusAction s) { state = s; }
	CellStatusAction getStatusAction() { return state; }

	void setError(bool t) { error = t; }
	bool isError() { return error; }

	void setValue(int v) { value = v; }
	int getValue() { return value; }
	
	void setDisplay(int val);
	void setDisplay(string d);
	string getDisplay() {return display;}

    void calculateExpression();
private:
    void setID(int i, int j);

	friend ostream& operator<<(ostream& os, const SS_Cell& c);
    friend ostream& operator<<(ostream& os, const SS_Cell* c);
};


class TableOfCells {
	SS_Cell cell[10][6];
	SS_Cell badCell;
public:
	TableOfCells(); // initializes cell IDs
	~TableOfCells() {}

	// calculate cells that need computation
	// for HW2 from top left row-wise.
	void calculateAllCells();

	void printTable(ostream& os);

	SS_Cell* getCell(string id);
	SS_Cell* getCell(CellArrayColumn ac, int row);
	SS_Cell* getCell(char ch, int row);
	SS_Cell* getCell(int col, int row);
};

#endif // SS_CELL_H_
