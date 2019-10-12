/*
Copyright 2019 Сергей Меликян АПО-12
Даны два массива неповторяющихся целых чисел,
упорядоченные по возрастанию.
A[0..n-1] и B[0..m-1]. n >> m. Найдите их пересечение.
Требования: Время работы: O(m * log k),
где k - позиция элемента B[m-1] в массиве A..
В процессе поиска очередного элемента B[i] в массиве A
пользуйтесь результатом поиска элемента B[i-1].
Внимание! В этой задаче для каждого B[i] сначала нужно определить
диапазон для бинарного поиска размером порядка k,
а потом уже в нем делать бинарный поиск.
*/

#include <iostream>
#include <sstream>
#include <cassert>
#include <ctime>

template<class T>
class Vector {

public:
    Vector() : size(4), pointer(0), buffer(nullptr) {
        buffer = new T[size];
    }

    explicit Vector(size_t n) : size(n), pointer(0), buffer(nullptr) {
        buffer = new T[size];
    }

    ~Vector() {
        delete[] buffer;
    }

    void pushBack(const T& element) {
        if (pointer == size)
            growUp();
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

    void resize(size_t newSize) {
        size = newSize;
        T* temp = new T[size];
        for (size_t i = 0; i < pointer; ++i) {
            temp[i] = buffer[i];
        }
        delete[] buffer;
        buffer = temp;
    }

    Vector(const Vector&) = delete;
    Vector(const Vector&&) = delete;
    Vector& operator=(const Vector&) = delete;
    Vector& operator=(const Vector&&) = delete;

private:
    size_t size;
    size_t pointer;
    T *buffer;
    void growUp() {
        size *= 2;
        T* temp = new T[size];
        for (size_t i = 0; i < pointer; ++i) {
            temp[i] = buffer[i];
        }
        delete[] buffer;
        buffer = temp;
    }
};


int binSearch(const Vector<int>& arr,
              size_t first, size_t right,
              int element) {
    size_t last = right;
    for (size_t mid = (first + last)/2;  first < last ; mid = (first + last)/2) {
        if (arr[mid] < element)
            first = mid +1;
        else
            last = mid;
    }
    return (first == right || arr[first] != element ) ? -1 : first;
}

size_t findRange(const Vector<int>& arr, size_t  left, int element) {
    if (arr[left] > element)
        return left;
    size_t i = 1;
    size_t size = arr.getSize();
    for (; left + i < size; i *= 2) {
        if (arr[left + i] > element)
            return left + i;
    }
    return  size;
}

void findIntersection(const Vector<int>& A,
                      const Vector<int>& B,
                      Vector<int>& result) {
    size_t  m = B.getSize();
    size_t left = 0;

    for (size_t i = 0; i < m; i++) {
        size_t right = findRange(A,left, B[i]);
        if (left < right) {
            int j = binSearch(A, left, right, B[i]);
            if (j != -1){
                result.pushBack(A[j]);
                left = j;
            }
        }
    }
}

void getArray(std::istream& input, Vector<int>& array, size_t  size) {
    for (size_t i = 0; i < size; i++) {
        int temp = 0;
        input >> temp;
        array.pushBack(temp);
    }
}

bool run(std::istream& input, std::ostream& output) {
    size_t sizeA, sizeB;
    input >> sizeA >> sizeB;
    if (sizeA <= sizeB)
        return false;
    assert(sizeA < 10000 || sizeB < 10000);
    Vector<int> A(sizeA);
    Vector<int> B(sizeB);
    Vector<int> intersection;
    getArray(input, A, sizeA);
    getArray(input, B, sizeB);
    findIntersection(A, B, intersection);
    size_t i = 0;
    size_t sizeI = intersection.getSize();
    if (sizeI > 0) {
        for (; i < sizeI - 1; i++) {
            output << intersection[i] << " ";
        }
        output << intersection[i] ;
    } else {
        output << "";
    }
    return true;
}

void test() {
    // Тест 1 из задания
    {
        std::stringstream input;
        std::stringstream output;
        input << "5" << std::endl;
        input << "3" << std::endl;
        input  <<"1 2 3 4 5" << std::endl;
        input  <<"1 3 5" << std::endl;
        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "1 3 5");
    }
    // Тест 2
    {
        std::stringstream input;
        std::stringstream output;
        input << "8" << std::endl;
        input << "5" << std::endl;
        input  <<"1 2 3 4 5 6 7 9" << std::endl;
        input  <<"1 3 4 5 9" << std::endl;
        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "1 3 4 5 9");
    }
    // Тест 3
    {
        std::stringstream input;
        std::stringstream output;
        input << "7" << std::endl;
        input << "6" << std::endl;
        input  <<"100 250 400 1000 1234 4444 5000" << std::endl;
        input  <<"1 3 4 5 7 1234" << std::endl;
        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "1234");
    }
    // Тест 4
    {
        std::stringstream input;
        std::stringstream output;
        input << "11" << std::endl;
        input << "8" << std::endl;
        input  <<"-6 -4 0 3 100 250 400 1000 1234 4444 5000" << std::endl;
        input  <<"-4 0 1 3 4 7 100 1234" << std::endl;
        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "-4 0 3 100 1234");
    }
    // Тест 4
    {
        std::stringstream input;
        std::stringstream output;
        input << "1000" << std::endl;
        input << "13" << std::endl;
        for (int i = 0; i < 999; i++) {
            input << i << " ";
        }
        input << 999 << std::endl;
        input << "-5  -4 0 27 131 157 243 666 781 871 945 999 1211" << std::endl;

        std::cout << input.str();

        auto start = clock();
        run(input, output);
        auto fin = (double)(clock() - start)/CLOCKS_PER_SEC;

        std::cout << (double)fin << std::endl;
        std::cout << output.str() << std::endl;
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
    if (run(std::cin, std::cout)){
        std::cout << std::endl;
        return 0;
    }
    return 1;
}
