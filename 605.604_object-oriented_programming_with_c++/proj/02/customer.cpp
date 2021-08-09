/*
 * customer.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the implementation for the Customer class.
 *
 */

#include "customer.hpp"
#include <iomanip>

// initialize the static variable
unsigned int Customer::customer_id_gen_{0};

/*
 * Default constructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
Customer::Customer()
    : customer_id_(++customer_id_gen_), is_senior_(false), arrival_time_(0.0),
      check_in_time_(0.0), vaccination_time_(0.0) {
    std::cout << std::fixed;
    std::cout << std::setprecision(2);
}

/*
 * Set is_senior_ to true
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void Customer::make_senior() {
    is_senior_ = true;
}

/*
 * Set is_senior_ to true
 *
 * Params:
 *  v <double>: new value for arrival_time_
 *
 * Returns:
 *  None
 */
void Customer::set_arrival_time(double v) {
    arrival_time_ = v;
}

/*
 * Set is_senior_ to true
 *
 * Params:
 *  v <double>: new value for check_in_time_
 *
 * Returns:
 *  None
 */
void Customer::set_check_in_time(double v) {
    check_in_time_ = v;
}

/*
 * Set is_senior_ to true
 *
 * Params:
 *  v <double>: new value for vaccination_time_
 *
 * Returns:
 *  None
 */
void Customer::set_vaccination_time(double v) {
    vaccination_time_ = v;
}

/*
 * Get is_senior_
 *
 * Params:
 *  None
 *
 * Returns:
 *  is_senior_ <bool>: flag to determine if Customer is senior
 */
bool Customer::is_senior() const {
    return is_senior_;
}

/*
 * Get arrival_time_
 *
 * Params:
 *  None
 *
 * Returns:
 *  arrival_time_ <double>: arrival time of Customer
 */
double Customer::get_arrival_time() const {
    return arrival_time_;
}

/*
 * Get check_in_time_
 *
 * Params:
 *  None
 *
 * Returns:
 *  check_in_time_ <double>: check-in time of Customer
 */
double Customer::get_check_in_time() const {
    return check_in_time_;
}

/*
 * Get vaccination_time_
 *
 * Params:
 *  None
 *
 * Returns:
 *  vaccination_time_ <double>: vaccination time of Customer
 */
double Customer::get_vaccination_time() const {
    return vaccination_time_;
}

/*
 * Get total time spent waiting to reach a vaccination station
 *
 * Params:
 *  None
 *
 * Returns:
 *  <double>: total time spent waiting to reach a vaccination station
 */
double Customer::get_wait_time() const {
    return arrival_time_ + check_in_time_;
}

/*
 * Get the total amount of time assigned to the Customer object during
 * initialization
 *
 * Params:
 *  None
 *
 * Returns:
 *  <double>: minimum total of all the times of the Customer
 */
double Customer::get_total_time() const {
    return arrival_time_ + check_in_time_ + vaccination_time_;
}

/*
 * Overloaded ostream::<<operator to conveniently display all attributes of the
 * Customer
 *
 * Params:
 *  os <std::ostream&>: output stream object to redirect to. For the scope of
 *                      this project, all outputs are redirected to stdout via
 *                      std::cout
 *  c <Customer&>: reference to the friend Customer object
 *
 * Returns:
 *  <std::ostream&>: modified output stream
 */
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
