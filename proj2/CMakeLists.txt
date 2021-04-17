cmake_minimum_required(VERSION 3.10)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(graphs)
set(FILES
    graph_list.cpp
    graph_matrix.cpp
    graph.cpp
    experiment.cpp
)
set(FLAGS -Wall -pedantic -Wextra)


add_executable(${PROJECT_NAME} main.cpp ${FILES})
target_compile_options(${PROJECT_NAME} PRIVATE ${FLAGS})
