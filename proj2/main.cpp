#include "experiment.hpp"
#include "graph_list.hpp"
#include "graph_matrix.hpp"

int main() {
    constexpr size_t graph_count = 100;
    constexpr size_t density_size = 3;
    constexpr size_t node_size = 5;
    constexpr double density[density_size] = {0.25, 0.5, 0.75};
    constexpr size_t node_count[node_size] = {10, 50, 100, 500, 1000};
    experiment exp;
    exp.count_and_display_all_times(node_count, node_size, density, density_size, graph_count);

    return 0;
}
