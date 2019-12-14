//
// Created by ser on 14.12.2019.
//

#include "SetGraph.hpp"
#include <cassert>

SetGraph::SetGraph(unsigned int count) : adjacencySets(count) {}

SetGraph::SetGraph(const IGraph &graph) : SetGraph(graph.VerticesCount()) {
    for (unsigned int i = 0; i < graph.VerticesCount(); i++)
        for (const auto &nextVertex : graph.GetNextVertices(i))
            adjacencySets[i].insert(nextVertex);
}

SetGraph::~SetGraph() = default;

void SetGraph::AddEdge(unsigned int from, unsigned int to) {
    assert(from >= 0 && from < adjacencySets.size());
    assert(to >= 0 && to < adjacencySets.size());
    adjacencySets[from].insert(to);
}

unsigned int SetGraph::VerticesCount() const { return adjacencySets.size(); }

std::vector<unsigned int> SetGraph::GetNextVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < adjacencySets.size());
    return std::vector<unsigned int>(adjacencySets[vertex].begin(),
                                     adjacencySets[vertex].end());
}

std::vector<unsigned int> SetGraph::GetPrevVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < adjacencySets.size());
    std::vector<unsigned int> result;
    for (unsigned int i = 0; i < adjacencySets.size(); i++)
        if (adjacencySets[i].find(vertex) != adjacencySets[i].end())
            result.push_back(i);
    return result;
}
