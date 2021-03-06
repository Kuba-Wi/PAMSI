#pragma once

#include <array>
#include <cmath>
#include "quick_sort.hpp"

template <typename ArrayType>
void shift_down(ArrayType& T, std::size_t first, std::size_t parent_to_change, std::size_t last) {
    std::size_t max_index = parent_to_change;
    std::size_t parent_index;
    std::size_t child_index;
    do {
        parent_index = max_index;
        child_index = 2 * (parent_index - first) + 1 + first;
        if (child_index <= last) {
            if (T[child_index] > T[max_index]) {
                max_index = child_index;
            }
        }
        child_index = 2 * (parent_index - first) + 2 + first;
        if (child_index <= last) {
            if (T[child_index] > T[max_index]) {
                max_index = child_index;
            }
        }
        std::swap(T[parent_index], T[max_index]);
    } while (parent_index != max_index);
}

template <typename ArrayType>
void heap_sort(ArrayType& T, std::size_t first, std::size_t last) {
    for (int i = (last - first + 1) / 2 + first - 1; i >= int(first); --i) {
        shift_down(T, first, i, last);
    }
    for (std::size_t i = last; i >= first + 1; --i) {
        std::swap(T[first], T[i]);
        shift_down(T, first, first, i - 1);
    }
}

template <typename ArrayType>
void intro_main(ArrayType& T, std::size_t first, std::size_t last, int M) {
    if (first >= last) {
        return;
    }
    if (M <= 0) {
        heap_sort(T, first, last);
        return;
    }
    auto divide_index = divide_array(T, first, last);
    intro_main(T, first, divide_index, M - 1);
    intro_main(T, divide_index + 1, last, M - 1);
}

template <typename ArrayType>
void intro_sort(ArrayType& T, std::size_t first, std::size_t last) {
    int M = (int)floor(2 * log2(last - first + 1));
    intro_main(T, first, last, M);
}
