#pragma once

template <typename ArrayType>
std::size_t divide_array(ArrayType& T, std::size_t first, std::size_t last) {
    std::size_t middle = (first + last) / 2;
    auto middle_value = T[middle];
    std::swap(T[middle], T[last]);

    std::size_t current_index = first;
    for (std::size_t i = first; i < last; ++i) {
        if (T[i] < middle_value) {
            std::swap(T[i], T[current_index++]);
        }
    }
    std::swap(T[current_index], T[last]);
    return current_index;
}

template <typename ArrayType>
void quick_sort(ArrayType& T, std::size_t first, std::size_t last) {
    if (first >= last) {
        return;
    }
    auto divide_index = divide_array(T, first, last);
    quick_sort(T, first, divide_index);
    quick_sort(T, divide_index + 1, last);
}
