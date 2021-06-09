#ifndef VENDINGMACHINE_HPP
#define VENDINGMACHINE_HPP

#include "item.hpp"

#include <vector>

class VendingMachine {

public:
    VendingMachine(std::string, int, int);

    ~VendingMachine();

    void stock_item(std::string, float, int, int, int);

    void display_menu();

    void add_money(float);

    std::string get_item_name(int, int);

    float get_item_price(int, int);

    int get_item_count(int, int);

    void pick_item(int, int);

private:
    Item* locate_item(int, int);

    std::vector<std::vector<Item*>> _inventory;
    std::string _name;
    float _balance;
    int _num_rows;
    int _num_cols;
    int _row_min_offset;
    int _row_max_offset;
};

#endif
