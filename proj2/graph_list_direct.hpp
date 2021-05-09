#pragma once
#include <istream>
#include "graph_list.hpp"

class graph_list_direct : public graph_list {
public:
    graph_list_direct(std::istream& strm);
    graph_list_direct(const graph_list_direct&) = delete;
    graph_list_direct& operator=(const graph_list_direct&) = delete;
    ~graph_list_direct() override = default;
};
