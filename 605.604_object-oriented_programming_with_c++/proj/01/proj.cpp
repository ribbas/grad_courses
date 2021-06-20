#include "vendingmachine.hpp"
#include "wallet.hpp"

#include <iostream>

VendingMachine* init_vending_machine() {

    srand(0);
    std::string item_array[15] = {"Pepsu",   "Cookie Kola", "Mr. Pepper", "Crocorade",
                                  "8 Down",  "Fake Water",  "Real Water", "Fantu",
                                  "TMobile", "Soda",        "Magma",      "Hot sauce",
                                  "Air",     "Moonshine",   "Nothing"};

    int cols = 3;
    int rows = 5;
    auto machine = new VendingMachine("JHU Vending Machine", cols, rows);

    int item_num = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            machine->stock_item(item_array[item_num], 1.0 + (rand() % 4 + 1) / 4.0, rand() % 10 + 1,
                                (char)(i + 65), j + 1);
            item_num++;
        }
    }

    return machine;
}

void make_transaction(Wallet* wallet, VendingMachine* machine, int col, int row) {

    std::cout << "Item name: " << machine->get_item_name(col, row) << '\n';
    float item_price = machine->get_item_price(col, row);
    std::cout << "Item price: " << item_price << '\n';
    if (wallet->take_money_out(item_price)) {
        machine->add_money(item_price);
    }
    machine->pick_item(col, row);

    std::cout << "Wallet balance: $" << wallet->check() << '\n';
}

int main() {

    auto wallet = new Wallet(25);
    std::cout << "Wallet balance: $" << wallet->check() << '\n';

    auto machine = init_vending_machine();

    machine->display_menu();
    make_transaction(wallet, machine, 'A', 2);
    machine->display_menu();

    delete wallet;
    wallet = nullptr;

    delete machine;
    machine = nullptr;
}
