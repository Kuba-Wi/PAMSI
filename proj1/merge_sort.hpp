#include <array>
#include <vector>

template <std::size_t size>
void merge(std::array<int, size>& T, std::size_t first, std::size_t middle, std::size_t last) {
    std::vector<int> temp_tab(last - first + 1);
    std::copy(T.begin() + first, T.begin() + last + 1, temp_tab.begin());
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

    std::copy(temp_tab.begin(), temp_tab.end(), T.begin() + first);
}

template <std::size_t size>
void merge_sort(std::array<int, size>& T, std::size_t first, std::size_t last) {
    if (first >= last) {
        return;
    }
    std::size_t middle = (first + last) / 2;
    merge_sort(T, first, middle);
    merge_sort(T, middle + 1, last);
    merge(T, first, middle, last);
}

template <std::size_t size>
void merge_sort_n_r(std::array<int, size>& T, std::size_t first, std::size_t last) {
    std::size_t step = 1;
    std::size_t index = first;
    while (step < size) {
        while (index + step - 1 <= last) {
            merge(T, index, index + step / 2, index + step - 1);
            index += step;
        }

        ++step;
        index = first;
    }
    // merge(T, 0, 0, 1);
    // merge(T, 0, 1, 2);
    // merge(T, 3, 3, 4);
    // merge(T, 3, 4, 5);
    // merge(T, 0, 2, 5);
}

template <std::size_t size>
void bubble_sort(std::array<int, size>& tab) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size - 1; j++) {
            if (tab[j] > tab[j + 1])
                std::swap(tab[j], tab[j + 1]);
        }
    }
}
