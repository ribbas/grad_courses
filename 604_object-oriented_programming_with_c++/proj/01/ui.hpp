/*
 * ui.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the function declarations for a simple user interface
 * class for the Mini-project 1.
 *
 */

#include "vendingmachine.hpp"
#include "wallet.hpp"

class Proj1UI {
public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    Proj1UI(std::string, int, int, int);

    /* ------------------------ DESTRUCTORS ------------------------ */
    ~Proj1UI();

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void init_vending_machine();
    void display_choice_menu();
    void parse_choice(int);
    void loop();

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    int cols_, rows_;
    std::string machine_name_;
    Wallet* wallet_;
    VendingMachine* vendingmachine_;
};
