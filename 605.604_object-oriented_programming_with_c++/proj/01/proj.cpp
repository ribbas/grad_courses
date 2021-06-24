#include "vendingmachine.hpp"
#include "wallet.hpp"

#include <iostream>
#include <iomanip>

void init_vending_machine(VendingMachine* machine, int cols, int rows) {

    std::string item_array[15] = {"Pepsu",   "Cookie Kola", "Mr. Pepper", "Crocorade",
                                  "8 Down",  "Fake Water",  "Real Water", "Fantu",
                                  "TMobile", "Soda",        "Magma",      "Hot sauce",
                                  "Air",     "Moonshine",   "Nothing"};

    int item_num = 0;
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            machine->stock_item(item_array[item_num], 1.0 + (rand() % 4 + 1) / 4.0, rand() % 10 + 1,
                                (char)(i + 65), j + 1);
            item_num++;
        }
    }
}

void display_choice_menu() {
    std::cout << std::string(40, '-') << '\n';
    std::cout << "\nPick an option from the menu below: \n\n";
    std::cout << std::string(40, '-') << "\n\n";
    std::cout << "1: Display items of vending machine\n";
    std::cout << "2: Check wallet\n";
    std::cout << "3: Check price of item\n";
    std::cout << "4: Pick item\n";
    std::cout << "5: Exit\n";
    std::cout << std::string(40, '-') << "\n";
    std::cout << "Your choice: ";
}

void parse_choice(Wallet* wallet, VendingMachine* machine, int choice) {

    char col;
    int row;
    switch (choice) {
        case 1: {
            machine->display_menu();
            break;
        }

        case 2: {
            std::cout << "Wallet balance: $" << wallet->check() << '\n';
            break;
        }

        case 3: {
            std::cout << "Enter item column: ";
            std::cin >> col;
            col = toupper(col);
            std::cout << "Enter item row: ";
            std::cin >> row;
            std::cout << "Item price: " << machine->get_item_price(col, row) << '\n';
            break;
        }

        case 4: {
            std::cout << "Enter item column: ";
            std::cin >> col;
            col = toupper(col);
            std::cout << "Enter item row: ";
            std::cin >> row;

            float item_price = machine->get_item_price(col, row);
            if (wallet->take_money_out(item_price)) {
                machine->add_money(item_price);
            }

            if (!machine->pick_item(col, row)) {
                wallet->put_money_in(item_price);
            }
            break;
        }

        default: {
            std::cout << "Please select a valid option\n";
            break;
        }
    }
    display_choice_menu();
}
int main() {

    int seed = 0;
    srand(seed);
    std::cout << std::setprecision(2) << std::fixed;

    auto wallet = new Wallet(25);
    std::cout << "Wallet balance: $" << wallet->check() << '\n';

    int cols = 3;
    int rows = 5;
    auto machine = new VendingMachine("JHU Vending Machine", cols, rows);
    init_vending_machine(machine, cols, rows);

    int choice = 1;
    parse_choice(wallet, machine, choice);

    while (choice != 5) {
        std::cin >> choice;
        parse_choice(wallet, machine, choice);
    }

    delete wallet;
    wallet = nullptr;

    delete machine;
    machine = nullptr;
}
