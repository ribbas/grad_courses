/*
 * state.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 9 Assignment #2
 *
 * This file contains the implementations for the State class
 *
 */

#include "state.hpp"

/*
 * Default constructor
 *
 */
State::State() : name_(""), capital_name_("") {}

/*
 * Parameterized constructor
 *
 */
State::State(std::string name, std::string capital_name)
    : name_(name), capital_name_(capital_name) {}

/*
 * Return state name
 *
 * Params:
 *  None
 *
 * Returns:
 *  name_ <std::string&>: name of state
 *
 */
std::string& State::get_name() {
    return name_;
}

/*
 * Set state name
 *
 * Params:
 *  name <std::string>: name of state
 *
 * Returns:
 *  None
 *
 */
void State::set_name(std::string name) {
    name_ = name;
}

/*
 * Return capital name
 *
 * Params:
 *  None
 *
 * Returns:
 *  name_ <std::string&>: name of capital
 *
 */
std::string& State::get_capital_name() {
    return capital_name_;
}

/*
 * Set capital name
 *
 * Params:
 *  name <std::string>: name of capital
 *
 * Returns:
 *  None
 *
 */
void State::set_capital_name(std::string capital_name) {
    capital_name_ = capital_name;
}
