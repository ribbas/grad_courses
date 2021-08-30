/*
 * myarray.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 4 Assignment
 *
 * This file provides the declaration and implementation of the MyArray class.
 * The class simulates a simple interger array class with methods to assign and
 * retrieve values at specific indices
 *
 */

#include <iostream>

class MyArray {

public:
    /*
     * Default constructor - initializes the member variables
     *
     * Params:
     *  sz <int>: size to initialize the array with
     *
     */
    MyArray(int sz) : data(new int[sz]), size(sz) {
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }

    /*
     * Copy constructor
     *
     * Params:
     *  other <MyArray&>: reference to the original object
     *
     */
    MyArray(const MyArray& other) : MyArray(other.size) {}

    /*
     * Destructor - frees up dynamically allocated attributes and resets all
     * variables
     *
     */
    ~MyArray() {
        if (data) {
            delete[] data;
            data = nullptr;
            size = 0;
        }
    }

    /* --------------- METHODS --------------- */

    /*
     * Assign value at specific index
     *
     * Params:
     *  index <int>: index at which to overwrite with new value
     *  value <int>: new value
     *
     */
    void assign(const int index, const int value) {
        if (index > -1 && index < size) {
            data[index] = value;
        } else {
            std::cout << "Index is out of range\n";
        }
    };

    /*
     * Return value at specific index
     *
     * Params:
     *  index <int>: index of array
     *
     * Returns:
     *  <int>: value at specified index
     *
     */
    int at(int index) {
        if (index > -1 && index < size) {
            return data[index];

        } else {
            std::cout << "Index is out of range\n";
            return 0;
        }
    }

    /*
     * Overwrite all values of array with zero
     *
     * Params:
     *  None
     *
     */
    void clear() {
        for (int i = 0; i < size; i++) {
            data[i] = 0;
        }
    }

    /*
     * Return the size of the array
     *
     * Params:
     *  None
     *
     * Returns:
     *  <int*>: the size of the array
     *
     */
    int get_size() {
        return size;
    }

private:
    /* --------------- MEMBER ATTRIBUTES --------------- */
    int* data;
    int size;
};
