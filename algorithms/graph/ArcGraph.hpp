//
// Created by ser on 15.12.2019.
//

#include <vector>

#include "interface.hpp"

#ifndef GRAPH_ARCGRAPH_HPP
#define GRAPH_ARCGRAPH_HPP

class ArcGraph : public IGraph {
  public:
    explicit ArcGraph(unsigned int count);
    explicit ArcGraph(const IGraph &graph);
    ~ArcGraph() override;

    [[nodiscard]] unsigned int VerticesCount() const override;

    [[nodiscard]] std::vector<unsigned int>
    GetNextVertices(unsigned int vertex) const override;
    [[nodiscard]] std::vector<unsigned int>
    GetPrevVertices(unsigned int vertex) const override;

    void AddEdge(unsigned int from, unsigned int to) override;

  private:
    std::vector<std::pair<unsigned int, unsigned int>> arcs;
    unsigned int count;
};

#endif // GRAPH_ARCGRAPH_HPP
