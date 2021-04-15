#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "graph_list.hpp"
#include "graph_matrix.hpp"

void make_graph() {
    std::ofstream strm{"../test_file.txt"};
    std::vector<std::vector<size_t>> vec(500 * 999, {0, 0});
    strm << 500 * 999 << " " << 1000 << " " << 0 << "\n";

    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distr(0, 10000);

    for (size_t i = 0; i < 1000 - 1; ++i) {
        for(size_t j = i + 1; j < 1000; ++j) {
            strm << i << " " << j << " " << distr(gen) << "\n";
        }
    }
    strm.close();
}

int main() {
    make_graph();

    std::ifstream strm{"../test_file.txt"};
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_list graph_l{strm};
    strm.close();
    // graph_l.display_graph(std::cout);

    std::ofstream write{"../result1.txt"};
    graph_l.find_paths();
    graph_l.display_result(write);
    write.close();

    strm.open("../test_file.txt");
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_matrix graph_m{strm};
    strm.close();
    // graph_m.display_graph(std::cout);

    write.open("../result2.txt");
    graph_m.find_paths();
    graph_m.display_result(write);
    write.close();

    return 0;
}