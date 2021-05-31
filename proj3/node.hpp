#pragma once
#include <functional>
#include <memory>
#include <vector>
#include "board.hpp"

class node {
public:
    node(size_t board_size, mark mark_to_put, mark win, mark lose);
    node(const board& board, const std::shared_ptr<node>& ptr);
    bool put_mark(size_t x, size_t y, mark m);
    static void make_tree(std::shared_ptr<node>& start_node, size_t index_x = 0, size_t index_y = 0, int depth = 5);
    static void next_move(std::shared_ptr<node>& ptr);
    static void clear_tree(std::shared_ptr<node>& ptr);
    void display() { board_.display(); }
    bool game_end();

private:
    static void make_subtree(std::shared_ptr<node>& start_node,
                      size_t index_x,
                      size_t index_y,
                      int depth,
                      std::function<bool(int, int)>&& compare);

    int value_ = 0;
    board board_;
    std::vector<std::shared_ptr<node>> next_nodes_;
    mark mark_to_put_;
    mark mark_to_win_;
    mark mark_to_lose_;
    static const int game_won_ = 1;
    static const int draw_ = 0;
    static const int game_lost_ = -1;

};
