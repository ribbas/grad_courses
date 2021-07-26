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
    bool is_senior();

    int get_state();

    bool is_unknown();

    bool is_arrived();

    bool is_verified();

    bool is_in_line();

    bool is_vaccinated();

    bool is_exited();

    void progress();

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    bool is_senior_;
    enum states_ { unknown, arrived, verified, in_line, vaccinated, exited };
    int current_state_;
};

#endif
