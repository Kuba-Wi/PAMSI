#include "graph_matrix.hpp"
#include <limits>

graph_matrix::~graph_matrix() {
    for (size_t i = 0; i < node_count_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
}

void graph_matrix::build_matrix(std::istream& strm) {
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
                matrix_[j][i] = std::numeric_limits<int>::max();
            }
        }
    }

    size_t first_node, second_node;
    int weight;
    for (size_t i = 0; i < node_count_; ++i) {
        strm >> first_node >> second_node >> weight;
        matrix_[first_node][second_node] = weight;
        matrix_[second_node][first_node] = weight;
    }
}

void graph_matrix::display_matrix(std::ostream& strm) {
    for (size_t i = 0; i < node_count_; ++i) {
        for (size_t j = 0; j < node_count_; ++j) {
            strm << matrix_[i][j] << " ";
        }
        strm << "\n";
    }
}
