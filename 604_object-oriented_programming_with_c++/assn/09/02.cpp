/*
 * 02.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 9 Assignment #2
 *
 * This file contains the main function to drive the State class
 *
 */

#include "state.hpp"

#include <iostream>
#include <set>

int main() {

    std::set<State*> state_set;

    // insert State pointers into the set
    state_set.insert(new State("Illinois", "Springfield"));
    state_set.insert(new State("Wisconsin", "Madison"));
    state_set.insert(new State("California", "Sacramento"));
    state_set.insert(new State("New York", "Albany"));
    state_set.insert(new State("Alaska", "Juneau"));

    // print out contents of the set
    for (auto s : state_set) {
        std::cout << s->get_name() << ", " << s->get_capital_name() << '\n';
    }

    // empty the set
    for (auto s : state_set) {
        delete s;
    }

    return 0;
}
