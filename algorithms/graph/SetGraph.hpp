//
// Created by ser on 14.12.2019.
//

#ifndef GRAPH_SETGRAPH_HPP
#define GRAPH_SETGRAPH_HPP

#include <set>
#include <vector>

#include "interface.hpp"

class SetGraph : public IGraph {
  public:
    explicit SetGraph(unsigned int count);
    SetGraph(const IGraph &graph);
    ~SetGraph() override;

    void AddEdge(unsigned int from, unsigned int to) override;

    [[nodiscard]] unsigned int VerticesCount() const override;

    [[nodiscard]] std::vector<unsigned int>
    GetNextVertices(unsigned int vertex) const override;
    [[nodiscard]] std::vector<unsigned int>
    GetPrevVertices(unsigned int vertex) const override;

  private:
    std::vector<std::set<unsigned int>> adjacencySets;
};

#endif // GRAPH_SETGRAPH_HPP
