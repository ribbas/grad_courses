#include "state.hpp"

State::State(std::string name, std::string capital_name)
    : name_(name), capital_name_(capital_name) {}

State::~State() {}

std::string& State::get_name() {
    return name_;
}

std::string& State::get_capital_name() {
    return capital_name_;
}
