//
// Created by ser on 14.12.2019.
//

#include <cassert>
#include <vector>

#include "ListGraph.hpp"

ListGraph::ListGraph(unsigned int count) : adjacencyLists(count) {}

ListGraph::ListGraph(const IGraph &graph) : ListGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        adjacencyLists[i] = graph.GetNextVertices(i);
}

ListGraph::~ListGraph() = default;

void ListGraph::AddEdge(unsigned int from, unsigned int to) {
    assert(from >= 0 && from < adjacencyLists.size());
    assert(to >= 0 && to < adjacencyLists.size());
    adjacencyLists[from].push_back(to);
}

unsigned int ListGraph::VerticesCount() const { return adjacencyLists.size(); }

std::vector<unsigned int>
ListGraph::GetNextVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());
    return adjacencyLists[vertex];
}

std::vector<unsigned int>
ListGraph::GetPrevVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < adjacencyLists.size());
    std::vector<unsigned int> result;
    for (unsigned int from = 0; from < adjacencyLists.size(); from++)
        for (unsigned int i = 0; i < adjacencyLists[from].size(); i++)
            if (adjacencyLists[from][i] == vertex)
                result.push_back(from);

    return result;
}
