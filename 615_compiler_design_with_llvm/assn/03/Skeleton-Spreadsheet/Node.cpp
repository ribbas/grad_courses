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
	if (tok and tok->getKind() == ID) cell->newControllers.addID(tok->getLexeme());
	if (left) left->walkTreeAddIDs(cell);
	if (right) right->walkTreeAddIDs(cell);
}

void Node::walkTreeCalculateValue(SS_Cell* cell) {
	walkTreeCalculateValue(cell->getTOC());
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
	case ID :
		cell = TOC->getCell(tok->getLexeme());
		errVal = cell->getError();
		if (errVal) {
			error = true;
			value = 0;
			return;
		}
		value = cell->getValue();
		return;
	case NUM :
		value = tok->getValue();
		error = tok->getError();
		return;
	case ADD :
		if (!left or !right) {
			error = true;
			value = 0;
			return;
		}
		value = left->value + right->value;
		return;
	case SUB :
		if (!left or !right) {
			error = true;
			value = 0;
			return;
		}
		value = left->value - right->value;
		return;
	case MULT :
		if (!left or !right) {
			error = true;
			value = 0;
			return;
		}
		value = left->value * right->value;
		return;
	case DIV : // integer division
		if (!left or !right) {
			error = true;
			value = 0;
			return;
		}
		value = left->value / right->value;
		return;
	default :
		error = true;
		value = 0;
		return;
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
	if (left) left->walkTreePrintAttributes(os, ind);
	if (right) right->walkTreePrintAttributes(os, ind);
	return;
}

ostream& operator<<(ostream& os, Node& n) {
	if (n.tok) {
		if (n.tok->getKind() == ID) {
			   os << "ID = " << n.tok->getLexeme() << "; ";
		} else os << n.tok->getKind() << ": ";
	} else     os << "No token: ";
	// TBD?? ... if you modify the Token class
	// put any additional token attributes here

	if (n.error) {
		os << "ERROR";
		return os;
	}
	os << "Value = " << n.value;
	// TBD?? ... if you modify the Node class
	// put any additional node attributes here

	return os;
}

ostream& operator<<(ostream& os, Node* n) {
	return os << *n;
}
