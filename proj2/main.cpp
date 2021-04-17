#include <fstream>
#include <iostream>
#include "experiment.hpp"
#include "graph_list.hpp"
#include "graph_matrix.hpp"

int main() {
    std::ofstream build{"../test_file.txt"};
    experiment exp;
    exp.build_graph_file(build, 1000, 0.5);
    build.close();
    exp.build_graphs("../test_file.txt");
    exp.find_path();
    exp.display_results("../result1.txt", "../result2.txt");

    return 0;
}
