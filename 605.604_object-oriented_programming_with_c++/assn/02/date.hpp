/*
 * date.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Assignment 1
 *
 * This file displays the values and sizes of the constants in climits that
 * represent the maximum and minimum values of various in-built data types.
 *
 */
#include <string> // for displaying output to stdout

class Date {

public:
    Date();

    Date(int, int, int);

    void set_day(int);

    void set_month(int);

    void set_year(int);

    int get_month();

    std::string get_month_name(bool);

    int get_day();

    int get_year();

    bool check_leap();

    void print_date(std::string);

private:
    bool month_set = false;
    bool year_set = false;
    bool is_leap = false;
    int month = -1;
    int day = -1;
    int year = -1;
    std::string month_name[12] = {"January",   "February", "March",    "April",
                                  "May",       "June",     "July",     "August",
                                  "September", "October",  "November", "December"};
};
