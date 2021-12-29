#include <iostream>
#include "ArcGraph.h"
#include "SetGraph.h"
#include "MatrixGraph.h"
#include "ListGraph.h"

int main() {
    ArcGraph arcGraph(9);

    arcGraph.AddEdge(0, 1);

    arcGraph.AddEdge(1, 5);

    arcGraph.AddEdge(6, 0);

    arcGraph.AddEdge(1, 2);

    arcGraph.AddEdge(2, 3);

    arcGraph.AddEdge(3, 4);

    arcGraph.AddEdge(4, 2);

    arcGraph.AddEdge(0, 7);

    arcGraph.AddEdge(0, 8);


    std::cout << "ArcGraph from ArcGraph(verticesCount: 6): " << std::endl;
    std::cout << "ArcGraph bfs: " << std::endl;
    bfs(arcGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    std::cout << "ArcGraph dfs: " << std::endl;
    dfsMain(arcGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    std::cout << "============================" << std::endl;

    std::cout << "ListGraph from ArcGraph: " << std::endl;
    ListGraph listGraph(arcGraph);
    std::cout << "ListGraph bfs: " << std::endl;
    bfs(listGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    std::cout << "ListGraph dfs: " << std::endl;
    dfsMain(listGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    std::cout << "============================" << std::endl;

    std::cout << "MatrixGraph from ListGraph: " << std::endl;
    MatrixGraph matrixGraph(listGraph);
    std::cout << "MatrixGraph bfs: " << std::endl;
    bfs(matrixGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    std::cout << "MatrixGraph dfs: " << std::endl;
    dfsMain(matrixGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    std::cout << "============================" << std::endl;

    std::cout << "SetGraph from MatrixGraph: " << std::endl;
    SetGraph setGraph(matrixGraph);
    std::cout << "SetGraph bfs: " << std::endl;
    bfs(setGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    std::cout << "SetGraph dfs: " << std::endl;
    dfsMain(setGraph, [](int element) {
        std::cout << element << " ";
    });
    std::cout << std::endl;

    return 0;
}
