#include "item.hpp"

Item::Item(std::string name, float price, int count) : name_(name), price_(price), count_(count) {}

void Item::set_name(std::string name) {
    name_ = name;
}

void Item::set_price(float price) {
    price_ = price;
}

void Item::set_count(int count) {
    count_ = count;
}

void Item::dec_count() {
    count_--;
}

std::string Item::get_name() {
    return name_;
}

float Item::get_price() {
    return price_;
}
int Item::get_count() {
    return count_;
}
