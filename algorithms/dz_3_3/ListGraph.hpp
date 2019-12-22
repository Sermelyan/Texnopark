//
// Created by ser on 14.12.2019.
//

#include <vector>


#ifndef GRAPH_LISTGRAPH_HPP
#define GRAPH_LISTGRAPH_HPP

class ListGraph {
  public:
    explicit ListGraph(unsigned int count);
    ~ListGraph();

    void AddEdge(unsigned int v1, unsigned int v2);

    [[nodiscard]] unsigned int VerticesCount() const;

    [[nodiscard]] std::vector<unsigned int>
    GetVertices(unsigned int vertex) const;

  private:
    std::vector<std::vector<unsigned int>> adjacencyLists;
};

#endif // GRAPH_LISTGRAPH_HPP
