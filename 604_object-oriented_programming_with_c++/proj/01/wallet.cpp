/*
 * wallet.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the implementation for the Wallet class.
 *
 */

#include "wallet.hpp"

#include <iostream>

/*
 * Parameterized constructor
 *
 * Initializes member attributes
 *
 * Params:
 *  max_amount <int>: maximum amount for the amount
 *
 */
Wallet::Wallet(int max_amount) {

    balance_ = (rand() % max_amount) + (rand() % 10 + 1) / 10.0;
}

/*
 * Return the balance
 *
 * Params:
 *  None
 *
 * Returns:
 *  balance_ <float>
 *
 */
float Wallet::check() {

    return balance_;
}

/*
 * Increase the balance by `amount`
 *
 * Params:
 *  amount <float>: amount of money to increase balance by
 *
 * Returns:
 *  None
 *
 */
void Wallet::put_money_in(float amount) {
    balance_ += amount;
};

/*
 * Decrease the balance by `amount`
 *
 * Params:
 *  amount <float>: amount of money to decrease balance by
 *
 * Returns:
 *  <bool>: if true, balance was decreased. If false, there is insufficient
 *          balance.
 *
 */
bool Wallet::take_money_out(float amount) {

    if (balance_ >= amount) {
        balance_ -= amount;
        return true;
    }
    return false;
}
