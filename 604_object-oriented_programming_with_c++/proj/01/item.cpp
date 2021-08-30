/*
 * item.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Mini-project 1
 *
 * This file contains the implementation for the Item class.
 *
 */

#include "item.hpp"

/*
 * Parameterized constructor
 *
 * Initializes member attributes
 *
 * Params:
 *  name <std::string>: name of item
 *  price <float>: price of item
 *  count <int>: count of item
 *
 */
Item::Item(std::string name, float price, int count)
    : name_(name), price_(price), count_(count) {}

/*
 * Set name of item
 *
 * Params:
 *  name <std::string>: name for the item
 *
 * Returns:
 *  None
 *
 */
void Item::set_name(std::string name) {
    name_ = name;
}

/*
 * Set price of item
 *
 * Params:
 *  price <float>: price for the item
 *
 * Returns:
 *  None
 *
 */
void Item::set_price(float price) {
    price_ = price;
}

/*
 * Set quantity of item
 *
 * Params:
 *  count <float>: count for the item
 *
 * Returns:
 *  None
 *
 */
void Item::set_count(int count) {
    count_ = count;
}

/*
 * Decrement quantity of item
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
void Item::dec_count() {
    count_--;
}

/*
 * Return the name of item
 *
 * Params:
 *  None
 *
 * Returns:
 *  name_ <std::string>: name of the item
 *
 */
std::string Item::get_name() {
    return name_;
}

/*
 * Return the price of item
 *
 * Params:
 *  None
 *
 * Returns:
 *  price_ <float>: price of the item
 *
 */
float Item::get_price() {
    return price_;
}

/*
 * Return the quantity of item
 *
 * Params:
 *  None
 *
 * Returns:
 *  count_ <int>: count of the item
 *
 */
int Item::get_count() {
    return count_;
}
