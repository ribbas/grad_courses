#include "customer.hpp"

Customer::Customer()
    : is_senior_(false), arrival_time_(0.0), check_in_time_(0.0),
      vaccination_time_(0.0) {}

bool Customer::is_senior() {
    return is_senior_;
}

void Customer::make_senior() {
    is_senior_ = true;
}

void Customer::set_arrival_time(double v) {
    arrival_time_ = v;
}

void Customer::set_check_in_time(double v) {
    check_in_time_ = v;
}

void Customer::set_vaccination_time(double v) {
    vaccination_time_ = v;
}

double Customer::get_arrival_time() {
    return arrival_time_;
}

double Customer::get_check_in_time() {
    return check_in_time_;
}

double Customer::get_vaccination_time() {
    return vaccination_time_;
}

double Customer::get_wait_time() {
    return arrival_time_ + check_in_time_;
}

double Customer::get_total_time() {
    return arrival_time_ + check_in_time_ + vaccination_time_;
}
