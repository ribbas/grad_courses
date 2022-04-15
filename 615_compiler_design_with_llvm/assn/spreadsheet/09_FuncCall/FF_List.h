/*
 * FF_List.h
 * Sabbir Ahmed
 * April 2022
 *
 * Declaration of the FF_List data structure
 */

#ifndef FF_LIST_H
#define FF_LIST_H

#include "Token.h"
#include <iostream>
#include <set>
#include <string>

typedef std::set<TokenKind> SynchSet;

class FF_List {
private:
    SynchSet _synchSet;
    void merge(SynchSet other);

public:
    static SynchSet expFirsts;
    static SynchSet expFollows;
    static SynchSet addOpFirsts;
    static SynchSet addOpFollows;
    static SynchSet termFirsts;
    static SynchSet termFollows;
    static SynchSet mulOpFirsts;
    static SynchSet mulOpFollows;
    static SynchSet factorFirsts;
    static SynchSet factorFollows;
    static SynchSet parenExpFirsts;
    static SynchSet parenExpFollows;

    FF_List();
    FF_List(SynchSet synchSet);
    bool contains(TokenKind kind);
    FF_List operator+(FF_List other);
};

#endif
