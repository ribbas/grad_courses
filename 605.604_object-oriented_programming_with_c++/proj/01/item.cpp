#include "item.hpp"

Item::Item(std::string name, float price, int count) : _name(name), _price(price), _count(count) {}

void Item::set_name(std::string name) {
    _name = name;
}

void Item::set_price(float price) {
    _price = price;
}

void Item::set_count(int count) {
    _count = count;
}

void Item::dec_count() {
    _count--;
}

std::string Item::get_name() {
    return _name;
}

float Item::get_price() {
    return _price;
}
int Item::get_count() {
    return _count;
}
