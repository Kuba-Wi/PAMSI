#include "graph.hpp"
#include <limits>

void graph::display_result(std::ostream& strm) const {
    for (size_t i = 0; i < node_count_; ++i) {
        if (i == start_node_) {
            continue;
        }
        strm << i << "\t" << weights_[i] << "\t";
        this->display_path(strm, i);
        strm << i << "\n";
    }
}

void graph::display_path(std::ostream& strm, size_t node_index) const {
    if (node_index == start_node_) {
        return;
    }
    display_path(strm, prev_node_[node_index]);
    strm << prev_node_[node_index] << " ";
}

void graph::fill_initial_weights() {
    delete[] weights_;
    weights_ = new int[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        weights_[i] = std::numeric_limits<int>::max();
    }
    weights_[start_node_] = 0;
}

void graph::fill_initial_prev_node() {
    delete[] prev_node_;
    prev_node_ = new size_t[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        prev_node_[i] = start_node_;
    }
}
