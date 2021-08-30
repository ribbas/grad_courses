/*
 * ui.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the implementation for a simple user interface class for
 * the Mini-project 1.
 *
 */

#include "ui.hpp"

#include <iomanip>
#include <iostream>

/*
 * Instantiates a VendingMachine and Wallet objects.
 *
 * Params:
 *  machine_name <std::string>: name of VendingMachine object
 *  cols <int>: number of columns in the VendingMachine object
 *  rows <int>: number of rows in the VendingMachine object
 *  max_amount <int>: maximum amount for the Wallet object balance
 *
 */
Proj1UI::Proj1UI(std::string machine_name, int cols, int rows, int max_amount)
    : cols_(cols), rows_(rows), machine_name_(machine_name),
      wallet_(new Wallet(max_amount)),
      vendingmachine_(new VendingMachine(machine_name, cols, rows)) {}

/*
 * Destructor
 *
 */
Proj1UI::~Proj1UI() {

    // free up dynamically allocated variables
    delete wallet_;
    wallet_ = nullptr;

    delete vendingmachine_;
    vendingmachine_ = nullptr;
}

/*
 * Initializes a VendingMachine object by prefilling it with item names,
 * prices, and quantities. The item names are provided by a prefilled array of
 * strings and the prices are generated randomly.
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
void Proj1UI::init_vending_machine() {

    // prefill the string array with item names
    std::string item_array[15] = {
        "Pepsu",      "Cookie Kola", "Mr. Pepper", "Crocorade", "8 Down",
        "Fake Water", "Real Water",  "Fantu",      "TMobile",   "Soda",
        "Magma",      "Hot sauce",   "Air",        "Moonshine", "Nothing"};

    int item_num = 0;
    // assign item name, price, quantity, column number and row number
    for (int i = 0; i < cols_; i++) {
        for (int j = 0; j < rows_; j++) {
            // item name is grabbed from `item_array`
            // item price is a float between 1.25 and 2.00 generated randomly
            // item quantity is an int between 1 and 10 generated randomly
            // item column number is a char between 'A' and (char)(`cols` + 65)
            // item row number is an integer between 1 and `rows`
            vendingmachine_->stock_item(item_array[item_num],
                                        1.0 + (rand() % 4 + 1) / 4.0,
                                        rand() % 10 + 1, (char)(i + 65), j + 1);
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
void Proj1UI::display_choice_menu() {
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
 * Initializes the member VendingMachine object by prefilling it with item
 * names, prices, and quantities. The item names are provided by a prefilled
 * array of strings and the prices are generated randomly.
 *
 * Params:
 *  choice <int>: user option. This function does NOT handle invalid data types
 *                 for user choice.
 *
 * Returns:
 *  None
 *
 */
void Proj1UI::parse_choice(int choice) {

    char col;
    int row;
    switch (choice) {
        // displays the vending machine menu
        case 1: {
            vendingmachine_->display_menu();
            break;
        }

        // displays the balance in the user's wallet
        case 2: {
            std::cout << "Wallet balance: $" << wallet_->check() << '\n';
            break;
        }

        // prompts user for item column and row to display its price
        case 3: {
            std::cout << "Enter item column: ";
            std::cin >> col;
            col = toupper(col);
            std::cout << "Enter item row: ";
            std::cin >> row;
            std::cout << "Item price: "
                      << vendingmachine_->get_item_price(col, row) << '\n';
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
            float item_price = vendingmachine_->get_item_price(col, row);
            if (wallet_->take_money_out(item_price)) {
                vendingmachine_->add_money(item_price);
            }

            // if the item is out of stock, put the money back in the wallet
            if (!vendingmachine_->pick_item(col, row)) {
                wallet_->put_money_in(item_price);
            }
            break;
        }

        // exit
        case 5: {
            std::cout << "Thank you for using " << machine_name_ << "!\n";
            return;
        }

        default: {
            std::cout << "Please select a valid option\n";
            break;
        }
    }
    display_choice_menu();
}

/*
 * Loops options continuously to user for prompts
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 */
void Proj1UI::loop() {

    // set the precision for floats to 2 fixed points
    std::cout << std::setprecision(2) << std::fixed;
    std::cout << "Wallet balance: $" << wallet_->check() << '\n';

    // initialize VendingMachine object with `cols` columns and `rows` rows
    init_vending_machine();

    // main loop to prompt for user choices
    int choice = 0;
    // parse_choice(choice);
    display_choice_menu();
    while (choice != 5) {
        std::cin >> choice;
        parse_choice(choice);
    }
}
