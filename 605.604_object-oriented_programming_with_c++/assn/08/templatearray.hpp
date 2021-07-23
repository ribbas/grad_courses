#ifndef TEMPLATEARRAY_HPP
#define TEMPLATEARRAY_HPP

// function template
#include <iostream>

template <class T> class TemplateArray {
private:
    T* data_;
    int size_;

public:
    int size();

    TemplateArray(int size = 0);

    ~TemplateArray();

    T& operator[](int index);
};

#endif