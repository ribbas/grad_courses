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
    /* ------------------------ CONSTRUCTORS ------------------------ */
    Customer();

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void make_senior();

    bool is_senior() const;

    void set_arrival_time(double);

    void set_check_in_time(double);

    void set_vaccination_time(double);

    double get_arrival_time() const;

    double get_check_in_time() const;

    double get_vaccination_time() const;

    double get_wait_time() const;

    double get_total_time() const;

    friend std::ostream& operator<<(std::ostream&, const Customer&);

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    static unsigned int customer_id_gen_;
    int customer_id_;
    bool is_senior_;
    double arrival_time_, check_in_time_, vaccination_time_;
};

#endif
