/*
Copyright 2019 Сергей Меликян АПО-12
Задание 3. Модуль 3.
*/

#include <cassert>
#include <climits>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
#include <set>

typedef std::pair<unsigned, unsigned> keyVal;

class ListGraph {
public:
    explicit ListGraph(unsigned int count);
    ~ListGraph();

    void AddEdge(unsigned v1, unsigned v2, unsigned dist);

    [[nodiscard]] unsigned int VerticesCount() const;

    [[nodiscard]] std::vector<keyVal>
    GetVertices(unsigned int vertex) const;

private:
    std::vector<std::vector<keyVal>> adjacencyLists;
};

ListGraph::ListGraph(unsigned int count) : adjacencyLists(count) {}

ListGraph::~ListGraph() = default;

void ListGraph::AddEdge(unsigned v1, unsigned v2, unsigned dist) {
    assert(v1 >= 0 && v1 < adjacencyLists.size());
    assert(v1 >= 0 && v2 < adjacencyLists.size());
    adjacencyLists[v1].emplace_back(v2, dist);
    adjacencyLists[v2].emplace_back(v1, dist);
}

unsigned int ListGraph::VerticesCount() const { return adjacencyLists.size(); }

std::vector<keyVal>
ListGraph::GetVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

struct less {
    bool operator()(const keyVal &left, const keyVal &right) const {
        return left.second < right.second;
    }
};

typedef std::multiset<keyVal, less> priority_queue;

int Dixtra(const ListGraph &graph, unsigned int start, unsigned finish) {
    std::vector<unsigned> vertDist(graph.VerticesCount(), INT_MAX);
    std::vector<unsigned> visited(graph.VerticesCount(), false);
    priority_queue qu;
    vertDist[start] = 0;
    qu.emplace(start, vertDist[start]);

    while (!qu.empty()) {
        auto current = *(qu.begin());
        qu.erase(qu.begin());

        for (const auto &next : graph.GetVertices(current.first)) {
            if (visited[next.first])
                continue;

            unsigned nextDist = vertDist[current.first] + next.second;
            if (nextDist < vertDist[next.first]) {
                auto findNext = qu.find(keyVal(next.first, vertDist[next.first]));
                vertDist[next.first] = nextDist;
                if (findNext != qu.end()) {
                    qu.erase(findNext);
                }
            }
            qu.emplace(next.first, nextDist);
        }
        visited[current.first] = true;
    }
    return (vertDist[finish] == INT_MAX) ? -1 : vertDist[finish];
}

void run(std::istream &input, std::ostream &output) {
    unsigned int n = 0, m = 0;
    input >> n >> m;
    assert(n > 0 && n <= 200000);
    assert(m > 0 && m <= 1000000);

    ListGraph graph(n);

    for (size_t i = 0; i < m; i++) {
        unsigned int v1, v2, d;
        input >> v1 >> v2 >> d;
        graph.AddEdge(v1, v2, d);
    }

    unsigned int Start, Finish;
    input >> Start >> Finish;
    assert(Start >= 0 && Start <= n);
    assert(Finish >= 0 && Finish <= n);
    output << Dixtra(graph, Start, Finish);
}

void test() {
    {
        std::stringstream input, output;
        input << "6\n"
                 "9\n"
                 "0 3 1\n"
                 "0 4 2\n"
                 "1 2 7\n"
                 "1 3 2\n"
                 "1 4 3\n"
                 "1 5 3\n"
                 "2 5 3\n"
                 "3 4 4\n"
                 "3 5 6\n"
                 "0 2";
        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "9");
    }
    {
        std::stringstream input, output;
        input << "6\n"
                 "9\n"
                 "0 1 7\n"
                 "0 2 9\n"
                 "0 5 14\n"
                 "1 2 10\n"
                 "1 3 15\n"
                 "2 5 2\n"
                 "2 3 11\n"
                 "3 4 6\n"
                 "5 4 9\n"
                 "0 3";
        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "20");
    }
    {
        std::stringstream input, output;
        input << "6\n"
                 "5\n"
                 "0 1 7\n"
//                 "0 2 9\n"
                 "0 5 14\n"
//                 "1 2 10\n"
                 "1 3 15\n"
//                 "2 5 2\n"
//                 "2 3 11\n"
                 "3 4 6\n"
                 "5 4 9\n"
                 "0 2";
        run(input, output);
        std::cout << output.str() << std::endl;
        assert(output.str() == "-1");
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
