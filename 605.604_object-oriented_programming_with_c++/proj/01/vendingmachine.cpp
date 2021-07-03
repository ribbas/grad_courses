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

VendingMachine::VendingMachine(std::string name, int num_cols, int num_rows)
    : name_(name), num_cols_(num_cols), num_rows_(num_rows),
      row_min_offset_(65) {

    row_max_offset_ = row_min_offset_ + num_cols_;
    for (int i = 0; i < num_cols_; i++) {
        std::vector<Item*> column;
        for (int j = 0; j < num_rows_; j++) {
            column.push_back(nullptr);
        }
        inventory_.push_back(column);
    }
}

VendingMachine::~VendingMachine() {

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

void VendingMachine::stock_item(std::string name, float price, int num_item,
                                int col, int row) {

    if (col >= row_min_offset_ && col < row_max_offset_ && row > 0 &&
        row <= num_rows_) {
        auto item = new Item(name, price, num_item);
        inventory_[col - row_min_offset_][row - 1] = item;
    }
}

void VendingMachine::display_menu() {

    std::cout << std::string(40, '-') << '\n';
    std::cout << "\nWelcome to " << name_ << "!\n\n";
    std::cout << std::string(40, '-') << '\n';
    std::cout << std::setw(5) << "NUM" << std::setw(14) << "NAME"
              << std::setw(10) << "PRICE" << std::setw(10) << "STOCK\n";
    std::cout << std::string(40, '-') << '\n';
    for (int i = 0; i < num_cols_; i++) {

        for (int j = 0; j < num_rows_; j++) {

            std::cout << std::setw(3) << (char)(i + row_min_offset_) << j + 1;

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

void VendingMachine::add_money(float amount) {
    balance_ += amount;
    std::cout << "Balance: $" << balance_ << '\n';
}

std::string VendingMachine::get_item_name(int col, int row) {

    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_name() : nullptr;
}

float VendingMachine::get_item_price(int col, int row) {

    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_price() : -1.0;
}

int VendingMachine::get_item_count(int col, int row) {

    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_count() : -1;
}

bool VendingMachine::pick_item(int col, int row) {

    auto picked_item = locate_item(col, row);

    if (picked_item && picked_item->get_price() <= balance_) {

        if (picked_item->get_count()) {

            picked_item->dec_count();
            std::cout << "Dispensing 1 " << picked_item->get_name() << '\n';
            std::cout << "Returning change: $"
                      << balance_ - picked_item->get_price() << '\n';
            balance_ = 0;
            return true;

        } else {
            std::cout << picked_item->get_name() << " is out of stock!\n";
        }

    } else {
        std::cout << "Not enough credit for " << picked_item->get_name()
                  << " ($" << picked_item->get_price() << ")!\n";
    }

    std::cout << "Returning change: $" << picked_item->get_price() << '\n';
    return false;
}

Item* VendingMachine::locate_item(int col, int row) {

    if (col >= row_min_offset_ && col < row_max_offset_ && row > 0 &&
        row <= num_rows_) {
        return inventory_[col - row_min_offset_][row - 1];
    }
    return nullptr;
}
