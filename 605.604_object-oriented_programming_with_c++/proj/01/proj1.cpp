/*
 * proj1.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the driver utilities for the Mini-project 1.
 *
 */

#include "vendingmachine.hpp"
#include "wallet.hpp"

#include <iomanip>
#include <iostream>

/*
 * Initializes a VendingMachine object by prefilling it with item names,
 * prices, and quantities. The item names are provided by a prefilled array of
 * strings and the prices are generated randomly.
 *
 * Params:
 *  machine <VendingMachine*>: pointer to the VendingMachine object
 *  cols: <int>: number of columns in the VendingMachine object
 *  rows: <int>: number of rows in the VendingMachine object
 *
 * Returns:
 *  None
 *
 */
void init_vending_machine(VendingMachine* machine, int cols, int rows) {

    // prefill the string array with item names
    std::string item_array[15] = {
        "Pepsu",      "Cookie Kola", "Mr. Pepper", "Crocorade", "8 Down",
        "Fake Water", "Real Water",  "Fantu",      "TMobile",   "Soda",
        "Magma",      "Hot sauce",   "Air",        "Moonshine", "Nothing"};

    int item_num = 0;
    // assign item name, price, quantity, column number and row number
    for (int i = 0; i < cols; i++) {
        for (int j = 0; j < rows; j++) {
            // item name is grabbed from `item_array`
            // item price is a float between 1.25 and 2.00 generated randomly
            // item quantity is an int between 1 and 10 generated randomly
            // item column number is a char between 'A' and (char)(`cols` + 65)
            // item row number is an integer between 1 and `rows`
            machine->stock_item(item_array[item_num],
                                1.0 + (rand() % 4 + 1) / 4.0, rand() % 10 + 1,
                                (char)(i + 65), j + 1);
            item_num++;
        }
    }
}

/*
 * Prints a menu to stdout displaying user options
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
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

/*
 * Initializes a VendingMachine object by prefilling it with item names,
 * prices, and quantities. The item names are provided by a prefilled array of
 * strings and the prices are generated randomly.
 *
 * Params:
 *  wallet: <Wallet>: pointer to the Wallet object
 *  machine <VendingMachine*>: pointer to the VendingMachine object
 *  choice: <int>: user option
 *
 * Returns:
 *  None
 *
 */
void parse_choice(Wallet* wallet, VendingMachine* machine, int choice) {

    char col;
    int row;
    switch (choice) {
        // displays the vending machine menu
        case 1: {
            machine->display_menu();
            break;
        }

        // displays the balance in the user's wallet
        case 2: {
            std::cout << "Wallet balance: $" << wallet->check() << '\n';
            break;
        }

        // prompts user for item column and row to display its price
        case 3: {
            std::cout << "Enter item column: ";
            std::cin >> col;
            col = toupper(col);
            std::cout << "Enter item row: ";
            std::cin >> row;
            std::cout << "Item price: " << machine->get_item_price(col, row)
                      << '\n';
            break;
        }

        // prompts user for item column and row to dispense the item and make
        // the transaction
        case 4: {
            std::cout << "Enter item column: ";
            std::cin >> col;
            col = toupper(col);
            std::cout << "Enter item row: ";
            std::cin >> row;

            // take the price of the item out of the wallet
            float item_price = machine->get_item_price(col, row);
            if (wallet->take_money_out(item_price)) {
                machine->add_money(item_price);
            }

            // if the item is out of stock, put the money back in the wallet
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

/*
 * Main driver function of the project
 *
 */
int main() {

    // seed the RNG
    int seed = 0;
    srand(seed);
    // set the precision for floats to 2 fixed points
    std::cout << std::setprecision(2) << std::fixed;

    // initialize Wallet object with a maximum amount of $25
    auto wallet = new Wallet(25);
    std::cout << "Wallet balance: $" << wallet->check() << '\n';

    // initialize VendingMachine object with 3 columns and 5 rows
    int cols = 3;
    int rows = 5;
    auto machine = new VendingMachine("JHU Vending Machine", cols, rows);
    init_vending_machine(machine, cols, rows);

    // main loop to prompt for user choices
    int choice = 1;
    parse_choice(wallet, machine, choice);
    while (choice != 5) {
        std::cin >> choice;
        parse_choice(wallet, machine, choice);
    }

    // free up dynamically allocated variables
    delete wallet;
    wallet = nullptr;

    delete machine;
    machine = nullptr;

    return 0;
}
