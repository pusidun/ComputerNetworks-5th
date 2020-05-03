//
// Created by pusid on 2019/10/3.
//

#ifndef CODE_REPO_ARRAY_H
#define CODE_REPO_ARRAY_H

template <typename T>
class Array
{
protected:
    T* data;
    size_t length;
    size_t base;

public:
    Array();
    Array(unsigned int, unsigned int = 0);
    ~Array();

    Array(const Array&);
    Array& operator=(const Array&);

    const T& operator[](size_t int) const;
    T& operator[](size_t int);

    const T* Data() const;
    size_t Base() const;
    size_t Length() const;

    void SetBase(size_t);
    void SetLength(size_t);
};
#endif //CODE_REPO_ARRAY_H
