#include "customer.hpp"

Customer::Customer() : current_state_(unknown), is_senior_(false) {}

bool Customer::is_senior() {
    return is_senior_;
}

void Customer::make_senior() {
    is_senior_ = true;
}

void Customer::progress() {
    if (current_state_ != exited) {
        current_state_++;
    }
}

bool Customer::is_unknown() {
    return current_state_ == unknown;
}

bool Customer::is_arrived() {
    return current_state_ == arrived;
}

bool Customer::is_verified() {
    return current_state_ == verified;
}

bool Customer::is_in_line() {
    return current_state_ == in_line;
}

bool Customer::is_vaccinated() {
    return current_state_ == vaccinated;
}

bool Customer::is_exited() {
    return current_state_ == exited;
}

int Customer::get_state() {
    return current_state_;
}
