/*
 * templatearray.cpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 8 Assignment
 *
 * This file contains the implementation of the methods for the TemplateAarray
 * class.
 *
 */

#include "templatearray.hpp"
#include "date.hpp"

// Explicitly instantiate the template class with data types specified in the
// project prompt
template class TemplateArray<int>;
template class TemplateArray<float>;
template class TemplateArray<std::string>;
template class TemplateArray<Date*>;

/*
 * Default constructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
template <class T>
TemplateArray<T>::TemplateArray() {
    size_ = 1;
    data_ = new T[size_];
}

/*
 * Parameterized constructor
 *
 * Params:
 *  size <int>: size to intialize the object array with
 *
 * Returns:
 *  None
 *
 */
template <class T>
TemplateArray<T>::TemplateArray(int size) : size_(size), data_(new T[size]) {}

/*
 * Copy constructor
 *
 * Params:
 *  other <TemplateArray&>: reference to original object
 *
 * Returns:
 *  None
 *
 */
template <class T>
TemplateArray<T>::TemplateArray(const TemplateArray& other)
    : TemplateArray(other.size_) {
    size_ = other.size_;
    for (int i = 0; i < other.size_; i++) {
        data_[i] = other.data_[i];
    }
}

/*
 * Destructor
 *
 * Params:
 *  None
 *
 * Returns:
 *  None
 *
 */
template <class T>
TemplateArray<T>::~TemplateArray() {
    size_ = 0;
    delete[] data_;
    data_ = nullptr;
}

/*
 * Return size of the array object.
 *
 * Params:
 *  None
 *
 * Returns:
 *  size_ <int>: size of the object array
 *
 */
template <typename T>
int TemplateArray<T>::size() {
    return size_;
}

/*
 * Resize the array object.
 *
 * Params:
 *  size <int>: new size of array object
 *
 * Returns:
 *  None
 *
 */
template <typename T>
void TemplateArray<T>::resize(int size) {
    delete[] data_;
    size_ = size;
    data_ = new T[size];
}

/*
 * Overloaded operator[] (subscript operator) for the class to assign or access
 * items at index. This behavior is consistent with a standard library array.
 *
 * Params:
 *  index <int>: subscript index
 *
 * Returns:
 *  data_[index] <T&>: value at index
 *
 */
template <class T>
T& TemplateArray<T>::operator[](int index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    return data_[index];
}
