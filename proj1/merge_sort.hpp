#pragma once

#include <vector>

template <typename ArrayType>
void merge(ArrayType& T, std::size_t first, std::size_t middle, std::size_t last) {
    std::vector temp_tab(std::begin(T) + first, std::begin(T) + last + 1);
    std::size_t temp_index = 0;
    std::size_t left_index = first;
    std::size_t right_index = middle + 1;
    while (left_index <= middle && right_index <= last) {
        if (T[left_index] < T[right_index]) {
            temp_tab[temp_index++] = T[left_index++];
        } else {
            temp_tab[temp_index++] = T[right_index++];
        }
    }
    while (left_index <= middle)
        temp_tab[temp_index++] = T[left_index++];
    while (right_index <= last)
        temp_tab[temp_index++] = T[right_index++];

    std::copy(temp_tab.begin(), temp_tab.end(), std::begin(T) + first);
}

template <typename ArrayType>
void merge_sort(ArrayType& T, std::size_t first, std::size_t last) {
    if (first >= last) {
        return;
    }
    std::size_t middle = (first + last) / 2;
    merge_sort(T, first, middle);
    merge_sort(T, middle + 1, last);
    merge(T, first, middle, last);
}
