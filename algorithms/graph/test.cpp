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

void BFS(const IGraph &graph, int vertex,
         const std::function<void(int)> &visit) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<unsigned int> qu;
    qu.push(vertex);
    visited[vertex] = true;

    while (!qu.empty()) {
        int current = qu.front();
        visit(current);
        qu.pop();
        std::vector<unsigned int> nextVertices = graph.GetNextVertices(current);
        for (int v : nextVertices)
            if (!visited[v]) {
                qu.push(v);
                visited[v] = true;
            }
    }
}

/*TEST(BFS, List) {
    ListGraph g(6);
    g.AddEdge(0, 5);
    g.AddEdge(0, 4);
    g.AddEdge(0, 2);
    g.AddEdge(1, 0);
    g.AddEdge(1, 2);
    g.AddEdge(2, 4);
    g.AddEdge(2, 3);
    g.AddEdge(3, 1);
    g.AddEdge(4, 3);
    g.AddEdge(5, 4);

    std::string ethalon, str;
    BFS(g, 5, [&ethalon](int v) { ethalon += std::to_string(v) + " "; });
    BFS(MatrixRPGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    EXPECT_EQ(ethalon, str);
    str.clear();
    BFS(SetGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(ArcGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
}

TEST(BFS, Matrix) {
    MatrixRPGraph g(6);
    g.AddEdge(0, 5);
    g.AddEdge(0, 4);
    g.AddEdge(0, 2);
    g.AddEdge(1, 0);
    g.AddEdge(1, 2);
    g.AddEdge(2, 4);
    g.AddEdge(2, 3);
    g.AddEdge(3, 1);
    g.AddEdge(4, 3);
    g.AddEdge(5, 4);

    std::string ethalon, str;
    BFS(g, 5, [&ethalon](int v) { ethalon += std::to_string(v) + " "; });
    BFS(ListGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    EXPECT_EQ(ethalon, str);
    str.clear();
    BFS(SetGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    EXPECT_EQ(ethalon, str);
    str.clear();
    BFS(ArcGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    EXPECT_EQ(ethalon, str);
}

TEST(BFS, Set) {
    SetGraph g(6);
    g.AddEdge(0, 5);
    g.AddEdge(0, 4);
    g.AddEdge(0, 2);
    g.AddEdge(1, 0);
    g.AddEdge(1, 2);
    g.AddEdge(2, 4);
    g.AddEdge(2, 3);
    g.AddEdge(3, 1);
    g.AddEdge(4, 3);
    g.AddEdge(5, 4);

    std::string ethalon, str;
    BFS(g, 5, [&ethalon](int v) { ethalon += std::to_string(v) + " "; });
    BFS(MatrixRPGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    EXPECT_EQ(ethalon, str);
    str.clear();
    BFS(ListGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(ArcGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
}

TEST(BFS, Arc) {
    ArcGraph g(6);
    g.AddEdge(0, 5);
    g.AddEdge(0, 4);
    g.AddEdge(0, 2);
    g.AddEdge(1, 0);
    g.AddEdge(1, 2);
    g.AddEdge(2, 4);
    g.AddEdge(2, 3);
    g.AddEdge(3, 1);
    g.AddEdge(4, 3);
    g.AddEdge(5, 4);

    std::string ethalon, str;
    BFS(g, 5, [&ethalon](int v) { ethalon += std::to_string(v) + " "; });
    BFS(MatrixRPGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    EXPECT_EQ(ethalon, str);
    str.clear();
    BFS(ListGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(SetGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
}*/

std::vector<std::pair<unsigned int, unsigned int>> arcs;
ListGraph *lg;
MatrixRPGraph *mg;
SetGraph *sg;
ArcGraph *ag;
unsigned int count = 1000;

TEST(DataPrerpare, ArcsGen) {
    std::random_device rd{};
    std::mt19937 gen{rd()};
    srandom(rd());

    std::normal_distribution<> d{(count / 2.0), 10};

    for (int i = 0; i < count; ++i) {
        for (int j = 0; j < random() % 20; ++j)
            arcs.emplace_back(i, static_cast<unsigned int>(d(gen)));
    }
}

TEST(DataPrerpare, ListAlloc) {
    lg = new ListGraph(count);
}

TEST(DataPrerpare, MatrixAlloc) {
    mg = new MatrixRPGraph(count);
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