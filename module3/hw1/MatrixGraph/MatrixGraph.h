#ifndef HW1_MATRIXGRAPH_H
#define HW1_MATRIXGRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include "Graph.h"

class MatrixGraph: public IGraph {
private:
    std::vector< std::vector<bool> > graph;
    size_t verticesCount;

public:
    MatrixGraph(size_t verticesCount);

    MatrixGraph(const IGraph& otherTypeGraph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~MatrixGraph();
};

#endif //HW1_MATRIXGRAPH_H
