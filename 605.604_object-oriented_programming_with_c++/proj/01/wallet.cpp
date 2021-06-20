#include "wallet.hpp"

#include <iostream>

Wallet::Wallet(int max_amount) {

    srand(0);
    balance_ = (rand() % max_amount) + (rand() % 10 + 1) / 10.0;
}

Wallet::~Wallet() {}

float Wallet::check() {

    return balance_;
}

void Wallet::put_money_in(float amount) {
    balance_ += amount;
};

bool Wallet::take_money_out(float amount) {

    if (balance_ >= amount) {
        balance_ -= amount;
        return true;
    }
    return false;
}
