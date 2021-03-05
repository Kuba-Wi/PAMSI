#pragma once

#include <array>
#include <cmath>
#include "quick_sort.hpp"

template <std::size_t size>
void shift_down(std::array<int, size>& T, std::size_t first, std::size_t parent_to_change, std::size_t last) {
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

template <std::size_t size>
void heap_sort(std::array<int, size>& T, std::size_t first, std::size_t last) {
    for (int i = (last - first + 1) / 2 + first - 1; i >= int(first); --i) {
        shift_down(T, first, i, last);
    }
    for (std::size_t i = last; i >= first + 1; --i) {
        std::swap(T[first], T[i]);
        shift_down(T, first, first, i - 1);
    }
}

template <std::size_t size>
void intro_sort(std::array<int, size>& T, std::size_t first, std::size_t last, int M = (int)floor(2 * log2(size))) {
    if(first >= last) {
        return;
    }
    if(M <= 0) {
        heap_sort(T, first, last);
        return;
    }
    auto divide_index = divide_array(T, first, last);
    intro_sort(T, first, divide_index, M - 1);
    intro_sort(T, divide_index + 1, last, M - 1);
}
