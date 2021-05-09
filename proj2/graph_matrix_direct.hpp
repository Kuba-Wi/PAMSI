#pragma once
#include <istream>
#include "graph_matrix.hpp"

class graph_matrix_direct : public graph_matrix {
public:
    graph_matrix_direct(std::istream& strm);
    graph_matrix_direct(const graph_matrix_direct&) = delete;
    graph_matrix_direct& operator=(const graph_matrix_direct&) = delete;
    ~graph_matrix_direct() override = default;
};
