/*Copyright 2019 Сергей Меликян АПО-12
Даны два строго возрастающих массива целых чисел A[0..n) и B[0..m) и число k.
Найти количество таких пар индексов (i, j), что A[i] + B[j] = k.
n, m ≤ 100000.
Указание. Обходите массив B от конца к началу.
Требования:  Время работы O(n + m).*/

#include <iostream>
#include <cassert>
#include<sstream>

size_t findPairsSum(const int* a, const int* b,
                                size_t aSize, size_t bSize, int k) {
    size_t  sum = 0;
    for (size_t i = aSize - 1, j = 0; i > 0 || j < bSize ; ) {
        if (a[i] + b[j] == k) {
            sum++;
            if (i > 0)
                i--;
            if (j < bSize)
                j++;
        } else if (a[i] + b[j] > k) {
            if (i > 0)
                i--;
            else if (j < bSize)
                j++;
        } else if (a[i] + b[j] < k) {
            if (j < bSize)
                j++;
            else if (i > 0)
                i--;
            else
                break;
        }
    }
    return sum;
}

size_t  getArray(std::istream& input, int** array) {
    size_t size = 0;
    input >> size;
    if (size > 100000) {
        return 0;
    }
    *array = new int[size];
    for (size_t i = 0; i < size; i++) {
        input >> (*array)[i];
    }
    return size;
}

void run(std::istream& input, std::ostream& output) {
    int *arr1 = nullptr, *arr2 = nullptr;
    size_t  size1 = getArray(input, &arr1);
    assert(size1 != 0);
    size_t  size2 = getArray(input, &arr2);
    assert(size2 != 0);
    int k = 0;
    input >> k;
    output << findPairsSum(arr1, arr2, size1, size2, k);
    delete[] arr1;
    delete[] arr2;
}

void test() {
    // Тест 1 из задания
    {
        std::stringstream input;
        std::stringstream output;
        input << "4" << std::endl;
        input  <<"-5 0 3 18" << std::endl;
        input << "5" << std::endl;
        input  <<"-10 -2 4 7 12" << std::endl;
        input  <<"7" << std::endl;
        run(input, output);
        assert(output.str() == "3");
    }
    // Тетст 2 перевёрнутый первый
    {
        std::stringstream input;
        std::stringstream output;
        input << "5" << std::endl;
        input  <<"-10 -2 4 7 12" << std::endl;
        input << "4" << std::endl;
        input  <<"-5 0 3 18" << std::endl;
        input  <<"7" << std::endl;
        run(input, output);
        assert(output.str() == "3");
    }
    // Тест 3
    {
        std::stringstream input;
        std::stringstream output;
        input << "10" << std::endl;
        input  <<"-20 -10 -7 -6 -5 0 3 18 20 25" << std::endl;
        input << "10" << std::endl;
        input  <<"-30 -18 -10 -8 0 2 4 7 10 12" << std::endl;
        input  <<"0" << std::endl;
        run(input, output);
        assert(output.str() == "4");
    }
    // Тест 4 реврес 3
    {
        std::stringstream input;
        std::stringstream output;
        input << "10" << std::endl;
        input  <<"-30 -18 -10 -8 0 2 4 7 10 12" << std::endl;
        input << "10" << std::endl;
        input  <<"-20 -10 -7 -6 -5 0 3 18 20 25" << std::endl;
        input  <<"0" << std::endl;
        run(input, output);
        assert(output.str() == "4");
    }
    // Тест 5
    {
        std::stringstream input;
        std::stringstream output;
        input << "10" << std::endl;
        input  <<"-20 -10 -7 -6 -5 0 3 7 20 25" << std::endl;
        input << "10" << std::endl;
        input  <<"-30 -23 -10 -8 0 2 4 7 10 12" << std::endl;
        input  <<"-3"<< std::endl;
        run(input, output);
        assert(output.str() == "5");
    }
    // Тест 6 реверс 5
    {
        std::stringstream input;
        std::stringstream output;
        input << "10" << std::endl;
        input  <<"-30 -23 -10 -8 0 2 4 7 10 12" << std::endl;
        input << "10" << std::endl;
        input  <<"-20 -10 -7 -6 -5 0 3 7 20 25" << std::endl;
        input  <<"-3"<< std::endl;
        run(input, output);
        assert(output.str() == "5");
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
    run(std::cin, std::cout);
    std::cout << std::endl;
    return 0;
}
