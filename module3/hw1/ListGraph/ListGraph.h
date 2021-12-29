#ifndef HW1_LISTGRAPH_H
#define HW1_LISTGRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include "Graph.h"

class ListGraph: public IGraph {
private:
    std::vector< std::vector<int> > graph;
    size_t verticesCount;

public:
    ListGraph(size_t verticesCount);

    ListGraph(const IGraph& otherTypeGraph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~ListGraph();
};

#endif //HW1_LISTGRAPH_H
