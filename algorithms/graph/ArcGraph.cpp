//
// Created by ser on 15.12.2019.
//

#include <cassert>
#include <vector>

#include "ArcGraph.hpp"

ArcGraph::ArcGraph(unsigned int count) : arcs(count * 2), count(count) {}

ArcGraph::ArcGraph(const IGraph &graph) : ArcGraph(graph.VerticesCount()) {
    for (int i = 0; i < graph.VerticesCount(); i++)
        for (const auto &j : graph.GetNextVertices(i))
            arcs.emplace_back(i, j);
}

ArcGraph::~ArcGraph() = default;

void ArcGraph::AddEdge(unsigned int from, unsigned int to) {
    assert(from >= 0 && from < count);
    assert(to >= 0 && to < count);
    arcs.emplace_back(from, to);
}

unsigned int ArcGraph::VerticesCount() const { return count; }

std::vector<unsigned int> ArcGraph::GetNextVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < count);
    std::vector<unsigned int> result;
    for (const auto &arc : arcs)
        if (arc.first == vertex)
            result.push_back(arc.second);
    return result;
}

std::vector<unsigned int> ArcGraph::GetPrevVertices(unsigned int vertex) const {
    assert(vertex >= 0 && vertex < count);
    std::vector<unsigned int> result;
    for (const auto &arc : arcs)
        if (arc.second == vertex)
            result.push_back(arc.first);
    return result;
}
