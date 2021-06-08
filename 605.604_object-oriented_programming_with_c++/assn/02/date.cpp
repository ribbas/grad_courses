/*
 * 01.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Assignment 1
 *
 * This file displays the values and sizes of the constants in climits that
 * represent the maximum and minimum values of various in-built data types.
 *
 */
#include <iostream> // for displaying output to stdout

#include "date.hpp"

Date::Date() { std::cout << "Empty date initialized\n"; }

Date::Date(int year, int month, int day) {
    set_year(year);
    set_month(month);
    set_day(day);
}

void Date::set_day(int day) {

    if (this->month_set && this->year_set) {

        if (day > 0) {

            switch (this->month) {

                case 1:
                case 3:
                case 5:
                case 7:
                case 8:
                case 10:
                case 12: {

                    if (day < 32) {
                        break;
                    }
                }

                case 4:
                case 6:
                case 9:
                case 11: {

                    if (day < 31) {
                        break;
                    }
                }

                case 2: {

                    if ((this->is_leap && day < 30) || (!this->is_leap && day < 29)) {
                        break;
                    }
                }

                default: {
                    throw std::invalid_argument("Invalid date for " + this->get_month_name(false));
                }
            }

            this->day = day;
            this->day_set = true;
        }

    } else {

        throw std::invalid_argument("Please initialize the month and year of the date first");
    }
}

void Date::set_month(int month) {

    if (month > 0 && month < 13) {
        this->month = month;
        this->month_set = true;
    } else {
        throw std::invalid_argument("Invalid month");
    }
}

void Date::set_year(int year) {

    if (year > 0) {
        this->year = year;
        this->year_set = true;
        this->is_leap = check_leap();
    } else {
        throw std::invalid_argument("Invalid year");
    }
}

int Date::get_month() { return this->month; }

std::string Date::get_month_name(bool shortened) {

    std::string _month = this->month_name[this->month - 1];
    return shortened ? _month.substr(0, 3) : _month;
}

int Date::get_day() { return this->day; }

int Date::get_year() { return this->year; }

bool Date::check_leap() {

    return ((!(this->year % 4) && (this->year % 100)) || !(this->year % 400));
}

void Date::print_date(std::string fmt) {

    if (this->year_set && this->month_set && this->day_set) {
        if (fmt == "YMD") {
            std::cout << this->year << '/' << this->month << '/' << this->day << '\n';
        } else if (fmt == "DMY") {
            std::cout << this->day << '/' << this->month << '/' << this->year << '\n';
        } else if (fmt == "MDY") {
            std::cout << this->month << '/' << this->day << '/' << this->year << '\n';
        } else {
            throw std::invalid_argument("Please input a valid format");
        }
    }
}
