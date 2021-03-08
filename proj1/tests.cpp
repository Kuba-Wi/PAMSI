#include <algorithm>
#include <random>
#include <vector>
#include "catch.hpp"
#include "introsort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "test_functions.hpp"

TEST_CASE("Sort algorithms should sort elements", "[sort]") {
    std::vector<std::vector<int>> vectors(100);
    std::size_t num_of_elements = 0;
    for (auto& vec : vectors) {
        vec.resize(++num_of_elements);
        std::iota(vec.begin(), vec.end(), 0);
        std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
    }
    SECTION("Merge sort should sort elements") { check_sort(merge_sort<decltype(vectors)::value_type>, vectors); }
    SECTION("Quicksort should sort elements") { check_sort(quick_sort<decltype(vectors)::value_type>, vectors); }
    SECTION("Intro sort should sort elements") { check_sort(intro_sort<decltype(vectors)::value_type>, vectors); }
    SECTION("Heap sort should sort elements") { check_sort(heap_sort<decltype(vectors)::value_type>, vectors); }
}
