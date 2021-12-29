#ifndef HW1_GRAPH_H
#define HW1_GRAPH_H

#include <vector>
#include <queue>

struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


template <class Callback>
void dfs(const IGraph& graph, std::vector<bool>& visited, int v, Callback callback) {
    visited[v] = true;
    callback(v);
    auto children = graph.GetNextVertices(v);
    for (int child: children) {
        if (!visited[child]) {
            dfs(graph, visited, child, callback);
        }
    }
}


template<class Callback>
void dfsMain(const IGraph& graph, Callback callback) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    for (size_t v = 0; v < graph.VerticesCount(); ++v) {
        if (!visited[v]) {
            dfs(graph, visited, v, callback);
        }
    }
}


template<class Callback>
void bfs(const IGraph& graph, Callback callback) {
    std::vector<bool> visited(graph.VerticesCount(), false);
    std::queue<int> q;
    for (int v = 0; v < graph.VerticesCount(); ++v) {
        if (!visited[v]) {
            visited[v] = true;
            q.push(v);
            while(!q.empty()) {
                int curVertex = q.front();
                q.pop();
                callback(curVertex);
                auto children = graph.GetNextVertices(curVertex);
                for (int child: children) {
                    if (!visited[child]) {
                        visited[child] = true;
                        q.push(child);
                    }
                }
            }
        }
    }
}

#endif //HW1_GRAPH_H
