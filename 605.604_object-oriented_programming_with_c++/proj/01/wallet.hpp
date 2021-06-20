#ifndef WALLET_HPP
#define WALLET_HPP

class Wallet {
public:
    Wallet(int);

    ~Wallet();

    void put_money_in(float);

    bool take_money_out(float);

    float check();

private:
    float balance_;
};

#endif
