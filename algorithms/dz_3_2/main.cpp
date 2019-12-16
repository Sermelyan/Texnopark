/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include <cassert>
#include <climits>
#include <functional>
#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include "ListGraph.hpp"

void BFS(const ListGraph &graph, unsigned int vertex,
         std::vector<int> &r, std::vector<int> &pi) {
    r.assign(graph.VerticesCount(), INT_MAX);
    std::queue<unsigned int> qu;
    qu.push(vertex);
    r[vertex] = 0;
    pi[vertex] = -1;

    while (!qu.empty()) {
        unsigned int current = qu.front();
        qu.pop();
        for (const auto& v : graph.GetVertices(current))
            if (r[v] > r[current] + 1) {
                r[v] = r[current] + 1;
                pi[v] = current;
                qu.push(v);
            }
    }
}

template <class T> void run(std::istream &input, std::ostream &output) {
    size_t n = 0;
    input >> n;
    assert(n > 0 && n <= 1000000);
    Comporator<T> c;
    AvlTree<T, Comporator<T>> at(c);
    for (size_t i = 0; i < n; i++) {
        T data;
        input >> data;
        assert(data >= INT_MIN && data <= INT_MAX);
        if (c(data, static_cast<T>(0))) {
            at.Add(data);
        } else {
            at.Delete(-data);
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
