/*
 * 01.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Assignment 1
 *
 * This file displays the values and sizes of the constants in climits that represent
 * the maximum and minimum values of various in-built data types.
 *
 */
#include <climits>  // for importing the constants
#include <iostream>  // for displaying output to stdout

int main() {

    std::cout << "CHAR_BIT\nvalue: " << CHAR_BIT << ", size: "  << sizeof CHAR_BIT << "\n\n";
    std::cout << "CHAR_MAX\nvalue: " << CHAR_MAX << ", size: "  << sizeof CHAR_MAX << "\n\n";
    std::cout << "CHAR_MIN\nvalue: " << CHAR_MIN << ", size: "  << sizeof CHAR_MIN << "\n\n";
    std::cout << "SHRT_MAX\nvalue: " << SHRT_MAX << ", size: "  << sizeof SHRT_MAX << "\n\n";
    std::cout << "SHRT_MIN\nvalue: " << SHRT_MIN << ", size: "  << sizeof SHRT_MIN << "\n\n";
    std::cout << "USHRT_MAX\nvalue: " << USHRT_MAX << ", size: "  << sizeof USHRT_MAX << "\n\n";
    std::cout << "INT_MAX\nvalue: " << INT_MAX << ", size: "  << sizeof INT_MAX << "\n\n";
    std::cout << "INT_MIN\nvalue: " << INT_MIN << ", size: "  << sizeof INT_MIN << "\n\n";
    std::cout << "UINT_MAX\nvalue: " << UINT_MAX << ", size: "  << sizeof UINT_MAX << "\n\n";
    std::cout << "LONG_MAX\nvalue: " << LONG_MAX << ", size: "  << sizeof LONG_MAX << "\n\n";
    std::cout << "LONG_MIN\nvalue: " << LONG_MIN << ", size: "  << sizeof LONG_MIN << "\n\n";
    std::cout << "ULONG_MAX\nvalue: " << ULONG_MAX << ", size: "  << sizeof ULONG_MAX << "\n\n";
    std::cout << "LLONG_MAX\nvalue: " << LLONG_MAX << ", size: "  << sizeof LLONG_MAX << "\n\n";
    std::cout << "LLONG_MIN\nvalue: " << LLONG_MIN << ", size: "  << sizeof LLONG_MIN << "\n\n";
    std::cout << "ULLONG_MAX\nvalue: " << ULLONG_MAX << ", size: "  << sizeof ULLONG_MAX << "\n\n";

    return 0;

}
