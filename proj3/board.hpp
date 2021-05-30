#pragma once
#include <memory>
#include <ostream>
#include <tuple>
#include <vector>

enum class mark {
    circle,
    cross
};

enum class error_code {
    ok,
    field_taken,
    size_exceeded,
    out_of_range,
    bad_mark
};

class board {
public:
    board(size_t size) : size_(size) {}
    error_code put_mark(size_t x, size_t y, mark m);
    bool check_win_condition(mark m) const;
    bool mark_count_full() const { return board_.size() == size_ * size_; }
    size_t get_size() const { return size_; }
    size_t get_mark_count() const { return board_.size(); }
    std::pair<size_t, size_t> added_index(const board& other) const;
    bool equal(const board& other) const;
    void display() const;
private:
    bool bad_mark(mark m) const;
    bool check_diagonal_win(const std::vector<std::tuple<size_t, size_t, mark>>& board_part) const;
    bool check_row_column_win(const std::vector<std::tuple<size_t, size_t, mark>>& board_part) const;
    
    size_t size_;
    std::vector<std::tuple<size_t, size_t, mark>> board_;
    size_t circle_count_ = 0;
    size_t cross_count_ = 0;
};
