/*
 * 02.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Assignment 1
 *
 * This file implements two versions of a method that swaps two integer values if the second
 * value is smaller than the first. The first version accepts the parameters as pointers and
 * the second accepts them as references.
 *
 */
#include <iostream>  // for displaying output to stdout

/*
 * Swaps two integer values passed as pointers
 */
void swap_ptr(int* a, int* b) {

    if (*a > *b) {
        int temp = *a;
        *a = *b;
        *b = temp;
    }

}

/*
 * Swaps two integer values passed as references
 */
void swap_ref(int& a, int& b) {

    if (a > b) {
        int temp = a;
        a = b;
        b = temp;
    }

}

int main() {

    int a = 10;
    int b = 5;

    std::cout << "Swapping as pointers:\n";
    std::cout << "Before: (a=" << a << ", b=" << b << ")\n";
    swap_ptr(&a, &b);
    std::cout << "After:  (a=" << a << ", b=" << b << ")\n";

    a = 20;
    b = 10;

    std::cout << "\nSwapping as references:\n";
    std::cout << "Before: (a=" << a << ", b=" << b << ")\n";
    swap_ptr(&a, &b);
    std::cout << "After:  (a=" << a << ", b=" << b << ")\n";

    return 0;

}
