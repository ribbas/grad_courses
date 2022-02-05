// SS_Cell.cpp
// Allyn Shell
// Feb 2018
// Modified by:
// TBD ... This is to be filled in for HW2 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW2

#include "SS_Cell.h"
#include "Token.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

TableOfCells* SS_Cell::TOC = 0;

string itos(int value);

// Table of Cells constructor
// sets ID for each cell
TableOfCells::TableOfCells() {
	if (!SS_Cell::TOC) SS_Cell::TOC = this;

	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 6; ++j)
			cell[i][j].setID(i, j);

	badCell.id = "XX";
	badCell.row = -1;
	badCell.col = -1;
	badCell.error = true;
	badCell.kind = DEAD;
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

SS_Cell* TableOfCells::getCell(const string id) {
	if (id.length() != 2) return &badCell;
	int row = (int)id[1] - (int)'0';
	int col = (int)id[0] - (int)'A';
	return getCell(col, row);
}

SS_Cell* TableOfCells::getCell(CellArrayColumn ac, int row) {
	int col = (int)ac;
	return getCell(col, row);
}

SS_Cell* TableOfCells::getCell(char ch, int row) {
	int col = (int)ch - (int)'A';
	return getCell(col, row);
}

SS_Cell* TableOfCells::getCell(int col, int row) {
	if (row < 0 or row > 9) return &badCell;
	if (col < 0 or col > 5) return &badCell;
	return &cell[row][col];
}

void SS_Cell::setDisplay(int val) {
	if (val < -999999) display = "-******";
	else if (val < 0) display = itos(value);
	else if (val < 999999) display = " " + itos(value);
	else if (val < 9999999) display = itos(value);
	else display = "*******";
}

void SS_Cell::setDisplay(string d) {
	if (d.size() < 8)	display = d;
	else display = d.substr(0,7);
}


// calculate cells that need computation
// for HW1 from top left row-wise.
void TableOfCells::calculateAllCells() {
	for (int i = 0; i < 10; ++i)
		for (int j = 0; j < 6; ++j) {
			cell[i][j].calculateExpression();
		}
}

void SS_Cell::calculateExpression() {
	if (kind != EXPRESSION or left == 0 or op == op_NONE or right == 0) return;
	int X = left->getValue();
	int Y = right->getValue();
	switch (op) {
	case op_ADD: value = X + Y; break;
	case op_SUB: value = X - Y; break;
	case op_MULT: value = X * Y; break;
	case op_DIV:
		if (Y == 0) {
			cout << "ERROR: Divide by zero in cell " << id << endl;
			error = true;
			value = 0;
			return;
		}
		value = X / Y; break;
	default:
		cout << "ERROR: Unrecognized operator in cell " << id << endl;
		error = true;
		value = 0;
		break;
	}
	setDisplay(value);
}

void TableOfCells::printTable(ostream& os) {
	const char tab = '\t'; // assumed to be 8 spaces
	const char dash[] = "-------+";
	os << tab;
	os << "|   A" << tab << "|   B" << tab;
	os << "|   C" << tab << "|   D" << tab;
	os << "|   E" << tab << "|   F" << tab;
	os << "|" << endl;
	for (int i = 0; i < 10; ++i) {
		os << ' ' << dash << dash << dash << dash << dash << dash << dash << endl;
		os << "    " << i << tab << '|';
		for (int j = 0; j < 6; ++j) {
			os << cell[i][j].display;
			if (cell[i][j].display.size() < 7) os << tab;
			os << '|';
		}
		os << endl;
	}
	os << ' ' << dash << dash << dash << dash << dash << dash << dash << endl;
	os << endl;
}

// int to string
string itos(int value) {
    ostringstream oss;
    oss << value;
    return oss.str();
}

SS_Cell::SS_Cell() : id(""), error(false), kind(BLANK),
		display("    "), value(0), left(0), op(op_NONE), right(0) {}


void SS_Cell::setTXTCell(const string txt) {
    error = false;
    kind = TEXT;
	setDisplay(txt);
    value = 0;
    left = 0;
    op = op_NONE;
    right = 0;
}

void SS_Cell::setNUMCell(const int num, int sign) {
    error = false;
    kind = NUMBER;
    value = num * sign;
	setDisplay(value);
	left = 0;
    op = op_NONE;
    right = 0;
}

void SS_Cell::setNUMCell(const string num, int sign) {
    error = false;
    kind = NUMBER;
    value = stoi(num) * sign;
	setDisplay(value);
	left = 0;
    op = op_NONE;
    right = 0;
}

void SS_Cell::setEXPCell(SS_Cell* lf, Op o, SS_Cell* rt) {
    error = false;
    kind = EXPRESSION;
    left = lf;
    op = o;
    right = rt;
    // value as exp
    calculateExpression();
	setDisplay(value);
}

void SS_Cell::clearCell() {
	error = false;
	kind = BLANK;
	setDisplay("");
	value = 0;
	left = 0;
	op = op_NONE;
	right = 0;
}

void SS_Cell::setLeft(const string id) {
	left = SS_Cell::TOC->getCell(id);
}

void SS_Cell::setOp(const Op o) {
	op = o;
}

void SS_Cell::setRight(const string id) {
	right = SS_Cell::TOC->getCell(id);
}

// enum CellKind {BLANK, TXT, NUM, EXP, ERROR}; // Cell kind
ostream& operator<<(ostream& os, const SS_Cell& cell) {
	if (cell.error) {os << "ERROR"; return os;}
	switch (cell.kind) {
	case BLANK : os << "    "; break;
	case TEXT : os << cell.display; break;
	case NUMBER : os << cell.value; break;
	case EXPRESSION : os << cell.value; break;
	case DEAD: os << "ERROR"; break;
	}
	return os;
}

ostream& operator<<(ostream& os, const SS_Cell* cell) {
	os << *cell;
	return os;
}
