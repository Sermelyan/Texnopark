//
// Created by ser on 14.12.2019.
//

#include <vector>

#include "interface.hpp"

#ifndef GRAPH_LISTGRAPH_HPP
#define GRAPH_LISTGRAPH_HPP

class ListGraph : public IGraph {
  public:
    explicit ListGraph(unsigned int count);
    explicit ListGraph(const IGraph &graph);
    ~ListGraph() override;

    void AddEdge(unsigned int from, unsigned int to) override;

    [[nodiscard]] unsigned int VerticesCount() const override;

    [[nodiscard]] std::vector<unsigned int>
    GetNextVertices(unsigned int vertex) const override;
    [[nodiscard]] std::vector<unsigned int>
    GetPrevVertices(unsigned int vertex) const override;

  private:
    std::vector<std::vector<unsigned int>> adjacencyLists;
};

#endif // GRAPH_LISTGRAPH_HPP
