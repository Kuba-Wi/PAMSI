#pragma once
#include <iostream>

class graph_matrix {
public:
    graph_matrix(std::istream& strm);
    graph_matrix(const graph_matrix&) = delete;
    graph_matrix& operator=(const graph_matrix&) = delete;
    ~graph_matrix();
    void display_matrix(std::ostream& strm);

private:
    int** matrix_ = nullptr;
    size_t start_node_;
    size_t node_count_;
    size_t edge_count_;
};
