#include "experiment.hpp"
#include <chrono>
#include <fstream>
#include <random>

experiment::~experiment() {
    delete graph_list_;
    delete graph_matrix_;
}

void experiment::build_full_graph_file(const char* filename, size_t node_count) const {
    std::ofstream strm{filename};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distr(0, node_count - 1);

    strm << node_count * (node_count - 1) / 2 << " " << node_count << " " << distr(gen) << "\n";

    for (size_t i = 0; i < node_count - 1; ++i) {
        for (size_t j = i + 1; j < node_count; ++j) {
            strm << i << " " << j << " " << distr(gen) << "\n";
        }
    }
    strm.close();
}

void experiment::build_graph_file(const char* filename, size_t node_count, double density) const {
    std::ofstream strm{filename};
    std::random_device rd;
    std::mt19937 gen{rd()};
    std::uniform_int_distribution<> distr(0, node_count - 1);

    size_t edge_count = (node_count * (node_count - 1) / 2) * density;
    strm << edge_count << " " << node_count << " " << distr(gen) << "\n";

    size_t first_node;
    size_t second_node;
    size_t i = 0;
    while (i < edge_count) {
        first_node = distr(gen);
        second_node = distr(gen);
        if (first_node == second_node) {
            continue;
        }

        strm << first_node << " " << second_node << " " << distr(gen) << "\n";
        ++i;
    }
    strm.close();
}

void experiment::find_path_and_count_time(double& time_list, double& time_matrix) {
    auto start = std::chrono::high_resolution_clock::now();
    graph_list_->find_paths();
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> interval_ms = stop - start;
    time_list = interval_ms.count();

    start = std::chrono::high_resolution_clock::now();
    graph_matrix_->find_paths();
    stop = std::chrono::high_resolution_clock::now();
    interval_ms = stop - start;
    time_matrix = interval_ms.count();
}

void experiment::find_paths() {
    graph_list_->find_paths();
    graph_matrix_->find_paths();
}

void experiment::build_graphs(const char* filename) {
    std::ifstream strm{filename};
    delete graph_list_;
    graph_list_ = new graph_list_direct{strm};
    strm.close();

    strm.open(filename);
    delete graph_matrix_;
    graph_matrix_ = new graph_matrix_direct{strm};
    strm.close();
}

void experiment::display_results(const char* file_list, const char* file_matrix) const {
    std::ofstream strm{file_list};
    graph_list_->display_result(strm);
    strm.close();
    
    strm.open(file_matrix);
    graph_matrix_->display_result(strm);
    strm.close();
}

void experiment::display_finding_times(size_t node_count, double density, size_t graph_count) {
    double one_time[2];
    double time_list = 0, time_matrix = 0;

    for (size_t j = 0; j < graph_count; ++j) {
        this->build_graph_file("../test_file.txt", node_count, density);
        this->build_graphs("../test_file.txt");
        this->find_path_and_count_time(one_time[0], one_time[1]);
        time_list += one_time[0];
        time_matrix += one_time[1];
        this->display_results("../result1.txt", "../result2.txt");
    }
    std::cout << "Density: " << density << "\n";
    std::cout << "\ttime for list: " << time_list / graph_count << " ms\n";
    std::cout << "\ttime for matrix: " << time_matrix / graph_count << " ms\n";
}

void experiment::display_full_graph_finding_times(size_t node_count, size_t graph_count) {
    double one_time[2];
    double time_list = 0, time_matrix = 0;

    for (size_t i = 0; i < graph_count; ++i) {
        this->build_full_graph_file("../test_file.txt", node_count);
        this->build_graphs("../test_file.txt");
        this->find_path_and_count_time(one_time[0], one_time[1]);
        time_list += one_time[0];
        time_matrix += one_time[1];
        this->display_results("../result1.txt", "../result2.txt");
    }
    std::cout << "Full graph:\n";
    std::cout << "\ttime for list: " << time_list / graph_count << " ms\n";
    std::cout << "\ttime for matrix: " << time_matrix / graph_count << " ms\n";
}

void experiment::count_and_display_all_times(const size_t* node_count,
                                             size_t node_size,
                                             const double* density,
                                             size_t density_size,
                                             size_t graph_count) {
    for (size_t nod = 0; nod < node_size; ++nod) {
        std::cout << "Graph node count: " << node_count[nod] << "\n";
        for (size_t den = 0; den < density_size; ++den) {
            this->display_finding_times(node_count[nod], density[den], graph_count);
        }

        this->display_full_graph_finding_times(node_count[nod], graph_count);
        std::cout << "\n";
    }
}
