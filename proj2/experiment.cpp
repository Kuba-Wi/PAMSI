#include "experiment.hpp"
#include <fstream>
#include <random>
#include <vector>

void experiment::build_full_graph_file(std::ostream& strm, size_t node_count) const {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distr(0, node_count - 1);

    strm << node_count * (node_count - 1) / 2 << " " << node_count << " " << distr(gen) << "\n";

    for (size_t i = 0; i < node_count - 1; ++i) {
        for (size_t j = i + 1; j < node_count; ++j) {
            strm << i << " " << j << " " << distr(gen) << "\n";
        }
    }
}

void experiment::build_graph_file(std::ostream& strm, size_t node_count, double density) const {
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distr(0, node_count - 1);

    size_t edge_count = (node_count * (node_count - 1) / 2) * density;
    strm << edge_count << " " << node_count << " " << distr(gen) << "\n";

    std::vector<std::vector<size_t>> edges;
    size_t first_node;
    size_t second_node;
    while (edges.size() < edge_count) {
        first_node = distr(gen);
        second_node = distr(gen);
        if (first_node == second_node) {
            continue;
        }

        edges.push_back({first_node, second_node});
    }

    for (auto& edge : edges) {
        strm << edge[0] << " " << edge[1] << " " << distr(gen) << "\n";
    }
}

void experiment::find_path() {
    graph_matrix_.find_paths();
    graph_list_.find_paths();
}

void experiment::build_graphs(const char* filename) {
    std::ifstream strm{filename};
    graph_list_.build_graph(strm);
    strm.close();
    strm.open(filename);
    graph_matrix_.build_graph(strm);
    strm.close();
}

void experiment::display_results(const char* file_list, const char* file_matrix) const {
    std::ofstream strm{file_list};
    graph_list_.display_result(strm);
    strm.close();
    strm.open(file_matrix);
    graph_matrix_.display_result(strm);
    strm.close();
}
