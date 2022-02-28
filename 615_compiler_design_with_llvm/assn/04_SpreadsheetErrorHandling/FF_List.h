// Original Grammar Rules                    |    Firsts      | Follows
//  <$>       =>  <exp> <eof>                | <ID>, <NUM>, ( | <EOF>
//  <exp>     => <term> {exp'}               | <ID>, <NUM>, ( | <EOF>, )
//  {exp'}    => <+-op> <term> {exp'} | e    |    +, ', e     | <EOF>, )
//  <+-op>  => '+' | '-'                     |    +, -        | <ID>, <NUM>, (
//  <term>    =>  <fact> {term'}             | <ID>, <NUM>, ( | +, -, <EOF>, )
//  {term'}   =>  <*-op> <fact> {term'} | e  |    *, /, e     | +, -, <EOF>, )
//  <*-op> =>  '*' | '/'                     |    *, /        | <ID>, <NUM>, (
//  <fact>    =>  <ID> | <NUM> | <paren-exp> | <ID>, <NUM>, ( | *,  /, +, -,
//                                                              <EOF>, )
//  <paren-exp> => '(' <exp> ')'
//

#ifndef FF_LIST_H
#define FF_LIST_H

#include "Token.h"
#include <set>
#include <string>

typedef std::set<TokenKind> SynchSet;

class FF_List {
private:
    SynchSet _synchSet;

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

    FF_List(SynchSet synchSet);
    SynchSet getSynchSet();
    bool contains(TokenKind kind);
    void merge(SynchSet other);

    FF_List operator+(FF_List& b) {
        FF_List other({});
        this->_synchSet.insert(b.getSynchSet().begin(), b.getSynchSet().end());
        return other;
    }
};

#endif