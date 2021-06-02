#include "board.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>

error_code board::put_mark(uint8_t x, uint8_t y, mark m) {
    if (mark_count_full()) {
        return error_code::size_exceeded;
    }
    if (x >= size_ || y >= size_) {
        return error_code::out_of_range;
    }
    if (bad_mark(m)) {
        return error_code::bad_mark;
    }

    auto it = std::find_if(board_.begin(), board_.end(), [&](const auto& field){
        return x == std::get<0>(field) && y == std::get<1>(field);
    });
    if (it != board_.end()) {
        return error_code::field_taken;
    }

    board_.emplace_back(x, y, m);
    if (m == mark::circle) {
        ++circle_count_;
    } else {
        ++cross_count_;
    }

    return error_code::ok;
}

bool board::check_win_condition(mark m) const {
    std::vector<std::tuple<uint8_t, uint8_t, mark>> board_copy;
    std::copy_if(board_.begin(),
                 board_.end(), 
                 std::back_inserter<std::vector<std::tuple<uint8_t, uint8_t, mark>>>(board_copy), 
                 [&](const auto& field){
        return std::get<2>(field) == m;
    });

    return check_row_win(board_copy) || check_column_win(board_copy) || check_diagonal_win(board_copy);
}

std::pair<uint8_t, uint8_t> board::added_index(const board& other) const {
    return {std::get<0>(other.board_.back()), std::get<1>(other.board_.back())};
}

bool board::equal(const board& other) const {
    return std::equal(board_.begin(), board_.end(), other.board_.begin(), [](const auto& lhs, const auto& rhs){
        return std::get<0>(lhs) == std::get<0>(rhs) &&
               std::get<1>(lhs) == std::get<1>(rhs) &&
               std::get<2>(lhs) == std::get<2>(rhs);
    });
}

bool board::bad_mark(mark m) const {
    return (m == mark::circle && circle_count_ > cross_count_) || 
           (m == mark::cross && cross_count_ > circle_count_);
}

bool board::check_diagonal_win(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& board_part) const {
    if (board_part.size() == 0) {
        return false;
    }

    std::vector<std::vector<bool>> vec(size_);
    for (auto& row : vec) {
        row.resize(size_);
    }
    auto board_copy = board_part;
    std::sort(board_copy.begin(), board_copy.end(), [](auto& lhs, auto& rhs){
        if (std::get<0>(lhs) == std::get<0>(rhs)) {
            return std::get<1>(lhs) < std::get<1>(rhs);
        }
        return (std::get<0>(lhs) < std::get<0>(rhs));
    });
    auto it = board_copy.begin();
    
    uint8_t i = 0, j = 0;
    for (; i < size_; ++i) {
        for (j = 0; j < size_; ++j) {
            if (it != board_copy.end()) {
                if (i == std::get<0>(*it) && j == std::get<1>(*it)) {
                    vec[i][j] = true;
                    ++it;
                } else {
                    vec[i][j] = false;
                }
            } else {
                vec[i][j] = false;
            }
        }
    }

    uint8_t counter = 0;
    uint8_t counter_anti = 0;
    for (int row_start = size_ - 1; row_start >= 0; --row_start) {
        j = 0;
        counter = 0;
        counter_anti = 0;
        for (i = row_start; i < size_; ++i) {
            if (vec[i][j]) {
                ++counter;
                if (counter >= marks_to_win_) {
                    return true;
                }
            } else {
                counter = 0;
            }
            if (vec[size_ - 1 - i][j++]) {
                ++counter_anti;
                if (counter_anti >= marks_to_win_) {
                    return true;
                }
            } else {
                counter_anti = 0;
            }
        }
    }
    uint8_t row = 0;
    for (uint8_t column_start = 1; column_start < size_; ++column_start) {
        row = 0;
        counter = 0;
        counter_anti = 0;
        for (uint8_t column = column_start; column < size_; ++column) {
            if (vec[row][column]) {
                ++counter;
                if (counter >= marks_to_win_) {
                    return true;
                }
            } else {
                counter = 0;
            }
            if (vec[size_ - 1 - row++][column]) {
                ++counter_anti;
                if (counter_anti >= marks_to_win_) {
                    return true;
                }
            } else {
                counter_anti = 0;
            }
        }
    }
    
    return false;
}

bool board::check_row_win(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& board_part) const {
    if (board_part.size() == 0) {
        return false;
    }
    auto board_copy = board_part;
    sort_row_column(board_copy);

    int prev = std::get<1>(board_copy.front()) - 1;
    uint8_t counter = 0;
    uint8_t row = 0;
    for (const auto& field : board_copy) {
        if (std::get<0>(field) != row) {
            prev = std::get<1>(field) - 1;
            counter = 0;
            row = std::get<0>(field);
        }
        if (int(std::get<1>(field)) == prev + 1) {
            ++counter;
            if (counter == marks_to_win_) {
                return true;
            }
        } else {
            counter = 0;
        }
        ++prev;
    }
    return false;
}

bool board::check_column_win(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& board_part) const {
    if (board_part.size() == 0) {
        return false;
    }
    auto board_copy = board_part;
    sort_column_row(board_copy);

    int prev = std::get<0>(board_copy.front()) - 1;
    uint8_t counter = 0;
    uint8_t column = 0;
    for (const auto& field : board_copy) {
        if (std::get<1>(field) != column) {
            prev = std::get<0>(field) - 1;
            counter = 0;
            column = std::get<1>(field);
        }
        if (int(std::get<0>(field)) == prev + 1) {
            ++counter;
            if (counter == marks_to_win_) {
                return true;
            }
        } else {
            counter = 0;
        }
        ++prev;
    }
    return false;
}

void board::sort_row_column(std::vector<std::tuple<uint8_t, uint8_t, mark>>& boar) const {
    std::sort(boar.begin(), boar.end(), [](auto& lhs, auto& rhs){
        if (std::get<0>(lhs) == std::get<0>(rhs)) {
            return std::get<1>(lhs) < std::get<1>(rhs);
        }
        return std::get<0>(lhs) < std::get<0>(rhs);
    });
}

void board::sort_column_row(std::vector<std::tuple<uint8_t, uint8_t, mark>>& boar) const {
    std::sort(boar.begin(), boar.end(), [](auto& lhs, auto& rhs){
        if (std::get<1>(lhs) == std::get<1>(rhs)) {
            return std::get<0>(lhs) < std::get<0>(rhs);
        }
        return (std::get<1>(lhs) < std::get<1>(rhs));
    });
}

void board::display() const {
    auto copy = board_;
    std::sort(copy.begin(), copy.end(), [](auto& lhs, auto& rhs){
        if (std::get<0>(lhs) == std::get<0>(rhs)) {
            return std::get<1>(lhs) < std::get<1>(rhs);
        }
        return (std::get<0>(lhs) < std::get<0>(rhs));
    });
    auto it = copy.begin();
    for (uint8_t i = 0; i < size_; ++i) {
        for (uint8_t j = 0; j < size_; ++j) {
            if (it != copy.end()) {
                if (std::get<0>(*it) == i && std::get<1>(*it) == j) {
                    std::cout << (std::get<2>(*it) == mark::circle ? "O" : "X") << " ";
                    ++it;
                    continue;
                }
            }
            std::cout << "- ";
        }
        std::cout << "\n";
    }
}
