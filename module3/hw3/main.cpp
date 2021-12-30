/*
Требуется отыскать самый выгодный маршрут между городами.
Требования: время работы O((N+M)logN), где N-количество городов, M-известных дорог между ними.
Формат входных данных.
Первая строка содержит число N – количество городов.
Вторая строка содержит число M - количество дорог.
Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
Последняя строка содержит маршрут (откуда и куда нужно доехать).
Формат выходных данных.
Вывести длину самого выгодного маршрута.
 */

#include <iostream>
#include <vector>
#include <set>


struct IGraph {
    virtual ~IGraph() {}

    virtual void AddEdge(int from, int to, int weight) = 0;

    virtual int VerticesCount() const  = 0;

    virtual std::vector<std::pair<int, int>> GetNextVerticesPair(int from) const = 0;
};


class ListGraph: public IGraph {
private:
    std::vector<std::vector<std::pair<int, int>>> graph;
    size_t verticesCount;

public:
    ListGraph(size_t verticesCount);

    void AddEdge(int from, int to, int weight) override;

    int VerticesCount() const override;

    std::vector<std::pair<int, int>> GetNextVerticesPair(int from) const override;

    virtual ~ListGraph();
};


ListGraph::ListGraph(size_t verticesCount): verticesCount(verticesCount) {
    graph.resize(verticesCount);
}


int ListGraph::VerticesCount() const {
    return verticesCount;
}


void ListGraph::AddEdge(int from, int to, int weight) {
    graph[from].push_back({to, weight});
    graph[to].push_back({from, weight});
}


std::vector<std::pair<int, int>> ListGraph::GetNextVerticesPair(int from) const {
    return graph[from];
}


ListGraph::~ListGraph() {}


void theBestWay(ListGraph& graph, int s, std::vector<int>& d, std::vector<int>& pi) {
    d[s] = 0;
    std::set< std::pair<int, int> > set; // расстояние/ключ, сортируем по расстоянию
    set.insert(std::make_pair(d[s], s));

    while (!set.empty()) {
        auto u = *set.begin();
        set.erase(set.begin());
        std::vector< std::pair<int, int> > children = graph.GetNextVerticesPair(u.second);
        for (auto& child: children) {
            if (d[child.first] == INT32_MAX) {
                d[child.first] = d[u.second] + child.second;
                pi[child.first] = u.second;
                set.insert(std::make_pair(d[child.first], child.first));
            }
            else {
                if (d[child.first] > d[u.second] + child.second) {
                    auto it = set.find(std::make_pair(d[child.first], child.first));
                    set.erase(it);
                    d[child.first] = d[u.second] + child.second;
                    pi[child.first] = u.second;
                    set.insert(std::make_pair(d[child.first], child.first));
                }
            }
        }
    }
}

int main() {
    int n = 0;
    std::cin >> n;
    ListGraph listGraph(n);
    int m = 0;
    std::cin >> m;
    int from = 0;
    int to = 0;
    int weight = 0;
    for (int i = 0; i < m; ++i) {
        std::cin >> from >> to >> weight;
        listGraph.AddEdge(from, to, weight);
    }
    std::cin >> from >> to;
    std::vector<int> d(listGraph.VerticesCount(), INT32_MAX);
    std::vector<int> pi(listGraph.VerticesCount(), -1);
    theBestWay(listGraph, from, d, pi);
    std::cout << d[to] << std::endl;
    return 0;
}
