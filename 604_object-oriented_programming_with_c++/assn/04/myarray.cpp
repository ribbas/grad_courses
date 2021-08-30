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

    std::cout << "Creating MyArray object existingObj with size: 3\n";
    MyArray existingObj(3);

    std::cout << "Assigning existingObj value at(0)=50\n";
    existingObj.assign(0, 50);
    std::cout << "Assigning existingObj value at(1)=40\n";
    existingObj.assign(1, 40);
    std::cout << "Assigning existingObj value at(2)=99999\n";
    existingObj.assign(2, 99999);

    std::cout << "Size of existingObj array: " << existingObj.get_size()
              << '\n';
    std::cout << "Checking existingObj value at(0)=" << existingObj.at(0)
              << '\n';
    std::cout << "Checking existingObj value at(1)=" << existingObj.at(1)
              << '\n';
    std::cout << "Checking existingObj value at(2)=" << existingObj.at(2)
              << '\n';

    std::cout << "\nCopying existingObj to another MyArray object newObj\n";
    MyArray newObj = existingObj;

    std::cout << "Assigning newObj value at(1)=40\n";
    newObj.assign(1, -42);

    std::cout << "Size of existingObj array: " << existingObj.get_size()
              << '\n';
    std::cout << "Checking existingObj value at(1)=" << existingObj.at(1)
              << '\n';

    std::cout << "Size of existingObj array: " << newObj.get_size() << '\n';
    std::cout << "Checking existingObj value at(1)=" << newObj.at(1) << '\n';
}
