#include "board.hpp"
#include <algorithm>
#include <iostream>
#include <unordered_map>

error_code board::put_mark(size_t x, size_t y, mark m) {
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
    std::vector<std::tuple<size_t, size_t, mark>> board_copy;
    std::copy_if(board_.begin(),
                 board_.end(), 
                 std::back_inserter<std::vector<std::tuple<size_t, size_t, mark>>>(board_copy), 
                 [&](const auto& field){
        return std::get<2>(field) == m;
    });

    return check_row_win(board_copy) || check_column_win(board_copy) || check_diagonal_win(board_copy);
}

std::pair<size_t, size_t> board::added_index(const board& other) const {
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

bool board::check_diagonal_win(const std::vector<std::tuple<size_t, size_t, mark>>& board_part) const {
    if (board_part.size() == 0) {
        return false;
    }
    std::vector<std::tuple<size_t, size_t, mark>> copy;
    std::copy_if(board_part.begin(), 
                 board_part.end(), 
                 std::back_inserter<std::vector<std::tuple<size_t, size_t, mark>>>(copy), 
                 [](auto& field){
        return std::get<0>(field) == std::get<1>(field);
    });
    std::sort(copy.begin(), copy.end(), [](auto& lhs, auto& rhs){
        return std::get<0>(lhs) < std::get<0>(rhs);
    });
    int prev = std::get<0>(copy.front()) - 1;
    size_t counter = 0;
    for (const auto& [x, y, m] : copy) {
        if (int(x) == prev + 1) {
            ++counter;
            if (counter == marks_to_win_) {
                return true;
            }
        } else {
            prev = x - 1;
            counter = 0;
        }
        ++prev;
    }

    copy.clear();
    std::copy_if(board_part.begin(), 
                 board_part.end(), 
                 std::back_inserter<std::vector<std::tuple<size_t, size_t, mark>>>(copy), 
                 [&](auto& field){
        return std::get<0>(field) == size_ - std::get<1>(field) - 1;
    });
    std::sort(copy.begin(), copy.end(), [](auto& lhs, auto& rhs){
        return std::get<0>(lhs) < std::get<0>(rhs);
    });

    prev = std::get<0>(copy.front()) - 1;
    counter = 0;
    for (const auto& [x, y, m] : copy) {
        if (int(x) == prev + 1) {
            ++counter;
            if (counter == marks_to_win_) {
                return true;
            }
        } else {
            prev = x - 1;
            counter = 0;
        }
        ++prev;
    }
    return false;
}

bool board::check_row_win(const std::vector<std::tuple<size_t, size_t, mark>>& board_part) const {
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

bool board::check_column_win(const std::vector<std::tuple<size_t, size_t, mark>>& board_part) const {
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

void board::sort_row_column(std::vector<std::tuple<size_t, size_t, mark>>& boar) const {
    std::sort(boar.begin(), boar.end(), [](auto& lhs, auto& rhs){
        if (std::get<0>(lhs) == std::get<0>(rhs)) {
            return std::get<1>(lhs) < std::get<1>(rhs);
        }
        return std::get<0>(lhs) < std::get<0>(rhs);
    });
}

void board::sort_column_row(std::vector<std::tuple<size_t, size_t, mark>>& boar) const {
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
    for (size_t i = 0; i < size_; ++i) {
        for (size_t j = 0; j < size_; ++j) {
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
