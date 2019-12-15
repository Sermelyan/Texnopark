//
// Created by ser on 15.12.2019.
//

#include <cassert>
#include "MatrixRPGraph.hpp"

MatrixRPGraph::MatrixRPGraph(unsigned int count) : count(count) {
    matrix = new unsigned int *[count];
    for (int i = 0; i < count; i++)
        matrix[i] = new unsigned int[count];
}

MatrixRPGraph::MatrixRPGraph(const IGraph &graph) : MatrixRPGraph(graph.VerticesCount()){
    for (int i = 0; i < graph.VerticesCount(); i++)
        for (const auto &j : graph.GetNextVertices(i))
            matrix[i][j]++;
}

MatrixRPGraph::~MatrixRPGraph() {
    for (int i = 0; i < count; i++)
        delete[] matrix[i];
    delete[] matrix;
}

void MatrixRPGraph::AddEdge(unsigned int from, unsigned int to) {
    assert(from >= 0 && from < count);
    assert(to >= 0 && to < count);
    matrix[from][to]++;
}

unsigned int MatrixRPGraph::VerticesCount() const {
    return count;
}

std::vector<unsigned int> MatrixRPGraph::GetNextVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < count);
    std::vector<unsigned int> result;
    for (unsigned int i = 0; i < count; i++)
        if (matrix[vertex][i] > 0)
            result.push_back(i);
    return result;
}

std::vector<unsigned int> MatrixRPGraph::GetPrevVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < count);
    std::vector<unsigned int> result;
    for (unsigned int i = 0; i < count; i++)
        if (matrix[i][vertex] > 0)
            result.push_back(i);
    return result;
}
