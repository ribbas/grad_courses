/*
 * date.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 8 Assignment
 *
 * This file contains the declaration of the methods for the Date class.
 * This implementation has been copied over and modified from the Week 2
 * Assignment.
 *
 */
#ifndef DATE_HPP
#define DATE_HPP

#include <iostream>
#include <string> // for string objects

class Date {

public:
    // default constructor
    Date();

    // constructor with parameters
    Date(int, int, int);

    // setter methods
    void set_year(int);

    void set_month(int);

    void set_day(int);

    // getter methods
    int get_year();

    int get_month();

    int get_day();

    std::string get_month_name(bool = false);

    // print the month, day and year attributes of the date
    friend std::ostream& operator<<(std::ostream&, const Date&);

private:
    // check if the year is leap
    bool check_leap();

    // member attributes
    bool year_set_;
    bool month_set_;
    bool day_set_;
    bool is_leap_;
    int month_;
    int day_;
    int year_;
    std::string month_name_[12] = {
        "January", "February", "March",     "April",   "May",      "June",
        "July",    "August",   "September", "October", "November", "December"};
};

#endif