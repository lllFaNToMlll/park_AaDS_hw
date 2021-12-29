#include <vector>
#include "Graph.h"
#include "SetGraph.h"

SetGraph::SetGraph(size_t verticesCount): verticesCount(verticesCount) {
    graph.resize(verticesCount);
}


int SetGraph::VerticesCount() const {
    return verticesCount;
}


void SetGraph::AddEdge(int from, int to) {
    graph[from].insert(to);
}


SetGraph::SetGraph(const IGraph& otherTypeGraph): SetGraph(otherTypeGraph.VerticesCount()) {
    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = otherTypeGraph.GetNextVertices(i);
        for (int j: nextVertices) {
            AddEdge(i, j);
        }
    }
}


std::vector<int> SetGraph::GetNextVertices(int vertex) const {
    std::vector<int> result(graph[vertex].begin(), graph[vertex].end());
    return result;
}


std::vector<int> SetGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < verticesCount; ++i) {
        if (graph[i].contains(vertex)) {
            result.push_back(i);
        }
    }
    return result;
}


SetGraph::~SetGraph() {}
