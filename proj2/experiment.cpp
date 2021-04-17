#include "experiment.hpp"
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
