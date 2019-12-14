//
// Created by ser on 14.12.2019.
//

#include <vector>

#include "interface.hpp"

#ifndef GRAPH_MATRIXGRAPH_HPP
#define GRAPH_MATRIXGRAPH_HPP

class MatrixGraph : public IGraph {
  public:
    explicit MatrixGraph(unsigned int count);
    explicit MatrixGraph(const IGraph &graph);
    ~MatrixGraph() override;

    [[nodiscard]] unsigned int VerticesCount() const override;

    [[nodiscard]] std::vector<unsigned int>
    GetNextVertices(unsigned int vertex) const override;
    [[nodiscard]] std::vector<unsigned int>
    GetPrevVertices(unsigned int vertex) const override;

    void AddEdge(unsigned int from, unsigned int to) override;

  private:
    std::vector<std::vector<unsigned int>> matrix;
};

#endif // GRAPH_MATRIXGRAPH_HPP
