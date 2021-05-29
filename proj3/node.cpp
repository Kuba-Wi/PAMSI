#include "node.hpp"

node::node(size_t board_size, mark mark_to_put, mark mark_to_win) : 
    board_(board_size), 
    mark_to_put_(mark_to_put), 
    mark_to_win_(mark_to_win) {}

node::node(const board& board, const std::shared_ptr<node>& ptr) : board_(board), mark_to_win_(ptr->mark_to_win_) {
    mark_to_put_ = ptr->mark_to_put_ == mark::circle ? mark::cross : mark::circle;
    prev_node_ = ptr;
}

void node::make_tree(std::shared_ptr<node>& start_node,size_t index_x, size_t index_y) {
    if (start_node->board_.mark_count_full()) {
        return;
    }
    auto size = start_node->board_.get_size();
    auto board_copy = start_node->board_;
    for (size_t i = index_x; i < size; ++i) {
        for (size_t j = index_y; j < size; ++j) {
            board_copy.put_mark(i, j, start_node->mark_to_put_);
            if (board_copy.get_size() > start_node->board_.get_size()) {
                start_node->next_nodes_.emplace_back(std::make_shared<node>(board_copy, start_node));
                board_copy = start_node->board_;

                make_tree(start_node->next_nodes_.back(), index_x, index_y + 1);
            }
        }
    }
}
