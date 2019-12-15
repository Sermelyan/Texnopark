//
// Created by ser on 15.12.2019.
//

#include <vector>

#include "interface.hpp"

#ifndef GRAPH_MATRIXRPGRAPH_HPP
#define GRAPH_MATRIXRPGRAPH_HPP

class MatrixRPGraph : public IGraph {
public:
    explicit MatrixRPGraph(unsigned int count);
    explicit MatrixRPGraph(const IGraph &graph);
    ~MatrixRPGraph() override;

    [[nodiscard]] unsigned int VerticesCount() const override;

    [[nodiscard]] std::vector<unsigned int>
    GetNextVertices(unsigned int vertex) const override;
    [[nodiscard]] std::vector<unsigned int>
    GetPrevVertices(unsigned int vertex) const override;

    void AddEdge(unsigned int from, unsigned int to) override;

private:
    unsigned int** matrix;
    unsigned int count;
};

#endif //GRAPH_MATRIXRPGRAPH_HPP
