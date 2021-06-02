#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "board.hpp"

const int initial_depth = 8;

class node {
public:
    node(uint8_t board_size, uint8_t board_marks_to_win, mark mark_to_put, mark win, mark lose);
    node(const board& board, const std::unique_ptr<node>& ptr);
    bool put_mark(uint8_t x, uint8_t y, mark m);
    static void make_tree(std::unique_ptr<node>& start_node, 
                          uint8_t index_x = 0, 
                          uint8_t index_y = 0, 
                          int depth = initial_depth,
                          int alpha = game_lost_,
                          int beta = game_won_);

    static void next_move(std::unique_ptr<node>& ptr);
    static void clear_tree(std::unique_ptr<node>& ptr);
    void display() const { board_.display(); }
    bool game_end() const;

private:
    static void make_subtree(std::unique_ptr<node>& start_node,
                             uint8_t index_x,
                             uint8_t index_y,
                             int depth,
                             int alpha,
                             int beta);

    static auto make_subtree_setup(std::unique_ptr<node>& start_node) -> 
        std::function<void(std::unique_ptr<node>&, int&, int&)>;

    int value_ = 0;
    board board_;
    std::vector<std::unique_ptr<node>> next_nodes_;
    mark mark_to_put_;
    mark mark_to_win_;
    mark mark_to_lose_;
    static const int game_won_ = 1;
    static const int draw_ = 0;
    static const int game_lost_ = -1;
};
