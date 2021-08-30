/*
 * vendingmachine.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the implementation for the VendingMachine class.
 *
 */

#include "vendingmachine.hpp"

#include <iomanip>
#include <iostream>

/*
 * Parameterized constructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  name <std::string>: name of the vending machine
 *  num_cols <int>: number of columns
 *  num_rows <int>: number of rows
 *
 */
VendingMachine::VendingMachine(std::string name, int num_cols, int num_rows)
    : name_(name), num_cols_(num_cols), num_rows_(num_rows),
      col_min_offset_(65) {

    // maximum char value of the column
    // i.e. 65 corresponds to the minimum char value 'A' the maximum value will
    // be 90 for 'Z'
    if (num_cols_ > 25) {
        throw std::invalid_argument("Invalid number of columns");
    }
    col_max_offset_ = col_min_offset_ + num_cols_;

    for (int i = 0; i < num_cols_; i++) {

        // initialize an empty column vector and fill it with nullptr
        std::vector<Item*> column;
        for (int j = 0; j < num_rows_; j++) {
            column.push_back(nullptr);
        }
        // push column vectors in the inventory vector of vectors
        inventory_.push_back(column);
    }
}

/*
 * Destructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
VendingMachine::~VendingMachine() {

    // free up the vector of `Item*` vectors
    for (int i = 0; i < num_cols_; i++) {

        for (int j = 0; j < num_rows_; j++) {
            delete inventory_[i][j];
            inventory_[i][j] = nullptr;
        }

        inventory_[i].clear();
        inventory_[i].resize(0);
    }

    inventory_.clear();
    inventory_.resize(0);
}

/*
 * Assign Item to inventory_
 *
 * Params:
 *  name <std::string>: name of item
 *  price <float>: price of item
 *  num_item <int>: quantity of item
 *  col <int>: column number of item
 *  row <int>: row number of item
 *
 * Returns:
 *  None
 *
 */
void VendingMachine::stock_item(std::string name, float price, int num_item,
                                int col, int row) {

    // if the column and row numbers are within bounds
    if (col >= col_min_offset_ && col < col_max_offset_ && row > 0 &&
        row <= num_rows_) {
        auto item = new Item(name, price, num_item);
        inventory_[col - col_min_offset_][row - 1] = item;
    }
}

/*
 * Display information of all the Item objects in inventory_
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
void VendingMachine::display_menu() {

    // print dividers and set maximum widths for floats
    std::cout << std::string(40, '-') << '\n';
    std::cout << "\nWelcome to " << name_ << "!\n\n";
    std::cout << std::string(40, '-') << '\n';
    std::cout << std::setw(5) << "NUM" << std::setw(14) << "NAME"
              << std::setw(10) << "PRICE" << std::setw(10) << "STOCK\n";
    std::cout << std::string(40, '-') << '\n';

    // loop through all Item objects
    for (int i = 0; i < num_cols_; i++) {

        for (int j = 0; j < num_rows_; j++) {

            std::cout << std::setw(3) << (char)(i + col_min_offset_) << j + 1;

            auto item = inventory_[i][j];

            if (item) {
                std::cout << std::setw(15) << item->get_name() << std::setw(6)
                          << " $" << item->get_price() << std::setw(9)
                          << item->get_count();
            }
            std::cout << std::endl;
        }
    }
}

/*
 * Add money to the balance
 *
 * Params:
 *  amount <float>: amount to increase balance by
 *
 * Returns:
 *  None
 *
 */
void VendingMachine::add_money(float amount) {
    balance_ += amount;
    std::cout << "Balance: $" << balance_ << '\n';
}

/*
 * Returns name of the Item at `col` and `row`
 *
 * Params:
 *  col <int>: column number of Item object
 *  row <int>: row number of Item object
 *
 * Returns:
 *  picked_item->name_ <std::string>: Item object if located by `col` and `row`
 *
 */
std::string VendingMachine::get_item_name(int col, int row) {

    // locate item by `row` and `col`
    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_name() : nullptr;
}

/*
 * Returns price of the Item at `col` and `row`
 *
 * Params:
 *  col <int>: column number of Item object
 *  row <int>: row number of Item object
 *
 * Returns:
 *  picked_item->price_ <float>: price of Item object if located by `col` and
 *                              `row`
 *
 */
float VendingMachine::get_item_price(int col, int row) {

    // locate item by `row` and `col`
    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_price() : -1.0;
}

/*
 * Returns quantity of the Item at `col` and `row`
 *
 * Params:
 *  col <int>: column number of Item object
 *  row <int>: row number of Item object
 *
 * Returns:
 *  picked_item->count_ <float>: quantity of Item object if located by `col` and
 *                              `row`
 *
 */
int VendingMachine::get_item_count(int col, int row) {

    // locate item by `row` and `col`
    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_count() : -1;
}

/*
 * Locates Item at `col` and `row` and adjusts the balance of the object and
 * quantity of the Item
 *
 * Params:
 *  col <int>: column number of Item object
 *  row <int>: row number of Item object
 *
 * Returns:
 *  picked_item->count_ <float>: quantity of Item object if located by `col` and
 *                              `row`
 *
 */
bool VendingMachine::pick_item(int col, int row) {

    auto picked_item = locate_item(col, row);

    // if Item is located and the price is less than the balance inserted
    if (picked_item && picked_item->get_price() <= balance_) {

        // if the quantity of the Item is greater than 0
        if (picked_item->get_count()) {

            picked_item->dec_count();
            std::cout << "Dispensing 1 " << picked_item->get_name() << '\n';
            std::cout << "Returning change: $"
                      << balance_ - picked_item->get_price() << '\n';
            balance_ = 0;
            return true;

            // Item has 0 count
        } else {
            std::cout << picked_item->get_name() << " is out of stock!\n";
        }

        // balance is insufficient
    } else {
        std::cout << "Not enough credit for " << picked_item->get_name()
                  << " ($" << picked_item->get_price() << ")!\n";
    }

    std::cout << "Returning change: $" << picked_item->get_price() << '\n';
    return false;
}

/*
 * Locates Item at `col` and `row`
 *
 * Params:
 *  col <int>: column number of Item object
 *  row <int>: row number of Item object
 *
 * Returns:
 *  picked_item <Item*>: Item object if located by `col` and `row`
 *
 */
Item* VendingMachine::locate_item(int col, int row) {

    // if the column and row numbers are within bounds
    if (col >= col_min_offset_ && col < col_max_offset_ && row > 0 &&
        row <= num_rows_) {
        return inventory_[col - col_min_offset_][row - 1];
    }

    return nullptr;
}
