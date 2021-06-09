#include "vendingmachine.hpp"
#include <iomanip>
#include <iostream>
#include <random>
#include <stdlib.h>

VendingMachine::VendingMachine(std::string name, int num_cols, int num_rows)
    : _name(name), _num_cols(num_cols), _num_rows(num_rows), _balance(0.0), _row_min_offset(65) {

    _row_max_offset = _row_min_offset + _num_cols;
    for (int i = 0; i < _num_cols; i++) {
        std::vector<Item*> column;
        for (int j = 0; j < _num_rows; j++) {
            column.push_back(nullptr);
        }
        _inventory.push_back(column);
    }
}

VendingMachine::~VendingMachine() {

    for (int i = 0; i < _num_cols; i++) {
        _inventory[i].clear();
    }
    _inventory.clear();
}

void VendingMachine::stock_item(std::string name, float price, int num_item, int col, int row) {

    if (col >= _row_min_offset && col < _row_max_offset && row > 0 && row <= _num_rows) {
        auto item = new Item(name, price, num_item);
        _inventory[col - _row_min_offset][row - 1] = item;
    }
}

Item* VendingMachine::locate_item(int col, int row) {

    if (col >= _row_min_offset && col < _row_max_offset && row > 0 && row <= _num_rows) {
        return _inventory[col - _row_min_offset][row - 1];
    }
    return nullptr;
}

void VendingMachine::pick_item(int col, int row) {

    auto picked_item = locate_item(col, row);

    if (picked_item && picked_item->get_price() <= _balance) {

        if (picked_item->get_count()) {

            std::cout << "Dispensing 1 " << picked_item->get_name() << '\n';
            picked_item->dec_count();
            dec_credit(picked_item->get_price());

        } else {
            std::cout << picked_item->get_name() << " is out of stock!\n";
        }

    } else {
        std::cout << "Not enough credit for " << picked_item->get_name() << " ($"
                  << picked_item->get_price() << ")!\n";
    }
}

void VendingMachine::display_menu() {

    std::cout << std::string(40, '-') << '\n';
    std::cout << "\nWelcome to " << _name << "!\n\n";
    std::cout << std::string(40, '-') << '\n';
    std::cout << std::setw(5) << "NUM" << std::setw(14) << "NAME" << std::setw(10) << "PRICE"
              << std::setw(10) << "STOCK\n";
    std::cout << std::string(40, '-') << '\n';
    std::cout << std::setprecision(2) << std::fixed;
    for (int i = 0; i < _num_cols; i++) {

        for (int j = 0; j < _num_rows; j++) {

            std::cout << std::setw(3) << (char)(i + _row_min_offset) << j + 1;

            auto item = _inventory[i][j];

            if (item) {
                std::cout << std::setw(15) << item->get_name() << std::setw(6) << " $"
                          << item->get_price() << std::setw(9) << item->get_count();
            }
            std::cout << std::endl;
        }
    }
}

void VendingMachine::inc_credit(float amount) {
    _balance += amount;
}

void VendingMachine::dec_credit(float amount) {
    _balance -= amount;
}

float VendingMachine::check_balance() {
    return _balance;
}

std::string VendingMachine::check_name_of_item(int col, int row) {

    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_name() : nullptr;
}

float VendingMachine::check_price_of_item(int col, int row) {

    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_price() : -1;
}

int VendingMachine::check_num_of_item(int col, int row) {

    auto picked_item = locate_item(col, row);
    return picked_item ? picked_item->get_count() : -1;
}

int main() {

    srand(0);

    std::string item_array[15] = {"Pepsu",   "Cookie Kola", "Mr. Pepper", "Crocorade",
                                  "8 Down",  "Fake Water",  "Real Water", "Fantu",
                                  "TMobile", "Soda",        "Magma",      "Hot sauce",
                                  "Air",     "Moonshine",   "Nothing"};

    int cols = 3;
    int rows = 5;
    VendingMachine machine("JHU Vending Machine", cols, rows);

    int item_num = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            machine.stock_item(item_array[item_num], 1.0 + (rand() % 4 + 1) / 4.0, rand() % 10 + 1,
                               (char)(i + 65), j + 1);
            item_num++;
        }
    }

    machine.display_menu();

    machine.inc_credit(3.5);

    std::cout << machine.check_name_of_item('A', 2) << '\n';
    std::cout << machine.check_price_of_item('A', 2) << '\n';
    machine.pick_item('A', 2);
    machine.pick_item('A', 2);
    machine.pick_item('A', 2);
    machine.pick_item('C', 2);

    machine.display_menu();
}
