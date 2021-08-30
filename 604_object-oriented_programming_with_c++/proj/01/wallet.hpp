/*
 * wallet.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the function declarations for the Wallet class.
 *
 */

#ifndef WALLET_HPP
#define WALLET_HPP

class Wallet {
public:
    /* ------------------------ CONSTRUCTORS ------------------------ */
    Wallet(int);

    /* ------------------------ PUBLIC METHODS ------------------------ */
    void put_money_in(float);

    bool take_money_out(float);

    float check();

private:
    /* ------------------------ PRIVATE ATTRIBUTES ------------------------ */
    float balance_;
};

#endif
