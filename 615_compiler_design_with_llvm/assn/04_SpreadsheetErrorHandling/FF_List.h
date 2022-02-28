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
#include <algorithm>
#include <string>
#include <vector>

typedef std::vector<TokenKind> TokenSet;

class FF_List {
private:
    TokenSet ffSet;

public:
    // static TokenSet expFirsts;
    // static TokenSet expFollows;
    // static TokenSet addOpFirsts;
    // static TokenSet addOpFollows;
    // static TokenSet termFirsts;
    // static TokenSet termFollows;
    // static TokenSet mulOpFirsts;
    // static TokenSet mulOpFollows;
    // static TokenSet factorFirsts;
    // static TokenSet factorFollows;
    // static TokenSet parenExpFirsts;
    // static TokenSet parenExpFollows;
    FF_List(TokenSet _ffSet) : ffSet(_ffSet) {}

    TokenSet getTokenSet() {
        return ffSet;
    }

    bool contains(TokenKind _kind) {
        return (std::find(ffSet.begin(), ffSet.end(), _kind) != ffSet.end());
    }

    void merge(TokenSet tk) {
        std::move(tk.begin(), tk.end(), std::back_inserter(ffSet));
    }
};

// Token        Firsts          Follows
// $	        NUM, ID, (      $
// exp	        NUM, ID, (      ), eof
// add-op	    +, -            NUM, ID, (
// term	        NUM, ID, (      +, -, ), eof
// mult-op	    *, /            NUM, ID, (
// factor	    NUM, ID, (      *, /, +, -, ), eof
// paren-exp	(               *, /, +, -, ), eof

// class expFirsts : public FF_List {
// public:
//     expFirsts() : FF_List({NUM, ID, LPAREN}) {}
// };
// class expFollows : public FF_List {
// public:
//     expFollows() : FF_List({RPAREN, T_ERROR}) {}
// };

// class addOpFirsts : public FF_List {
// public:
//     addOpFirsts() : FF_List({ADD, SUB}) {}
// };
// class addOpFollows : public FF_List {
// public:
//     addOpFollows() : FF_List({NUM, ID, LPAREN}) {}
// };

// class termFirsts : public FF_List {
// public:
//     termFirsts() : FF_List({NUM, ID, LPAREN}) {}
// };
// class termFollows : public FF_List {
// public:
//     termFollows() : FF_List({ADD, SUB, RPAREN, T_ERROR}) {}
// };

// class mulOpFirsts : public FF_List {
// public:
//     mulOpFirsts() : FF_List({MULT, DIV}) {}
// };
// class mulOpFollows : public FF_List {
// public:
//     mulOpFollows() : FF_List({NUM, ID, LPAREN}) {}
// };

// class factorFirsts : public FF_List {
// public:
//     factorFirsts() : FF_List({NUM, ID, LPAREN}) {}
// };
// class factorFollows : public FF_List {
// public:
//     factorFollows() : FF_List({MULT, DIV, ADD, SUB, RPAREN, T_ERROR}) {}
// };

// class parenExpFirsts : public FF_List {
// public:
//     parenExpFirsts() : FF_List({LPAREN}) {}
// };
// class parenExpFollows : public FF_List {
// public:
//     parenExpFollows() : FF_List({MULT, DIV, ADD, SUB, RPAREN, T_ERROR}) {}
// };

extern FF_List expFirsts;
extern FF_List expFollows;

extern FF_List addOpFirsts;
extern FF_List addOpFollows;

extern FF_List termFirsts;
extern FF_List termFollows;

extern FF_List mulOpFirsts;
extern FF_List mulOpFollows;

extern FF_List factorFirsts;
extern FF_List factorFollows;

extern FF_List parenExpFirsts;
extern FF_List parenExpFollows;

#endif