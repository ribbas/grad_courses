/*
 * FF_List.cpp
 * Sabbir Ahmed
 * April 2022
 *
 * Implementation of the FF_List data structure
 */

#include "FF_List.h"

// Token        Firsts          Follows
// exp	        NUM, ID, (      ), EOF
SynchSet FF_List::expFirsts = {NUM, ID, LPAREN};
SynchSet FF_List::expFollows = {RPAREN, T_EOF};

// Token        Firsts          Follows
// add-op	    +, -            NUM, ID, (
SynchSet FF_List::addOpFirsts = {ADD, SUB};
SynchSet FF_List::addOpFollows = {NUM, ID, LPAREN};

// Token        Firsts          Follows
// term	        NUM, ID, (      +, -, ), EOF
SynchSet FF_List::termFirsts = {NUM, ID, LPAREN};
SynchSet FF_List::termFollows = {ADD, SUB, RPAREN, T_EOF};

// Token        Firsts          Follows
// mult-op	    *, /            NUM, ID, (
SynchSet FF_List::mulOpFirsts = {MULT, DIV};
SynchSet FF_List::mulOpFollows = {NUM, ID, LPAREN};

// Token        Firsts          Follows
// factor	    NUM, ID, (      *, /, +, -, ), EOF
SynchSet FF_List::factorFirsts = {NUM, ID, LPAREN};
SynchSet FF_List::factorFollows = {MULT, DIV, ADD, SUB, RPAREN, T_EOF};

// Token        Firsts          Follows
// paren-exp	(               *, /, +, -, ), EOF
SynchSet FF_List::parenExpFirsts = {LPAREN};
SynchSet FF_List::parenExpFollows = {MULT, DIV, ADD, SUB, RPAREN, T_EOF};

// Default constructor
FF_List::FF_List() : _synchSet({}) {}

// Parameterized constructor
FF_List::FF_List(SynchSet synchSet) : _synchSet(synchSet) {}

// Search for item in set
bool FF_List::contains(TokenKind kind) {
    return (_synchSet.find(kind) != _synchSet.end());
}

// Perform a union with the other set
void FF_List::merge(SynchSet other) {
    _synchSet.insert(other.begin(), other.end());
}

// Overloaded binary add operator to perform a union with the other set
FF_List FF_List::operator+(FF_List other) {
    FF_List b(this->_synchSet);
    b.merge(other._synchSet);
    return b;
}
