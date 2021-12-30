/*
Задача 2. Количество различных путей (3 балла)
Обязательная задача
Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами. Найдите количество различных кратчайших путей между заданными вершинами.
Требования: сложность O(V+E).
Формат ввода.
v: кол-во вершин (макс. 50000),
n: кол-во ребер (макс. 200000),
n пар реберных вершин,
пара вершин u, w для запроса.
Формат вывода.
Количество кратчайших путей от u к w.
 */

#include <iostream>
#include <vector>
#include <queue>


struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<int> GetNextVertices(int vertex) const = 0;

    virtual std::vector<int> GetPrevVertices(int vertex) const = 0;
};


class ListGraph: public IGraph {
private:
    std::vector< std::vector<int> > graph;
    size_t verticesCount;

public:
    ListGraph(size_t verticesCount);

    void AddEdge(int from, int to) override;

    int VerticesCount() const override;

    std::vector<int> GetNextVertices(int vertex) const override;

    std::vector<int> GetPrevVertices(int vertex) const override;

    virtual ~ListGraph();
};


ListGraph::ListGraph(size_t verticesCount): verticesCount(verticesCount) {
    graph.resize(verticesCount);
}


int ListGraph::VerticesCount() const {
    return verticesCount;
}


void ListGraph::AddEdge(int from, int to) {
    graph[from].push_back(to);
    graph[to].push_back(from);
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


int numberOfShortestWay(const IGraph& graph, const int from, const int to) {
    std::queue<int> q;
    std::vector<int> paths(graph.VerticesCount(), 0);
    std::vector<int> depth(graph.VerticesCount(), 0);
    q.push(from);
    paths[from] = 1;

    while (!q.empty()) {
        int v = q.front(); q.pop();
        std::vector<int> children = graph.GetNextVertices(v);
        for (int & child : children) {
            // if vertex is not visited
            if (paths[child] == 0) {
                paths[child] = paths[v];
                depth[child] = depth[v] + 1;
                q.push(child);
            }
                // if vertex is visited
            else if (depth[child] == depth[v] + 1) {
                paths[child] += paths[v];
            }
        }
    }
    return paths[to];
}


int main() {
    size_t v = 0;
    std::cin >> v;
    ListGraph listGraph(v);

    int n = 0;
    std::cin >> n;

    int from = 0;
    int to = 0;
    for (int i = 0; i < n; ++i) {
        std::cin >> from >> to;
        listGraph.AddEdge(from, to);
    }

    std::cin >> from >> to;
    std::cout << numberOfShortestWay(listGraph, from, to);

    return 0;
}
