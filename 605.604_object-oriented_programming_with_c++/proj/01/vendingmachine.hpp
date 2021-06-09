#ifndef VENDINGMACHINE_HPP
#define VENDINGMACHINE_HPP

#include "item.hpp"
#include <string>
#include <vector>

class VendingMachine {

public:
    VendingMachine(std::string, int, int);

    ~VendingMachine();

    void stock_item(std::string, float, int, int, int);

    void inc_credit(float);

    void dec_credit(float);

    float check_balance();

    std::string check_name_of_item(int, int);

    float check_price_of_item(int, int);

    int check_num_of_item(int, int);

    void pick_item(int, int);

    void display_menu();

private:
    Item* locate_item(int, int);
    std::vector<std::vector<Item*>> _inventory;
    std::string _name;
    int _num_rows;
    int _num_cols;

    float _balance;

    int _row_min_offset;
    int _row_max_offset;
};

#endif
