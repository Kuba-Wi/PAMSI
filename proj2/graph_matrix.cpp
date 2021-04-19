#include "graph_matrix.hpp"
#include <limits>

graph_matrix::graph_matrix(std::istream& strm) {
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
    for (size_t i = 0; i < edge_count_; ++i) {
        strm >> first_node >> second_node >> weight;
        matrix_[first_node][second_node] = weight;
        matrix_[second_node][first_node] = weight;
    }
}

graph_matrix::~graph_matrix() {
    for (size_t i = 0; i < node_count_; ++i) {
        delete[] matrix_[i];
    }
    delete[] matrix_;
    delete[] weights_;
    delete[] prev_node_;
}

void graph_matrix::display_graph(std::ostream& strm) const {
    for (size_t i = 0; i < node_count_; ++i) {
        for (size_t j = 0; j < node_count_; ++j) {
            strm << matrix_[i][j] << " ";
        }
        strm << "\n";
    }
}

void graph_matrix::find_paths() {
    this->fill_initial_prev_node();
    this->fill_initial_weights();

    bool* visited_nodes = new bool[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        visited_nodes[i] = false;
    }

    size_t node_index = start_node_;
    while (!visited_nodes[node_index]) {
        visited_nodes[node_index] = true;
        for (size_t i = 0; i < node_count_; ++i) {
            this->update_weight_and_prev_node(i, node_index, visited_nodes);
        }
        node_index = this->get_cheapest_index(visited_nodes);
    }

    delete[] visited_nodes;
}

size_t graph_matrix::get_cheapest_index(bool* visited) const {
    size_t node_index = start_node_;
    for (size_t i = 0; i < node_count_; ++i) {
        if (!visited[i]) {
            node_index = i;
            break;
        }
    }
    if (visited[node_index]) {
        return node_index;
    }

    for (size_t i = 0; i < node_count_; ++i) {
        if (!visited[i] && weights_[i] < weights_[node_index]) {
            node_index = i;
        }
    }
    return node_index;
}

void graph_matrix::update_weight_and_prev_node(size_t neighbour, size_t node_index, bool* visited) {
    if (visited[neighbour] || matrix_[node_index][neighbour] == std::numeric_limits<int>::max()) {
        return;
    }
    if (is_new_path_cheaper(neighbour, node_index)) {
        weights_[neighbour] = weights_[node_index] + matrix_[node_index][neighbour];
        prev_node_[neighbour] = node_index;
    }
}

bool graph_matrix::is_new_path_cheaper(size_t neighbour, size_t node_index) const {
    return weights_[node_index] < weights_[neighbour] - matrix_[node_index][neighbour];
}
