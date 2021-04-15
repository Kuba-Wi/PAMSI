#include <fstream>
#include <iostream>
#include "graph_list.hpp"
#include "graph_matrix.hpp"

int main() {
    std::ifstream strm{"../input1.txt"};
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_list graph{strm};
    strm.close();
    graph.display_list(std::cout);
    std::cout << "\n";
    graph.find_paths();
    graph.display_paths();
    std::cout << "\n";
    strm.open("../input1.txt");
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_matrix graph_m{strm};
    strm.close();
    graph_m.display_matrix(std::cout);

    return 0;
}