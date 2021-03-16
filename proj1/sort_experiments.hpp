#pragma once
#include <algorithm>
#include <array>
#include <chrono>
#include <iostream>
#include <random>
#include <vector>

template <typename T, typename Arr>
void fill_partly_sorted(T& tables,
                        const Arr& sort_percent,
                        std::size_t elements_sizes,
                        std::size_t first,
                        std::size_t last) {
    std::size_t index_perc = 0;
    for (std::size_t i = first; i <= last; ++i) {
        tables[i].resize(elements_sizes);
        std::iota(tables[i].begin(), tables[i].end(), 1);
        std::shuffle(tables[i].begin() + sort_percent[index_perc] * elements_sizes, tables[i].end(),
                     std::mt19937{std::random_device{}()});
        if (++index_perc >= sort_percent.size()) {
            index_perc = 0;
        }
    }
}

template <typename T>
void fill_descending(T& tables, std::size_t elements_sizes, std::size_t first, std::size_t last) {
    for (std::size_t i = first; i <= last; ++i) {
        tables[i].resize(elements_sizes);
        std::generate(tables[i].begin(), tables[i].end(), [n{elements_sizes}]() mutable { return n--; });
    }
}

template <typename T>
void fill_tables(T& tables, std::size_t elements_sizes) {
    for (std::size_t i = 0; i < 25; ++i) {
        tables[i].resize(elements_sizes);
        std::iota(tables[i].begin(), tables[i].end(), 1);
        std::shuffle(tables[i].begin(), tables[i].end(), std::mt19937{std::random_device{}()});
    }

    std::array sort_percent{0.25, 0.5, 0.75};
    fill_partly_sorted(tables, sort_percent, elements_sizes, 25, 49);
    sort_percent = {0.95, 0.99, 0.997};
    fill_partly_sorted(tables, sort_percent, elements_sizes, 50, 74);
    fill_descending(tables, elements_sizes, 75, tables.size() - 1);
}

template <typename Sort_fun, typename T>
auto sort_time(Sort_fun sort_fun, T& tables, std::size_t first, std::size_t last) {
    auto start = std::chrono::high_resolution_clock::now();
    for (std::size_t i = first; i <= last; ++i) {
        sort_fun(tables[i], 0, tables[i].size() - 1);
    }
    auto stop = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count();
}

template <typename Sort_fun, typename T>
void sort_experiment(Sort_fun sort_fun, T& tables, std::size_t elements_sizes) {
    int all_time = 0;
    int one_time = 0;
    std::cout << elements_sizes << " elements:\n";

    one_time = sort_time(sort_fun, tables, 0, 24);
    std::cout << "\t25 tables of random numbers:\t" << one_time << " ms\n";
    all_time += one_time;

    one_time = sort_time(sort_fun, tables, 25, 49);
    std::cout << "\t25 tables sorted in 25%, 50%, 75%:\t " << one_time << " ms\n";
    all_time += one_time;

    one_time = sort_time(sort_fun, tables, 50, 74);
    std::cout << "\t25 tables sorted in 95%, 99%, 99.7%:\t " << one_time << " ms\n";
    all_time += one_time;

    one_time = sort_time(sort_fun, tables, 75, tables.size() - 1);
    std::cout << "\t25 tables of reverse sorted numbers:\t" << one_time << " ms\n";
    all_time += one_time;

    std::cout << "\tAll time: " << all_time << "\n";
}
