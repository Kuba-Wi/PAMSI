#include "graph_list_direct.hpp"

graph_list_direct::graph_list_direct(std::istream& strm) {
    strm >> edge_count_ >> node_count_ >> start_node_;
    list_ = new node*[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        list_[i] = nullptr;
    }

    size_t first_node, second_node;
    int weight;
    for (size_t i = 0; i < edge_count_; ++i) {
        strm >> first_node >> second_node >> weight;

        list_[first_node] = new node{second_node, weight, list_[first_node]};
    }
}
