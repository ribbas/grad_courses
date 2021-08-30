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

#include <iostream>

class Customer {
public:
    /* ---------- CONSTRUCTORS ---------- */
    Customer();

    /* ---------- PUBLIC SETTERS ---------- */
    void make_senior();

    void set_arrival_time(double);

    void set_check_in_time(double);

    void set_vaccination_time(double);

    /* ---------- PUBLIC GETTERS ---------- */
    bool is_senior() const;

    double get_arrival_time() const;

    double get_check_in_time() const;

    double get_vaccination_time() const;

    double get_wait_time() const;

    double get_total_time() const;

    /* ---------- OVERLOADED OPERATORS ---------- */
    friend std::ostream& operator<<(std::ostream&, const Customer&);

private:
    /* ---------- MEMBER ATTRIBUTES ---------- */
    static unsigned int
        customer_id_gen_; // to assign a unique ID to every Customer object
    int customer_id_;
    bool is_senior_;
    double arrival_time_, check_in_time_, vaccination_time_;
};

#endif
