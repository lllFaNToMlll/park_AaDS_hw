#ifndef HW1_ARCGRAPH_H
#define HW1_ARCGRAPH_H

#include "Graph.h"

class ArcGraph: public IGraph {
private:
    std::vector< std::pair<int, int> > graph;
    size_t verticesCount;

public:
    ArcGraph(size_t verticesCount);

    ArcGraph(const IGraph& otherTypeGraph);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~ArcGraph();
};

#endif //HW1_ARCGRAPH_H
