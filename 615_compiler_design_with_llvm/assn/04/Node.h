// Node.h
// Allyn Shell
// July 2019
// Node of AST
// Modified by:
// TBD ... This is to be filled in for HW3 if you make changes
// Modified date:
// TBD ... This is to be filled in for HW3

#ifndef NODE_H
#define NODE_H

#include "Token.h"

class SS_Cell;
class TableOfCells;


class Node {
public:
	Node() {}
	virtual ~Node();

	int value = 0;
	bool error = false;

	Node* left = 0;
	Token* tok = 0;
	Node* right = 0;

	// add all the IDs to the Controllers list
	void walkTreeAddIDs(SS_Cell* cell);

	// calculate value
	void walkTreeCalculateValue(SS_Cell* cell);

	// display attributes
	void walkTreePrintAttributes(ostream& os, int indentation = 0);
	friend ostream& operator<<(ostream& os, Node& n);
	friend ostream& operator<<(ostream& os, Node* n);

private:
	void walkTreeCalculateValue(TableOfCells* TOC);
};

#endif // NODE_H
