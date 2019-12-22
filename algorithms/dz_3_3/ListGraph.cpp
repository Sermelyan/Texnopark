//
// Created by ser on 14.12.2019.
//

#include <cassert>
#include <vector>

#include "ListGraph.hpp"

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
