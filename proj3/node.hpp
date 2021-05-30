#pragma once
#include <memory>
#include <optional>
#include <vector>
#include "board.hpp"

enum class next_move {
    max,
    min
};

class node {
public:
    node(size_t board_size, mark mark_to_put, mark win, mark lose);
    node(const board& board, const std::shared_ptr<node>& ptr);
    bool put_mark(size_t x, size_t y, mark m);
    static void make_tree(std::shared_ptr<node>& start_node, size_t index_x = 0, size_t index_y = 0);
    static void assign_values(std::shared_ptr<node>& start_node);
    static void next_move(std::shared_ptr<node>& ptr);
    static void clear_tree(std::shared_ptr<node>& ptr) {ptr->next_nodes_.clear(); ptr->prev_node_ = nullptr; ptr->value_ = 0;}
    void display() { board_.display(); }
private:

    int value_ = 0;
    board board_;
    std::vector<std::shared_ptr<node>> next_nodes_;
    std::shared_ptr<node> prev_node_;
    mark mark_to_put_;
    mark mark_to_win_;
    mark mark_to_lose_;
};
