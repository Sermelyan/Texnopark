/*
Copyright 2019 Сергей Меликян АПО-12
 */

#ifndef _DYNAMICARRAY_HPP_
#define _DYNAMICARRAY_HPP_

#include <iostream>
#include <cassert>

template<class T>
class DynamicArray {

 public:
    DynamicArray() : size(4), pointer(0), buffer(nullptr) {
        buffer = new T[size];
    }

    explicit DynamicArray(size_t n) : size(n), pointer(0), buffer(nullptr) {
        buffer = new T[size];
    }

    ~DynamicArray() {
        delete[] buffer;
    }

    void pushBack(const T& element) {
        if (pointer == size)
            resize();
        buffer[pointer++] = element;
    }

    [[nodiscard]] size_t getSize() const {
        return pointer;
    }

    T operator[](size_t n)  const {
        assert(n < pointer);
        return buffer[n];
    }

    T& operator[](size_t n) {
        assert(n < pointer);
        return buffer[n];
    }

    DynamicArray(const DynamicArray&) = delete;
    DynamicArray(const DynamicArray&&) = delete;
    DynamicArray& operator=(const DynamicArray&) = delete;
    DynamicArray& operator=(const DynamicArray&&) = delete;

 private:
    size_t size;
    size_t pointer;
    T *buffer;
    void resize() {
        size *= 2;
        T* temp = new T[size];
        for (size_t i = 0; i < pointer; ++i) {
            temp[i] = buffer[i];
        }
        delete[] buffer;
        buffer = temp;
    }
};

#endif //   _DYNAMICARRAY_HPP_
