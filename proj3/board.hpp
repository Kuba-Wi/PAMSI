#pragma once
#include <memory>
#include <tuple>
#include <vector>

enum class mark : uint8_t {
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
    board(uint8_t size, uint8_t marks_to_win) : size_(size), marks_to_win_(marks_to_win) {}
    error_code put_mark(uint8_t x, uint8_t y, mark m);
    bool check_win_condition(mark m) const;
    bool mark_count_full() const { return board_.size() == size_ * size_; }
    uint8_t get_size() const { return size_; }
    uint8_t get_mark_count() const { return board_.size(); }
    void display() const;
    int sum_of_distance_from_center(mark m) const;
private:
    bool bad_mark(mark m) const;
    
    bool check_diagonal_win(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& board_part) const;
    bool check_diagonal_first_part(const std::vector<std::vector<bool>>& full_board) const;
    bool check_diagonal_second_part(const std::vector<std::vector<bool>>& full_board) const;
    void fill_full_board(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& boar, 
                         std::vector<std::vector<bool>>& full_board) const;

    bool check_row_win(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& board_part) const;
    bool check_column_win(const std::vector<std::tuple<uint8_t, uint8_t, mark>>& board_part) const;
    void sort_row_column(std::vector<std::tuple<uint8_t, uint8_t, mark>>& boar) const;
    void sort_column_row(std::vector<std::tuple<uint8_t, uint8_t, mark>>& boar) const;
    
    uint8_t size_;
    uint8_t marks_to_win_;
    std::vector<std::tuple<uint8_t, uint8_t, mark>> board_;
    uint8_t circle_count_ = 0;
    uint8_t cross_count_ = 0;
};
