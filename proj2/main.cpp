#include <fstream>
#include <iostream>
#include <random>
#include "experiment.hpp"
#include "graph_list.hpp"
#include "graph_matrix.hpp"

int main() {
    std::ofstream build{"../test_file.txt"};
    experiment exp;
    exp.build_graph_file(build, 1000, 0.5);
    build.close();

    std::ifstream strm{"../test_file.txt"};
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_list graph_l;
    graph_l.build_graph(strm);
    strm.close();

    std::ofstream write{"../result1.txt"};
    graph_l.find_paths();
    graph_l.display_result(write);
    write.close();

    strm.open("../test_file.txt");
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_matrix graph_m;
    graph_m.build_graph(strm);
    strm.close();

    write.open("../result2.txt");
    graph_m.find_paths();
    graph_m.display_result(write);
    write.close();

    return 0;
}
