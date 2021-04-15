#include <fstream>
#include <iostream>
#include "graph_list.hpp"
#include "graph_matrix.hpp"

int main() {
    std::ifstream strm{"../input1.txt"};
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_list graph_l{strm};
    strm.close();
    graph_l.display_graph(std::cout);

    std::cout << "\n";
    graph_l.find_paths();
    graph_l.display_result(std::cout);
    std::cout << "\n";

    strm.open("../input1.txt");
    if (!strm.is_open()) {
        std::cout << "File not open\n";
    }
    graph_matrix graph_m{strm};
    strm.close();
    graph_m.display_graph(std::cout);

    std::cout << "\n";
    graph_m.find_paths();
    graph_m.display_result(std::cout);

    return 0;
}