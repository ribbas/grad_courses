/*
 * 01.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Assignment 2
 *
 * Driver file for the Date class
 *
 */

#include "date.hpp"

#include <iostream> // for displaying output to stdout

int main() {

    // instantiate a Date object with values
    Date date1(2021, 6, 7);
    std::cout << date1.get_month_name() << '\n';
    date1.print_date();

    // instantiate an empty Date object and set values later
    Date date2;
    date2.set_year(2021);
    date2.set_month(2);
    date2.set_day(28);
    std::cout << date2.get_month_name() << '\n';
    date2.print_date();

    // raise an exception
#ifdef DEBUG
    // instantiate a Date object with invalid values
    Date date3(1900, 2, 29);
    std::cout << date3.get_month_name() << '\n';
    date3.print_date();
#endif
}
