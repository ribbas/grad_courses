/*
 * myarray.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 4 Assignment
 *
 * Driver file for the MyArray class
 *
 */

#include "myarray.hpp"

int main() {
    MyArray existingObj(3);

    existingObj.assign(0, 50);
    existingObj.assign(1, 40);
    existingObj.assign(2, 60);
    std::cout << existingObj.get_size() << '\n';
    std::cout << existingObj.at(0) << '\n';
    std::cout << existingObj.at(1) << '\n';
    std::cout << existingObj.at(2) << '\n';

    MyArray newObj = existingObj;
    newObj.assign(2, 60000);
    std::cout << existingObj.get_size() << '\n';
    std::cout << existingObj.at(2) << '\n';
    std::cout << newObj.get_size() << '\n';
    std::cout << newObj.at(2) << '\n';
}
