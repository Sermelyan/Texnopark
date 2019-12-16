/*
Copyright 2019 Сергей Меликян АПО-12
*/

#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

#include "ListGraph.hpp"

void BFS(const ListGraph &graph, unsigned int vertex, std::vector<int> &r,
         std::vector<int> &pi) {
    r.assign(graph.VerticesCount(), INT_MAX);
    pi.assign(graph.VerticesCount(), -1);
    std::queue<unsigned int> qu;
    qu.push(vertex);
    r[vertex] = 0;

    while (!qu.empty()) {
        unsigned int current = qu.front();
        qu.pop();
        for (const auto &v : graph.GetVertices(current)) {
            if (r[v] > r[current] + 1) {
                r[v] = r[current] + 1;
                pi[v] = current;
                qu.push(v);
            }
        }
    }
}

int FindShortestWaysCount(const ListGraph &graph, unsigned int vStart,
                          unsigned int vFinish) {
    std::vector<int> r, pi;
    BFS(graph, vStart, r, pi);
    int wCount;
    if (pi[vFinish]) {
        wCount = 1;
    } else {
        return -1;
    }
    for (auto &v = pi[vFinish]; v != vStart; v = pi[v]) {
        for (const auto &w : graph.GetVertices(v)) {
            if (w != pi[v] && r[w] <= r[v])
                wCount++;
        }
    }
    return wCount;
}

void run(std::istream &input, std::ostream &output) {
    unsigned int v = 0, n = 0;
    input >> v >> n;
    assert(v > 0 && v <= 50000);
    assert(n > 0 && n <= 200000);

    ListGraph graph(v);

    for (size_t i = 0; i < n; i++) {
        unsigned int v1, v2;
        input >> v1 >> v2;
        graph.AddEdge(v1, v2);
    }

    unsigned int Start, Finish;
    input >> Start >> Finish;
    assert(Start > 0 && Start < v);
    assert(Finish > 0 && Finish < v);
    output << FindShortestWaysCount(graph, Start, Finish);
}

void test() {
    {
        std::stringstream input, output;
        input << "4\n" << "5\n" << "0 1\n" << "0 2\n" <<"1 2\n" << "1 3\n" << "2 3\n" << "0 3";
        run(input, output);
        assert(output.str() == "2");
    }
}

int main(int argc, char **argv) {
    if (argc >= 2) {
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
