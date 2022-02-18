// SS_Cell.cpp
// Allyn Shell
// Feb 2018
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#include "SS_Cell.h"
#include "Token.h"
#include "Node.h"
#include <string>
#include <iostream>
#include <sstream>
using namespace std;


TableOfCells* SS_Cell::TOC = 0;

string itos(int value);

SS_Cell::~SS_Cell() { delete expNode; }

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

void SS_Cell::calculateExpression(SS_Cell* root, bool err) {
	// this set of tests prevent an infinite loop of users
	if (err and error) return; // this prevents the infinite loop
	if (err and root != this) { // everything in loop is set to error
		err = true;
		error = true;
		setDisplay("ERROR");
		calculateUserExpressions(root,err);
		return;
	}
	if (root == this) { // this identifies a loop
		err = true;
		error = true;
		setDisplay("ERROR");
		calculateUserExpressions(root, err);
		return;
	}
	if (!root) root = this; // first time through

	if (kind != EXPRESSION or expNode == 0) {
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
		display("    "), value(0) {}


void SS_Cell::setTXTCell(const string txt) {
	kind = TEXT;
	value = 0;
	error = false;
	setDisplay(txt);
	delete expNode;
}

void SS_Cell::setNUMCell(const int num, int sign) {
    kind = NUMBER;
    value = num * sign;
	error = false;
	setDisplay(value);
	delete expNode;
}

void SS_Cell::setNUMCell(const string num, int sign) {
	kind = NUMBER;
	if (num == "") {
		value = 0;
		error = true;
		setDisplay("ERROR");
	} else {
		value = stoi(num) * sign;
		error = false;
		setDisplay(value);
	}
	delete expNode;
}

void SS_Cell::clearCell() {
	kind = BLANK;
	value = 0;
	error = false;
	setDisplay("");
	delete expNode;
}

void SS_Cell::identifyControllers(Node* node) {
	newControllers.clear();
	// walk AST and add all IDs in AST to list
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
				SS_Cell::TOC->getCell(c, r)->calculateExpression(root,err);
}

void SS_Cell::printCellAttributes(ostream& os) {
	os << id << ": col = " << col << "; row = " << row << ": kind = " << kind << ": " << endl;
	if (error) os << "    error = true; display = " << display << ":" << endl;
	else os << "    value = " << value << ": display = " << display << ":" << endl;
	// TBD? ... if you modify the SS_Cell class for HW3
	// put any additional cell attributes here

	os << "    users list = " << users << endl;
	os << "    controllers list = " << controllers << endl;
	if (expNode) {
		os << "    AST: of (( " << equation << " ))" << endl;
		expNode->walkTreePrintAttributes(os);
	}
	return;
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
	return os << *cell;
}
