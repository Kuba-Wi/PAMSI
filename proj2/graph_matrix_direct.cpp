#include <limits>
#include "graph_matrix_direct.hpp"

graph_matrix_direct::graph_matrix_direct(std::istream& strm) {
    strm >> edge_count_ >> node_count_ >> start_node_;
    matrix_ = new int*[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        matrix_[i] = new int[node_count_];
    }

    for (size_t i = 0; i < node_count_; ++i) {
        for (size_t j = 0; j < node_count_; ++j) {
            if (i == j) {
                matrix_[i][j] = 0;
            } else {
                matrix_[i][j] = std::numeric_limits<int>::max();
            }
        }
    }

    size_t first_node, second_node;
    int weight;
    for (size_t i = 0; i < edge_count_; ++i) {
        strm >> first_node >> second_node >> weight;
        matrix_[first_node][second_node] = weight;
    }
}
