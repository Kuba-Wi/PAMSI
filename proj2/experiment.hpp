#pragma once
#include <ostream>
#include "graph_list.hpp"
#include "graph_matrix.hpp"

class experiment {
public:
    void build_graph_file(std::ostream& strm, size_t node_count, double density) const;
    void build_full_graph_file(std::ostream& strm, size_t node_count) const;
    void find_path();
    void build_graphs(const char* filename);
    void display_results(const char* file_list, const char* file_matrix) const;

private:
    graph_list graph_list_;
    graph_matrix graph_matrix_;
};
