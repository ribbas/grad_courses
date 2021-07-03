/*
 * item.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the function declarations for the Item class.
 *
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Item {

public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    Item(std::string, float, int = 0);

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void set_name(std::string);

    void set_price(float);

    void set_count(int);

    void dec_count();

    std::string get_name();

    float get_price();

    int get_count();

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    std::string name_;
    float price_;
    int count_;
};

#endif
