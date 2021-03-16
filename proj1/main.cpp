#include <algorithm>
#include <array>
#include <iostream>
#include <vector>
#include "introsort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "sort_experiments.hpp"

int main() {
    std::vector<std::vector<int>> tables(100);
    const std::array<std::size_t, 5> sizes{10'000, 50'000, 100'000, 500'000, 1'000'000};

    std::cout << "Merge sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, i);
        sort_experiment(merge_sort<std::vector<int>>, tables, i);
    }

    std::cout << "\nQuick sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, i);
        sort_experiment(quick_sort<std::vector<int>>, tables, i);
    }

    std::cout << "\nIntro sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, i);
        sort_experiment(intro_sort<std::vector<int>>, tables, i);
    }

    std::cout << "\nHeap sort:\n";
    for (auto i : sizes) {
        fill_tables(tables, i);
        sort_experiment(heap_sort<std::vector<int>>, tables, i);
    }

    return 0;
}
