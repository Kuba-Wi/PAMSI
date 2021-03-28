#include <algorithm>
#include <random>
#include <vector>
#include "catch.hpp"
#include "introsort.hpp"
#include "merge_sort.hpp"
#include "quick_sort.hpp"
#include "sort_experiments.hpp"
#include "test_functions.hpp"

TEST_CASE("Sort algorithms should sort elements", "[sort]") {
    std::vector<std::vector<int>> vectors(100);
    std::size_t num_of_elements = 0;
    for (auto& vec : vectors) {
        vec.resize(++num_of_elements);
        std::iota(vec.begin(), vec.end(), 0);
        std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
    }
    std::vector<int> vec(1'000'000);
    std::iota(vec.begin(), vec.end(), 0);
    std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
    vectors.push_back(vec);
    
    SECTION("Merge sort should sort elements") { check_sort(merge_sort<decltype(vectors)::value_type>, vectors); }
    SECTION("Quicksort should sort elements") { check_sort(quick_sort<decltype(vectors)::value_type>, vectors); }
    SECTION("Intro sort should sort elements") { check_sort(intro_sort<decltype(vectors)::value_type>, vectors); }
    SECTION("Heap sort should sort elements") { check_sort(heap_sort<decltype(vectors)::value_type>, vectors); }
}

TEST_CASE("Fill partly sorted function should fill table", "[fill]") {
    constexpr std::size_t size = 10;
    std::vector<std::vector<int>> tables(2);
    std::array sort_percent{0.2, 0.3};
    fill_partly_sorted(tables, sort_percent, size, 0, 1);

    REQUIRE(tables[0][0] == 1);
    REQUIRE(tables[0][1] == 2);
    REQUIRE(tables[1][0] == 1);
    REQUIRE(tables[1][1] == 2);
    REQUIRE(tables[1][2] == 3);
    REQUIRE(!std::is_sorted(tables[0].begin(), tables[0].end()));
    REQUIRE(!std::is_sorted(tables[1].begin(), tables[1].end()));
}

TEST_CASE("Fill descending function should fill descending", "[fill]") {
    constexpr std::size_t size = 5;
    const std::vector<int> result{5, 4, 3, 2, 1};
    std::vector<std::vector<int>> tables(2);
    fill_descending(tables, size, 0, 1);
    REQUIRE(result == tables[0]);
    REQUIRE(result == tables[1]);
}
