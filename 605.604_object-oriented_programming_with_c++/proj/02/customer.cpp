#include "customer.hpp"

Customer::Customer() : is_senior_(false) {}

bool Customer::is_senior() {
    return is_senior_;
}

void Customer::make_senior() {
    is_senior_ = true;
}
