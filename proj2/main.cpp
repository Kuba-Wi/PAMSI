#include <fstream>
#include <iostream>
#include "graph_list.hpp"
#include "graph_matrix.hpp"

int main() {
    std::ifstream strm{"../input.txt"};
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_list graph;
    graph.build_list(strm);
    strm.close();
    graph.display_list(std::cout);

    strm.open("../input.txt");
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_matrix graph_m;
    graph_m.build_matrix(strm);
    strm.close();
    graph_m.display_matrix(std::cout);

    return 0;
}