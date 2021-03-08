#pragma once
#include <algorithm>
#include "catch.hpp"

template <typename T,typename Vectors>
void check_sort(T sort_fun, const Vectors& vectors_const) {
    for (auto vec : vectors_const) {
        sort_fun(vec, 0, vec.size() - 1);
        REQUIRE(std::is_sorted(vec.begin(), vec.end()));
    }
}
