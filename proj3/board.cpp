#include "board.hpp"
#include <algorithm>
#include <map>

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
    if (board_.size() < 2 * size_ - 1) {
        return false;
    }

    std::vector<std::tuple<size_t, size_t, mark>> board_copy;
    std::copy_if(board_.begin(),
                 board_.end(), 
                 std::back_inserter<std::vector<std::tuple<size_t, size_t, mark>>>(board_copy), 
                 [&](const auto& field){
        return std::get<2>(field) == m;
    });

    return check_row_column_win(board_copy) || check_diagonal_win(board_copy);
}

bool board::bad_mark(mark m) const {
    return (m == mark::circle && circle_count_ > cross_count_) || 
           (m == mark::cross && cross_count_ > circle_count_);
}

bool board::check_diagonal_win(const std::vector<std::tuple<size_t, size_t, mark>>& board_part) const {
    if (std::count_if(board_part.begin(), board_part.end(), [&](auto& field) {
        return std::get<0>(field) == std::get<1>(field);
    }) == int(size_)) {
        return true;
    }

    return (std::count_if(board_part.begin(), board_part.end(), [&](auto& field) {
        return std::get<0>(field) == size_ - std::get<1>(field) - 1;
    }) == int(size_));
}

bool board::check_row_column_win(const std::vector<std::tuple<size_t, size_t, mark>>& board_part) const {
    std::map<size_t, size_t> map_x;
    std::map<size_t, size_t> map_y;
    for (const auto& field : board_part) {
        ++map_x[std::get<0>(field)];
        ++map_y[std::get<1>(field)];
    }
    if (std::any_of(map_x.begin(), map_x.end(), [&](auto& pair){ return pair.second == size_; })) {
        return true;
    }

    return (std::any_of(map_y.begin(), map_y.end(), [&](auto& pair){ return pair.second == size_; }));
}
