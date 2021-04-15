#pragma once
#include <iostream>

class graph_matrix {
public:
    graph_matrix(std::istream& strm);
    graph_matrix(const graph_matrix&) = delete;
    graph_matrix& operator=(const graph_matrix&) = delete;
    ~graph_matrix();
    void display_matrix(std::ostream& strm);
    void display_paths() const;
    void find_paths();

private:
    void fill_initial_weights();
    size_t get_cheapest_unvisited_index(bool* visited) const;
    void update_weight_and_prev_node(size_t neighbour, size_t node_index, bool* visited);
    bool is_new_path_cheaper(size_t neighbour, size_t node_index) const;

    int** matrix_ = nullptr;
    int* weights_ = nullptr;
    size_t* prev_node_ = nullptr;
    size_t start_node_;
    size_t node_count_;
    size_t edge_count_;
};
