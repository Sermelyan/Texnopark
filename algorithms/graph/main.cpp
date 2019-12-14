/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include <cassert>
#include <climits>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>

template <class T> void run(std::istream &input, std::ostream &output) {
    size_t n = 0;
    input >> n;
    assert(n > 0 && n <= 1000000);
    Comporator<T> c;
    AvlTree<T, Comporator<T>> at(c);
    for (size_t i = 0; i < n; i++) {
        T data;
        // unsigned pos;
        // input >> data >> pos;
        input >> data;
        assert(data >= INT_MIN && data <= INT_MAX);
        if (c(data, static_cast<T>(0))) {
            at.Add(data);
            // output << at.StatK(pos) << std::endl;
        } else {
            at.Delete(-data);
            // output << at.StatK(pos) << std::endl;
        }
    }
    std::vector<T> ord = at.InOrder();
    for (size_t i = 0; i < n - 1; i++) {
        output << ord[i] << " ";
    }
    output << ord[n - 1];
}

int main(int argc, char **argv) {
    if (argc >= 2) {
        std::string s(argv[1]);
        if (s == "test") {
            test();
            return 0;
        }
    }
    run<int>(std::cin, std::cout);
    return 0;
}
