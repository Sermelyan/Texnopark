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

TEST(BFS, List) {
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
    BFS(MatrixGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(SetGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(ArcGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
}

TEST(BFS, Matrix) {
    MatrixGraph g(6);
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
    BFS(MatrixGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(SetGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(ArcGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
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
    BFS(MatrixGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
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
    BFS(MatrixGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(ListGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
    str.clear();
    BFS(SetGraph(g), 5, [&str](int v) { str += std::to_string(v) + " "; });
    ASSERT_EQ(ethalon, str);
}

class TotalTest : public ::testing::Test {
  protected:
    void SetUp() override {
        std::random_device rd{};
        std::mt19937 gen{rd()};
        srandom(rd());
        unsigned int count = 50000;
        std::normal_distribution<> d{(count / 2.0), 10};

        for (int i = 0; i < count; ++i) {
            for (int j = 0; j < random() % 10; ++j)
                arcs.emplace_back(i, static_cast<unsigned int>(d(gen)));
        }

        lg = new ListGraph(count);
        mg = new MatrixGraph(count);
        sg = new SetGraph(count);
        ag = new ArcGraph(count);
        for (const auto &arc : arcs) {
            lg->AddEdge(arc.first, arc.second);
            mg->AddEdge(arc.first, arc.second);
            sg->AddEdge(arc.first, arc.second);
            ag->AddEdge(arc.first, arc.second);
        }
    }

    void TearDown() override {
        delete lg;
        delete mg;
        delete sg;
        delete ag;
    }

    std::vector<std::pair<unsigned int, unsigned int>> arcs;
    ListGraph *lg;
    MatrixGraph *mg;
    SetGraph *sg;
    ArcGraph *ag;
};

// TEST_F(TotalTest, Print) {
//    for (const auto &arc : arcs)
//        std::cout << arc.first << " " << arc.second <<std::endl;
//}

TEST_F(TotalTest, List) {
    BFS(*lg, 100, [](int v) {});
}

TEST_F(TotalTest, Matrix) {
    BFS(*mg, 100, [](int v) {});
}

TEST_F(TotalTest, Set) {
    BFS(*sg, 100, [](int v) {});
}

TEST_F(TotalTest, Arc) {
    BFS(*ag, 100, [](int v) {});
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}