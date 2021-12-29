#include "ListGraph.h"
#include <vector>
#include "Graph.h"

ListGraph::ListGraph(size_t verticesCount): verticesCount(verticesCount) {
    graph.resize(verticesCount);
}


int ListGraph::VerticesCount() const {
    return verticesCount;
}


void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
}


ListGraph::ListGraph(const IGraph& otherTypeGraph): ListGraph(otherTypeGraph.VerticesCount()) {
    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = otherTypeGraph.GetNextVertices(i);
        for (int j: nextVertices) {
            AddEdge(i, j);
        }
    }
}


std::vector<int> ListGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    result.resize(graph[vertex].size());
    std::copy(graph[vertex].begin(), graph[vertex].end(), result.begin());
    return result;
}

std::vector<int> ListGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (size_t parent = 0; parent < verticesCount; ++parent) {
        for (int child: graph[parent]) {
            if (child == vertex) {
                result.push_back(parent);
            }
        }
    }
    return result;
}

ListGraph::~ListGraph() {}
