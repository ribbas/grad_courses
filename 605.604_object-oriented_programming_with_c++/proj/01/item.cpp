#include "item.hpp"

Item::Item() : _name(""), _price(0.0), _count(0) {}

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

void Item::inc_count() {
    _count += 1;
}

void Item::dec_count() {
    _count -= 1;
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
