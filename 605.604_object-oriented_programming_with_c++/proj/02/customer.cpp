#include "customer.hpp"
#include <iomanip>

unsigned int Customer::customer_id_gen_{0};

Customer::Customer()
    : customer_id_(++customer_id_gen_), is_senior_(false), arrival_time_(0.0),
      check_in_time_(0.0), vaccination_time_(0.0) {
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
}

bool Customer::is_senior() const {
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

double Customer::get_arrival_time() const {
    return arrival_time_;
}

double Customer::get_check_in_time() const {
    return check_in_time_;
}

double Customer::get_vaccination_time() const {
    return vaccination_time_;
}

double Customer::get_wait_time() const {
    return arrival_time_ + check_in_time_;
}

double Customer::get_total_time() const {
    return arrival_time_ + check_in_time_ + vaccination_time_;
}

std::ostream& operator<<(std::ostream& os, const Customer& c) {

    os << std::right << std::setw(4) << std::setfill(' ') << c.customer_id_
       << " | ";
    os << std::right << std::setw(1) << std::setfill(' ') << c.is_senior()
       << " | ";
    os << std::right << std::setw(6) << std::setfill(' ')
       << c.get_arrival_time() << " | ";
    os << std::right << std::setw(4) << std::setfill(' ')
       << c.get_check_in_time() << " | ";
    os << std::right << std::setw(5) << std::setfill(' ')
       << c.get_vaccination_time() << " |";

    return os;
}
