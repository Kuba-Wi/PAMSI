#pragma once
#include "graph.hpp"
#include <iostream>

class graph_matrix : public graph {
public:
    graph_matrix(std::istream& strm);
    graph_matrix(const graph_matrix&) = delete;
    graph_matrix& operator=(const graph_matrix&) = delete;
    ~graph_matrix() override;
    void display_graph(std::ostream& strm) const override;
    void find_paths() override;

private:
    void fill_initial_weights();
    size_t get_cheapest_index(bool* visited) const;
    void update_weight_and_prev_node(size_t neighbour, size_t node_index, bool* visited);
    bool is_new_path_cheaper(size_t neighbour, size_t node_index) const;

    int** matrix_ = nullptr;
    size_t edge_count_;
};
