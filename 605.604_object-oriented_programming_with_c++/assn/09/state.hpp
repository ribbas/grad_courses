/*
 * state.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 9 Assignment #2
 *
 * This file contains the declarations for the State class
 *
 */

#include <string>

class State {
public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    State();

    State(std::string, std::string);

    /* ------------------------ PUBLIC METHODS ------------------------ */
    std::string& get_name();

    void set_name(std::string&);

    std::string& get_capital_name();

    void set_capital_name(std::string&);

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    std::string name_, capital_name_;
};
