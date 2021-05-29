#pragma once
#include <vector>
#include <memory>
#include "board.hpp"

enum class next_move {
    max,
    min
};

class node {
public:
    node(size_t board_size, mark mark_to_put, mark mark_to_win);
    node(const board& board, const std::shared_ptr<node>& ptr);
    static void make_tree(std::shared_ptr<node>& start_node, size_t index_x = 0, size_t index_y = 0);
private:
    size_t value_;
    board board_;
    std::vector<std::shared_ptr<node>> next_nodes_;
    std::shared_ptr<node> prev_node_;
    mark mark_to_put_;
    mark mark_to_win_;
};
