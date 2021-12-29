#include "ArcGraph.h"
#include <vector>
#include "Graph.h"

ArcGraph::ArcGraph(size_t verticesCount): verticesCount(verticesCount) {}


int ArcGraph::VerticesCount() const {
    return verticesCount;
}


void ArcGraph::AddEdge(int from, int to) {
    graph.push_back(std::make_pair(from, to));
}


ArcGraph::ArcGraph(const IGraph& otherTypeGraph): ArcGraph(otherTypeGraph.VerticesCount()) {
    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = otherTypeGraph.GetNextVertices(i);
        for (int j: nextVertices) {
            AddEdge(i, j);
        }
    }
}


std::vector<int> ArcGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < verticesCount; ++i) {
        if (graph[i].first == vertex) {
            result.push_back(graph[i].second);
        }
    }
    return result;
}

std::vector<int> ArcGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < verticesCount; ++i) {
        if (graph[i].second == vertex) {
            result.push_back(graph[i].first);
        }
    }
    return result;
}


ArcGraph::~ArcGraph() {}
