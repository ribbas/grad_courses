/*
 * proj1.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the driver utilities for the Mini-project 1.
 *
 */

#include "ui.hpp"

#include <iostream>

/*
 * Main driver function of the project
 *
 */
int main() {

    // initialize VendingMachine object with 3 columns and 5 rows
    auto ui = new Proj1UI("JHU Vending Machine", 3, 5, 25);

    // seed the RNG
    int seed = 0;
    srand(seed);

    // begin loop
    ui->loop();

    // free up dynamically allocated variables
    delete ui;
    ui = nullptr;

    return 0;
}
