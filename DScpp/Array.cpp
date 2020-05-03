//
// Created by pusid on 2019/10/3.
//

#include "Array.h"

template <typename T>
Array<T>::Array()
{
    base = 0;
    length = 0;
    data = nullptr;
}

template <typename T>
Array::Array(size_t n, size_t m = 0)
{
    base = n;
    length = m;
    data = new T[base + length];
}

template <typename T>
Array::~Array()
{
    if(data != nullptr)
        delete (data);
}

template <typename T>
Array::Array(const Array& rhs)
{
    base = rhs.base;
    length = rhs.length;

}