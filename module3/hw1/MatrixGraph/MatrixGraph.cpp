#include "MatrixGraph.h"
#include <vector>
#include "Graph.h"

MatrixGraph::MatrixGraph(size_t verticesCount): verticesCount(verticesCount) {
    graph.resize(verticesCount);
    for (size_t i = 0; i < verticesCount; ++i) {
        graph[i].resize(verticesCount);
        std::fill(graph[i].begin(), graph[i].end(), false);
    }
}


int MatrixGraph::VerticesCount() const {
    return verticesCount;
}


void MatrixGraph::AddEdge(int from, int to) {
    graph[from][to] = true;
}


MatrixGraph::MatrixGraph(const IGraph& otherTypeGraph): MatrixGraph(otherTypeGraph.VerticesCount()) {
    for (int i = 0; i < verticesCount; ++i) {
        std::vector<int> nextVertices = otherTypeGraph.GetNextVertices(i);
        for (int j: nextVertices) {
            AddEdge(i, j);
        }
    }
}


std::vector<int> MatrixGraph::GetNextVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < verticesCount; ++i) {
        if (graph[vertex][i]) {
            result.push_back(i);
        }
    }
    return result;
}


std::vector<int> MatrixGraph::GetPrevVertices(int vertex) const {
    std::vector<int> result;
    for (int i = 0; i < verticesCount; ++i) {
        if (graph[i][vertex]) {
            result.push_back(i);
        }
    }
    return result;
}


MatrixGraph::~MatrixGraph() {}
