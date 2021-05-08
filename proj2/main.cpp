#include <iostream>
#include "experiment.hpp"

int choose_option() {
    std::cout << "1 - efficiency tests\n";
    std::cout << "2 - read custom file with graph\n";
    int option;
    std::cin >> option;
    return option;
}

void efficiency_test() {
    experiment exp;
    constexpr size_t graph_count = 100;
    constexpr size_t density_size = 3;
    constexpr size_t node_size = 5;
    constexpr double density[density_size] = {0.25, 0.5, 0.75};
    constexpr size_t node_count[node_size] = {10, 50, 100, 500, 1000};
    exp.count_and_display_all_times(node_count, node_size, density, density_size, graph_count);
}

void custom_file() {
    std::cout << "File name:\n";
    experiment exp;
    char filename[100];
    std::cin >> filename;
    exp.build_graphs(filename);
    exp.find_paths();
    exp.display_results("../result1.txt", "../result2.txt");
}

int main() {
    int option = choose_option();
    if (option == 1) {
        efficiency_test();
    } else {
        custom_file();
    }

    return 0;
}
