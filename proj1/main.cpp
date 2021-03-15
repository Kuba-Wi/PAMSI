#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include "introsort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "sort_experiments.hpp"

int main() {
    constexpr std::size_t size = 100;
    std::vector<std::vector<int>> tables(size);
    std::array<std::size_t, 5> sizes{10'000, 50'000, 100'000, 500'000, 1'000'000};

    std::cout << "Merge sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, size, i);
        sort_experiment(merge_sort<std::vector<int>>, tables, size, i);
    }

    std::cout << "\nQuick sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, size, i);
        sort_experiment(quick_sort<std::vector<int>>, tables, size, i);
    }

    std::cout << "\nIntro sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, size, i);
        sort_experiment(intro_sort<std::vector<int>>, tables, size, i);
    }

    std::cout << "\nHeap sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, size, i);
        sort_experiment(heap_sort<std::vector<int>>, tables, size, i);
    }

    return 0;
}
