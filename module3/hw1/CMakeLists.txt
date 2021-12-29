set(CMAKE_CXX_STANDARD 20)
project(hw1)
cmake_minimum_required(VERSION 3.11)

include_directories(Graph ListGraph ArcGraph MatrixGraph SetGraph)

add_library(GRAPHS SHARED
        ArcGraph/ArcGraph.cpp ArcGraph/ArcGraph.h
        Graph/Graph.h
        ListGraph/ListGraph.cpp ListGraph/ListGraph.h
        MatrixGraph/MatrixGraph.cpp MatrixGraph/MatrixGraph.h
        SetGraph/SetGraph.cpp SetGraph/SetGraph.h
        )

add_executable(hw1 main.cpp)
target_link_libraries(hw1 GRAPHS)