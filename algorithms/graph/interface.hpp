//
// Created by ser on 14.12.2019.
//

#include <vector>

#ifndef GRAPH_INTERFACE_HPP
#define GRAPH_INTERFACE_HPP

struct IGraph {
    virtual ~IGraph() = default;

    virtual void AddEdge(unsigned int from, unsigned int to) = 0;

    [[nodiscard]] virtual unsigned int VerticesCount() const = 0;

    virtual std::vector<unsigned int>
    GetNextVertices(unsigned int vertex) const = 0;
    virtual std::vector<unsigned int>
    GetPrevVertices(unsigned int vertex) const = 0;
};

#endif // GRAPH_INTERFACE_HPP
