/*
Copyright 2019 Сергей Меликян АПО-12
3_1. Реализовать очередь с динамическим зацикленным буфером.
Требования: Очередь должна быть реализована в виде класса.
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include <sstream>

template <typename T>
inline bool isLess(const T& l, const T& r) {
    return l > r;
}

template <typename T>
inline size_t get_pivot(T* a, size_t n, bool compare(const T& l, const T& r)) {
    size_t end = n - 1, mid = (n - 1) / 2;
    if (compare(a[end], a[0])) {
        if (compare(a[end], a[mid])) {
            return (compare(a[mid], a[0]) ? mid : 0);
        } else {
            return end;
        }
    } else {
        if (compare(a[0], a[mid])) {
            return (compare(a[mid], a[end]) ? mid : end);
        } else {
            return 0;
        }
    }
}

template <typename T>
size_t partition(T* a, size_t n, bool compare(const T& l, const T& r)) {
    if (n <= 1) {
        return 0;
    }
    size_t med = get_pivot(a, n, compare);
    std::swap(a[n - 1], a[med]);
    int i = 0, j = 0;
    while (j < n - 1) {
        for (; compare(a[j], a[n - 1]); j++) {}
        if (j < n - 1) {
            std::swap(a[i++], a[j++]);
        }
    }
    std::swap(a[i], a[n - 1]);
    return i;
}

template <typename T>
T findElement(T *array, size_t n, size_t k,
              bool compare(const T& l, const T& r)) {
    T* a = array;
    size_t k_t = k;
    size_t i = 0, limit = n;
    while (i < limit / 4) {
        size_t p = partition(a, n, compare);
        if (p == k_t) {
            break;
        } else if (k_t < p) {
            n = p + 1;
        } else {
            a = &a[p + 1];
            n = n - (p + 1);
            k_t = k_t - (p + 1);
        }
        i++;
    }
    return array[k];
}

template <typename T>
void run(std::istream& input, std::ostream& output) {
    std::size_t n = 0, k = 0;
    const size_t max_int = 1000000000;
    input >> n >> k;
    assert(n > 0 && n <= max_int);
    assert(k >= 0 && k < max_int);
    auto array = new T[n];
    for (std::size_t i = 0; i < n; i++) {
        unsigned int temp;
        input >> temp;
        assert(temp >= 0 && temp < max_int);
        array[i] = temp;
    }
    output << findElement(array, n, k, isLess);
    delete[] array;
}

void test() {
    // 1-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 4 1 2 3 4 5 6 7 8 9 10";
        run<size_t >(input, output);
        assert(output.str() == "5");
    }
    //  2-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 0 3 6 5 7 2 9 8 10 4 1";
        run<size_t >(input, output);
        assert(output.str() == "1");
    }
    //  3-й тест из условия
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 9 0 0 0 0 0 0 0 0 0 1";
        run<size_t >(input, output);
        assert(output.str() == "1");
    }
    //  4-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 5 28 4 12 105 6 64 0 54 14 99";
        run<size_t >(input, output);
        assert(output.str() == "28");
    }
    //  5-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 9 1 0 0 0 0 0 0 0 0 0";
        run<size_t >(input, output);
        assert(output.str() == "1");
    }
    //  6-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "10 5 10 10 10 10 10 10 10 10 10 10";
        run<size_t >(input, output);
        assert(output.str() == "10");
    }
    //  7-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "100 61 ";
        for (size_t i = 0; i < 100; i++) {
            input << i << " ";
        }
        run<size_t >(input, output);
        assert(output.str() == "61");
    }
    //  7-й тест
    {
        std::stringstream input;
        std::stringstream output;
        input << "10000 999 ";
        for (int i = 9999; i >= 0; i--) {
            input << i << " ";
        }
        run<size_t >(input, output);
        assert(output.str() == "999");
    }
}

int main(int argc, char** argv) {
    if (argc >=  2) {
        std::string s(argv[1]);
        if (s == "test") {
            test();
            return 0;
        }
    }
    run<size_t>(std::cin, std::cout);
    std::cout << std::endl;
    return 0;
}
