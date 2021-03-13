#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

template <typename T>
void fill_tables(T& tables, std::size_t size, std::size_t elements_num) {
    constexpr std::size_t sort_percent_size = 7;
    std::array<double, sort_percent_size> sort_percent{0, 0.25, 0.5, 0.75, 0.95, 0.99, 0.997};
    std::size_t index_perc = 0;

    for (std::size_t i = 0; i < size * 0.75; ++i) {
        tables[i].resize(elements_num);
        std::iota(tables[i].begin(), tables[i].end(), 1);
        std::shuffle(tables[i].begin() + sort_percent[index_perc] * elements_num, tables[i].end(),
                     std::mt19937{std::random_device{}()});
        if (++index_perc >= sort_percent_size) {
            index_perc = 0;
        }
    }
    for (std::size_t i = size * 0.75; i < size; ++i) {
        tables[i].resize(elements_num);
        std::generate(tables[i].begin(), tables[i].end(), [n{elements_num}]() mutable { return n--; });
    }
}

template <typename Sort_fun, typename T>
void sort_experiment(Sort_fun sort_fun, T& tables, std::size_t elements_num) {
    auto start = std::chrono::high_resolution_clock::now();
    for (auto& tab : tables) {
        sort_fun(tab, 0, elements_num - 1);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    std::cout << elements_num
              << " elements: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count()
              << " ms\n";
}
