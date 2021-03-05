#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include "merge_sort.hpp"

int main() {
    constexpr std::size_t size = 10;
    std::array<int, size> t;
    std::iota(t.begin(), t.end(), 0);
    std::shuffle(t.begin(), t.end(), std::mt19937{std::random_device{}()});
    for (auto i : t) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    merge_sort(t, 0, size - 1);
    for (auto i : t) {
        std::cout << i << " ";
    }
    std::cout << "\n";
    std::cout << std::boolalpha << std::is_sorted(t.begin(), t.end()) << "\n";
    return 0;
}
