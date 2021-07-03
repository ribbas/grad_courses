/*
 * vendingmachine.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the function declarations for the VendingMachine class.
 *
 */

#ifndef VENDINGMACHINE_HPP
#define VENDINGMACHINE_HPP

#include "item.hpp"

#include <vector>

class VendingMachine {

public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    VendingMachine(std::string, int, int);

    /* ------------------------ DESTRUCTORS ------------------------ */
    ~VendingMachine();

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void stock_item(std::string, float, int, int, int);

    void display_menu();

    void add_money(float);

    std::string get_item_name(int, int);

    float get_item_price(int, int);

    int get_item_count(int, int);

    bool pick_item(int, int);

private:
    /* ------------------------ PRIVATE METHODS ------------------------ */
    Item* locate_item(int, int);

    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    std::vector<std::vector<Item*>> inventory_;
    std::string name_;
    float balance_;
    int num_rows_, num_cols_, col_min_offset_, col_max_offset_;
};

#endif
