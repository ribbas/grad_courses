#include "templatearray.hpp"
#include "date.hpp"

#include <string>

template class TemplateArray<int>;
template class TemplateArray<float>;
template class TemplateArray<std::string>;
template class TemplateArray<Date*>;

template <typename T> int TemplateArray<T>::size() {
    return size_;
}

template <class T> TemplateArray<T>::TemplateArray(int size) {
    size_ = size;
    data_ = new T[size_];
}

template <class T> TemplateArray<T>::~TemplateArray() {
    size_ = 0;
    delete[] data_;
    data_ = nullptr;
}

template <class T> T& TemplateArray<T>::operator[](int index) {
    if (index >= size_) {
        throw std::out_of_range("Index out of bounds");
    }
    return data_[index];
}
