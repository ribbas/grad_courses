#include "vendingmachine.hpp"

#include <iostream>

int main() {

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

    machine->display_menu();

    machine->add_money(10.0);
    std::cout << machine->get_item_name('A', 2) << '\n';
    std::cout << machine->get_item_price('A', 2) << '\n';
    machine->pick_item('A', 2);

    machine->add_money(0);
    machine->add_money(0.25);
    machine->add_money(100);
    machine->pick_item('C', 4);
    machine->pick_item('A', 2);
    machine->pick_item('C', 2);

    machine->display_menu();

    delete machine;
    machine = nullptr;
}
