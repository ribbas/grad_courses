/*
 * date.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Assignment 2
 *
 * This file contains the implementation of the methods for the Date class.
 *
 */

#include "date.hpp"

#include <iostream> // for displaying output to stdout

/* ------------------------ CONSTRUCTORS ------------------------ */

/*
 * Default constructor
 *
 * Initializes all member attributes with default values.
 *
 */
Date::Date()
    : year_set_(false), month_set_(false), day_set_(false), is_leap_(false), month_(-1), day_(-1),
      year_(-1) {
    std::cout << "Empty date initialized\n";
}

/*
 * Default constructor
 *
 * Initialize all member attributes with parameter values.
 * The constructor sets the year, month and day in order to enforce their respective constraints.
 *
 * Params:
 *  year <int>: year of the date
 *  month <int>: month of the date
 *  day <int>: day of the date
 *
 */
Date::Date(int year, int month, int day)
    : year_set_(false), month_set_(false), day_set_(false), is_leap_(false), month_(-1), day_(-1),
      year_(-1) {
    set_year(year);
    set_month(month);
    set_day(day);
}

/* ------------------------ SETTERS ------------------------ */

/*
 * Set year of date and checks if it is a leap year
 *
 * Params:
 *  year <int>: year of the date
 *
 * Returns:
 *  None
 *
 */
void Date::set_year(int year) {

    if (year > 0) {
        year_ = year;
        year_set_ = true;
        is_leap_ = check_leap();
    } else {
        throw std::invalid_argument("Invalid year");
    }
}

/*
 * Set month of date.
 *
 * Params:
 *  month <int>: month of the date
 *
 * Returns:
 *  None
 *
 */
void Date::set_month(int month) {

    if (month > 0 && month < 13) {
        month_ = month;
        month_set_ = true;
    } else {
        throw std::invalid_argument("Invalid month");
    }
}

/*
 * Set day of date.
 * The method verifies the day being set for the date is valid based on the year and month.
 *
 * Params:
 *  day <int>: day of the date
 *
 * Returns:
 *  None
 *
 */
void Date::set_day(int day) {

    // the year and month must be set first
    if (month_set_ && year_set_) {

        // minimum value for day
        if (day > 0) {

            // depending on month set, check against the maximum value for day
            switch (month_) {

                // Jan, Mar, May, Jul, Aug, Oct, Dec
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

                // Apr, Jun, Sep, Nov
                case 4:
                case 6:
                case 9:
                case 11: {

                    if (day < 31) {
                        break;
                    }
                }

                // Feb
                case 2: {

                    // check if leap year
                    if ((is_leap_ && day < 30) || (!is_leap_ && day < 29)) {
                        break;
                    }
                }

                default: {
                    throw std::invalid_argument("Invalid date for " + get_month_name(false));
                }
            }

            day_ = day;
            day_set_ = true;
        }

    } else {

        throw std::invalid_argument("Please initialize the month and year of the date first");
    }
}

/* ------------------------ GETTERS ------------------------ */

/*
 * Get year of date
 *
 * Params:
 *  year <int>: year of the date
 *
 * Returns:
 *  year_ <int>: year of the date
 *
 */
int Date::get_year() {
    return year_;
}

/*
 * Get month of date
 *
 * Params:
 *  month <int>: month of the date
 *
 * Returns:
 *  month_ <int>: month of the date
 *
 */
int Date::get_month() {
    return month_;
}

/*
 * Get day of date
 *
 * Params:
 *  day <int>: day of the date
 *
 * Returns:
 *  day_ <int>: day of the date
 *
 */
int Date::get_day() {
    return day_;
}

/*
 * Get month name of date
 *
 * Params:
 *  shortened <bool (default=false)>: if true, returns the first 3 characters of the month name
 *
 * Returns:
 *  <std::string>: month name of the date
 *
 */
std::string Date::get_month_name(bool shortened) {

    // get the (month_ - 1)-th index of the month_name_ array
    std::string _month = month_name_[month_ - 1];
    return shortened ? _month.substr(0, 3) : _month;
}

/* ------------------------ OTHER METHODS ------------------------ */

/*
 * Print the date object to stdout
 *
 * Params:
 *  format <std::string (default="YMD")>: set order of the attributes to print
 *
 * Returns:
 *  None
 *
 */
void Date::print_date(std::string format) {

    // if all attributes are set
    if (year_set_ && month_set_ && day_set_) {
        if (format == "YMD") {
            std::cout << year_ << '/' << month_ << '/' << day_ << '\n';
        } else if (format == "DMY") {
            std::cout << day_ << '/' << month_ << '/' << year_ << '\n';
        } else if (format == "MDY") {
            std::cout << month_ << '/' << day_ << '/' << year_ << '\n';
        } else {
            throw std::invalid_argument("Please input a valid format");
        }
    }
}

/*
 * Check if the year set is leap
 *
 * Params:
 *  None
 *
 * Returns:
 *  <bool>: is leap
 *
 */
bool Date::check_leap() {
    // if year is divisible by 400 or divisible by 4 and not 100
    return ((!(year_ % 4) && (year_ % 100)) || !(year_ % 400));
}
