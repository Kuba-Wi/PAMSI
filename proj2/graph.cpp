#include "graph.hpp"
#include <iostream>

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
