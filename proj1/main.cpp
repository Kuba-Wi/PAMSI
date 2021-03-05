#include <algorithm>
#include <array>
#include <iostream>
#include <iterator>
#include <random>
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "introsort.hpp"

int main() {
    constexpr std::size_t size = 1000'000;
    std::array<int, size> t;
    std::iota(t.begin(), t.end(), 0);
    std::shuffle(t.begin(), t.end(), std::mt19937{std::random_device{}()});
    // std::copy(t.begin(), t.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << "\n";
    intro_sort(t, 0, size - 1);
    // std::copy(t.begin(), t.end(), std::ostream_iterator<int>{std::cout, " "});
    std::cout << "\n";
    std::cout << std::boolalpha << std::is_sorted(t.begin(), t.end()) << "\n";
    return 0;
}
