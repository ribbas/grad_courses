/*
 * customer.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 2
 *
 * This file contains the function declarations for the Customer class.
 *
 */

#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

class Customer {
public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    Customer();

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void make_senior();

    bool is_senior();

    void set_arrival_time(double v) {
        arrival_time_ = v;
    }

    void set_check_in_time(double v) {
        check_in_time_ = v;
    }

    void set_vaccination_time(double v) {
        vaccination_time_ = v;
    }

    double get_arrival_time() {
        return arrival_time_;
    }

    double get_check_in_time() {
        return check_in_time_;
    }

    double get_vaccination_time() {
        return vaccination_time_;
    }

    double get_wait_time() {
        return arrival_time_ + check_in_time_;
    }

    // double get_wait_time() {
    //     return arrival_time_ + check_in_time_ + vaccination_time_;
    // }

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    bool is_senior_;
    double arrival_time_, check_in_time_, vaccination_time_;
};

#endif
