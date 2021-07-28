/*
 * ui.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the function declarations for a simple user interface
 * class for the Mini-project 1.
 *
 */

#include <string>

class State {
public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    State(std::string, std::string);

    /* ------------------------ DESTRUCTORS ------------------------ */
    ~State();

    /* ------------------------ PUBLIC METHODS ------------------------ */
    std::string& get_name();

    std::string& get_capital_name();

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    std::string name_, capital_name_;
};
