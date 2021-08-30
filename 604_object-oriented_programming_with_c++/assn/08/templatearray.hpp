/*
 * templatearray.hpp
 * Sabbir Ahmed
 * 605.604: Object-Oriented Programming Using C++
 * Week 8 Assignment
 *
 * This file contains the declaration of the methods for the TemplateAarray
 * class.
 *
 */

#ifndef TEMPLATEARRAY_HPP
#define TEMPLATEARRAY_HPP

template <class T>
class TemplateArray {
private:
    int size_;
    T* data_;

public:
    /* --------------- CONSTRUCTORS/DESTRUCTORS --------------- */
    TemplateArray();

    TemplateArray(int = 0);

    TemplateArray(const TemplateArray&);

    ~TemplateArray();

    /* --------------- METHODS --------------- */
    int size();

    void resize(int);

    /* --------------- OVERLOADED OPERATORS --------------- */
    T& operator[](int);
};

#endif