#ifndef HW1_SETGRAPH_H
#define HW1_SETGRAPH_H

#include <vector>
#include <iostream>
#include <queue>
#include <set>
#include "Graph.h"

class SetGraph: public IGraph {
private:
    std::vector< std::set<int> > graph;
    size_t verticesCount;

public:
    SetGraph(size_t verticesCount);

    void AddEdge(int from, int to) override;

    SetGraph(const IGraph& otherTypeGraph);

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~SetGraph();
};


#endif //HW1_SETGRAPH_H
