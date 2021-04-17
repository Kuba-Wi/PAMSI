#pragma once
#include <ostream>
#include "graph_list.hpp"
#include "graph_matrix.hpp"

class experiment {
public:
    void build_graph_file(std::ostream& strm, size_t node_count, double density) const;
    void build_full_graph_file(std::ostream& strm, size_t node_count) const;

private:
    graph_list graph_list_;
    graph_matrix graph_matrix_;
};
