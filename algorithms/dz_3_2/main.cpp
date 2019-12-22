/*
Copyright 2019 Сергей Меликян АПО-12
Задание 2. Модуль 3.
*/

#include <cassert>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

class ListGraph {
public:
    explicit ListGraph(unsigned int count);
    ~ListGraph();

    void AddEdge(unsigned int v1, unsigned int v2);

    [[nodiscard]] unsigned int VerticesCount() const;

    [[nodiscard]] std::vector<unsigned int>
    GetVertices(unsigned int vertex) const;

private:
    std::vector<std::vector<unsigned int>> adjacencyLists;
};

ListGraph::ListGraph(unsigned int count) : adjacencyLists(count) {}

ListGraph::~ListGraph() = default;

void ListGraph::AddEdge(unsigned int v1, unsigned int v2) {
    assert(v1 >= 0 && v1 < adjacencyLists.size());
    assert(v1 >= 0 && v2 < adjacencyLists.size());
    adjacencyLists[v1].push_back(v2);
    adjacencyLists[v2].push_back(v1);
}

unsigned int ListGraph::VerticesCount() const { return adjacencyLists.size(); }

std::vector<unsigned int>
ListGraph::GetVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

int FindShortestWaysCount(const ListGraph &graph, unsigned int start, unsigned int finish) {
    std::vector<unsigned> ways(graph.VerticesCount(), 0);
    std::vector<unsigned> dist(graph.VerticesCount(), 0);
    std::queue<unsigned int> qu;

    qu.push(start);
    ways[start] = 1;

    while (!qu.empty()) {
        unsigned int current = qu.front();
        qu.pop();

        for (const auto &v : graph.GetVertices(current)) {
            if (ways[v] == 0) {
                qu.push(v);
                ways[v] = ways[current];
                dist[v] = dist[current] + 1;
            } else if (dist[v] == dist[current] + 1) {
                ways[v] += ways[current];
            }
        }
    }
    return ways[finish];
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
    assert(Start >= 0 && Start < v);
    assert(Finish >= 0 && Finish < v);
    output << FindShortestWaysCount(graph, Start, Finish);
}

void test() {
    {
        std::stringstream input, output;
        input << "7\n" << "9\n" << "0 1\n" << "0 6\n" <<"1 2\n" << "1 5\n" << "2 3\n" << "2 5 5 4 3 4 6 5 5 0";
        run(input, output);
        assert(output.str() == "2");
    }
    {
        std::stringstream input, output;
        input << "4\n" << "5\n" << "0 1\n" << "0 2\n" <<"1 2\n" << "1 3\n" << "2 3\n" << "0 3";
        run(input, output);
        assert(output.str() == "2");
    }
    {
        std::stringstream input, output;
        input << "13 18 0 1 0 2 1 3 1 4 2 4 2 5 3 6 4 6 5 6 6 7 6 8 6 9 7 10 8 10 8 11 9 11 10 12 11 12 0 12";
        run(input, output);
        assert(output.str() == "16");
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
