//
// Created by ser on 14.12.2019.
//

#include <cassert>
#include "MatrixGraph.hpp"

MatrixGraph::MatrixGraph(unsigned int count) : matrix(count) {
    for (auto &item : matrix) {
        item.assign(count, 0);
    }
}

MatrixGraph::MatrixGraph(const IGraph &graph) : MatrixGraph(graph.VerticesCount()){
    for (int i = 0; i < graph.VerticesCount(); i++)
        for (const auto &j : graph.GetNextVertices(i))
            matrix[i][j]++;
}

MatrixGraph::~MatrixGraph() = default;

void MatrixGraph::AddEdge(unsigned int from, unsigned int to) {
    assert(from >= 0 && from < matrix.size());
    assert(to >= 0 && to < matrix.size());
    matrix[from][to]++;
}

unsigned int MatrixGraph::VerticesCount() const {
    return matrix.size();
}

std::vector<unsigned int> MatrixGraph::GetNextVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < matrix.size());
    std::vector<unsigned int> result;
    for (unsigned int i = 0; i < matrix[vertex].size(); i++)
        if (matrix[vertex][i] > 0)
            result.push_back(i);
    return result;
}

std::vector<unsigned int> MatrixGraph::GetPrevVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < matrix.size());
    std::vector<unsigned int> result;
    for (unsigned int i = 0; i < matrix.size(); i++)
        if (matrix[i][vertex] > 0)
            result.push_back(i);
    return result;
}
