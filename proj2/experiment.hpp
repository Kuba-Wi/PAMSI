#pragma once
#include <ostream>
#include "graph_list.hpp"
#include "graph_matrix.hpp"

class experiment {
public:
    experiment() = default;
    experiment(const experiment&) = delete;
    experiment& operator=(const experiment&) = delete;
    ~experiment();

    void build_graph_file(const char* filename, size_t node_count, double density) const;
    void build_full_graph_file(const char* filename, size_t node_count) const;
    void find_path_and_count_time(double& time_list, double& time_matrix);
    void build_graphs(const char* filename);
    void display_results(const char* file_list, const char* file_matrix) const;
    void display_finding_times(size_t node_count, double density, size_t graph_count);
    void display_full_graph_finding_times(size_t node_count, size_t graph_count);
    
    void count_and_display_all_times(const size_t* node_count,
                                     size_t node_size,
                                     const double* density,
                                     size_t density_size,
                                     size_t graph_count);

private:
    graph_list* graph_list_ = nullptr;
    graph_matrix* graph_matrix_ = nullptr;
};
