//
// Created by ser on 14.12.2019.
//

#include <gtest/gtest.h>
#include <queue>
#include <random>
#include <vector>

#include "ArcGraph.hpp"
#include "ListGraph.hpp"
#include "MatrixGraph.hpp"
#include "MatrixRPGraph.hpp"
#include "SetGraph.hpp"

void BFS(const IGraph &graph, unsigned int vertex,
         const std::function<void(int)> &visit) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<unsigned int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        unsigned int current = qu.front();
        visit(current);
        qu.pop();
        std::vector<unsigned int> nextVertices = graph.GetNextVertices(current);
        for (const auto& v : nextVertices)
            if (!visited[v]) {
                qu.push(v);
                visited[v] = true;
            }
    }
}

std::vector<std::pair<unsigned int, unsigned int>> arcs;
ListGraph *lg;
MatrixGraph *mg;
SetGraph *sg;
ArcGraph *ag;
unsigned int count = 25000;

TEST(DataPrerpare, ArcsGen) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    srandom(rd());

    std::normal_distribution<> d{(count / 2.0), 10};

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < random() % 10; ++j)
            arcs.emplace_back(i, static_cast<unsigned int>(d(gen)));
    }
}

TEST(DataPrerpare, ListAlloc) {
    lg = new ListGraph(count);
}

TEST(DataPrerpare, MatrixAlloc) {
    mg = new MatrixGraph(count);
}

TEST(DataPrerpare, SetAlloc) {
    sg = new SetGraph(count);
}

TEST(DataPrerpare, ArcAlloc) {
    ag = new ArcGraph(count);
}

TEST(GraphFilling, ListFill) {
    for (const auto &arc : arcs) {
        lg->AddEdge(arc.first, arc.second);
    }
}

TEST(GraphFilling, MatrixFill) {
    for (const auto &arc : arcs) {
        mg->AddEdge(arc.first, arc.second);
    }
}

TEST(GraphFilling, SetFill) {
    for (const auto &arc : arcs) {
        sg->AddEdge(arc.first, arc.second);
    }
}

TEST(GraphFilling, ArcFill) {
    for (const auto &arc : arcs) {
        ag->AddEdge(arc.first, arc.second);
    }
}

TEST(GraphBFSTest, List) {
    BFS(*lg, 666, [](int v) {});
}

TEST(GraphBFSTest, Matrix) {
    BFS(*mg, 666, [](int v) {});
}

TEST(GraphBFSTest, Set) {
    BFS(*sg, 666, [](int v) {});
}

TEST(GraphBFSTest, Arc) {
    BFS(*ag, 666, [](int v) {});
}

TEST(DataFree, CleanUp) {
    delete lg;
    delete mg;
    delete sg;
    delete ag;
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}