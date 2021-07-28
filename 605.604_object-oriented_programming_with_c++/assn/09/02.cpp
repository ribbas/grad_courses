// constructing lists
#include "state.hpp"
#include <iostream>
#include <set>

int main() {

    auto state_set = std::set<State*>();

    state_set.insert(new State("Illinois", "Springfield"));
    state_set.insert(new State("Wisconsin", "Madison"));
    state_set.insert(new State("California", "Sacramento"));
    state_set.insert(new State("New York", "Albany"));
    state_set.insert(new State("Alaska", "Juneau"));

    for (auto s : state_set) {
        std::cout << s->get_name() << '\n';
    }

    for (auto s : state_set) {
        delete s;
    }

    return 0;
}
