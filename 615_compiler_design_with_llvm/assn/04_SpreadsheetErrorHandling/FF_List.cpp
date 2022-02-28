#include "FF_List.h"

// Token        Firsts          Follows
// $	        NUM, ID, (      $
// exp	        NUM, ID, (      ), eof
// add-op	    +, -            NUM, ID, (
// term	        NUM, ID, (      +, -, ), eof
// mult-op	    *, /            NUM, ID, (
// factor	    NUM, ID, (      *, /, +, -, ), eof
// paren-exp	(               *, /, +, -, ), eof
SynchSet FF_List::expFirsts = {NUM, ID, LPAREN};
SynchSet FF_List::expFollows = {RPAREN, T_ERROR};

SynchSet FF_List::addOpFirsts = {ADD, SUB};
SynchSet FF_List::addOpFollows = {NUM, ID, LPAREN};

SynchSet FF_List::termFirsts = {NUM, ID, LPAREN};
SynchSet FF_List::termFollows = {ADD, SUB, RPAREN, T_ERROR};

SynchSet FF_List::mulOpFirsts = {MULT, DIV};
SynchSet FF_List::mulOpFollows = {NUM, ID, LPAREN};

SynchSet FF_List::factorFirsts = {NUM, ID, LPAREN};
SynchSet FF_List::factorFollows = {MULT, DIV, ADD, SUB, RPAREN, T_ERROR};

SynchSet FF_List::parenExpFirsts = {LPAREN};
SynchSet FF_List::parenExpFollows = {MULT, DIV, ADD, SUB, RPAREN, T_ERROR};

FF_List::FF_List(SynchSet synchSet) : _synchSet(synchSet) {}

SynchSet FF_List::getSynchSet() {
    return _synchSet;
}

bool FF_List::contains(TokenKind kind) {
    return (_synchSet.find(kind) != _synchSet.end());
}

void FF_List::merge(SynchSet other) {
    _synchSet.insert(other.begin(), other.end());
}
