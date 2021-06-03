#include "board.hpp"
#include <algorithm>
#include <iostream>
#include <numeric>

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
    std::copy_if(board_.begin(), board_.end(), std::back_inserter(board_copy), [&](const auto& field){
        return std::get<2>(field) == m;
    });

    return check_row_win(board_copy) || check_column_win(board_copy) || check_diagonal_win(board_copy);
}

bool board::bad_mark(mark m) const {
    return (m == mark::circle && circle_count_ > cross_count_) || 
           (m == mark::cross && cross_count_ > circle_count_);
}

bool board::check_diagonal_win(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& board_part) const {
    if (board_part.size() == 0) {
        return false;
    }
    auto board_copy = board_part;
    sort_row_column(board_copy);
    std::vector<std::vector<bool>> full_board;
    fill_full_board(board_copy, full_board);

    return check_diagonal_first_part(full_board) || 
           check_diagonal_second_part(full_board);
}

bool board::check_diagonal_first_part(const std::vector<std::vector<bool>>& full_board) const {
    uint8_t counter = 0;
    uint8_t counter_antydiagonal = 0;
    uint8_t row, column;
    for (int row_start = size_ - 1; row_start >= 0; --row_start) {
        column = 0;
        counter = 0;
        counter_antydiagonal = 0;
        for (row = row_start; row < size_; ++row) {
            if (full_board[row][column]) {
                ++counter;
                if (counter >= marks_to_win_) {
                    return true;
                }
            } else {
                counter = 0;
            }
            if (full_board[size_ - 1 - row][column++]) {
                ++counter_antydiagonal;
                if (counter_antydiagonal >= marks_to_win_) {
                    return true;
                }
            } else {
                counter_antydiagonal = 0;
            }
        }
    }
    return false;
}

bool board::check_diagonal_second_part(const std::vector<std::vector<bool>>& full_board) const {
    
    uint8_t counter = 0;
    uint8_t counter_antydiagonal = 0;
    uint8_t row, column;
    for (uint8_t column_start = 1; column_start < size_; ++column_start) {
        row = 0;
        counter = 0;
        counter_antydiagonal = 0;
        for (column = column_start; column < size_; ++column) {
            if (full_board[row][column]) {
                ++counter;
                if (counter >= marks_to_win_) {
                    return true;
                }
            } else {
                counter = 0;
            }
            if (full_board[size_ - 1 - row++][column]) {
                ++counter_antydiagonal;
                if (counter_antydiagonal >= marks_to_win_) {
                    return true;
                }
            } else {
                counter_antydiagonal = 0;
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

void board::fill_full_board(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& boar, 
                            std::vector<std::vector<bool>>& full_board) const {

    full_board.resize(size_);
    for (auto& row : full_board) {
        row.resize(size_);
    }
    auto it = boar.begin();
    
    for (uint8_t i = 0; i < size_; ++i) {
        for (uint8_t j = 0; j < size_; ++j) {
            if (it == boar.end()) {
                full_board[i][j] = false;
            } else {
                if (i == std::get<0>(*it) && j == std::get<1>(*it)) {
                    full_board[i][j] = true;
                    ++it;
                } else {
                    full_board[i][j] = false;
                }
            }
        }
    }
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

int board::sum_of_distance_from_center(mark m) const {
    return std::accumulate(board_.begin(), board_.end(), 0, [&](int init, auto& field) {
        if (std::get<2>(field) == m) {
            return init - std::abs(std::get<0>(field) - size_ / 2) - std::abs(std::get<1>(field) - size_ / 2);
        }
        return init + std::abs(std::get<0>(field) - size_ / 2) + std::abs(std::get<1>(field) - size_ / 2);
    });
}
