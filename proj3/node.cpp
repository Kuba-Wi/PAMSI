#include "node.hpp"

node::node(size_t board_size, mark mark_to_put, mark win, mark lose) : 
    board_(board_size), 
    mark_to_put_(mark_to_put), 
    mark_to_win_(win),
    mark_to_lose_(lose) {}

node::node(const board& board, const std::shared_ptr<node>& ptr) : 
    board_(board),
    mark_to_win_(ptr->mark_to_win_),
    mark_to_lose_(ptr->mark_to_lose_) {
    mark_to_put_ = ptr->mark_to_put_ == mark::circle ? mark::cross : mark::circle;
}

bool node::put_mark(size_t x, size_t y, mark m) {
    if (board_.put_mark(x, y, m) == error_code::ok) {
        mark_to_put_ = mark_to_put_ == mark::circle ? mark::cross : mark::circle;
        return true;
    }
    return false;
}

void node::make_tree(std::shared_ptr<node>& start_node, size_t index_x, size_t index_y, int depth) {
    if (start_node->board_.check_win_condition(start_node->mark_to_win_)) {
        start_node->value_ = 1;
        return;
    }
    if (start_node->board_.check_win_condition(start_node->mark_to_lose_)) {
        start_node->value_ = -1;
        return;
    }
    if (start_node->board_.mark_count_full()) {
        start_node->value_ = 0;
        return;
    }
    if (depth <= 0) {
        start_node->value_ = 0;
        return;
    }

    auto size = start_node->board_.get_size();
    auto board_copy = start_node->board_;
    error_code error;
    for (size_t i = index_x; i < size; ++i) {
        for (size_t j = index_y; j < size; ++j) {
            error = board_copy.put_mark(i, j, start_node->mark_to_put_);

            if (error == error_code::ok) {
                start_node->next_nodes_.emplace_back(std::make_shared<node>(board_copy, start_node));
                board_copy = start_node->board_;

                make_tree(start_node->next_nodes_.back(), index_x, index_y, depth - 1);
            }
        }
    }
}

void node::assign_values(std::shared_ptr<node>& start_node) {
    bool value_assigned = false;
    int value;
    for (auto& node : start_node->next_nodes_) {
        assign_values(node);
        if (!value_assigned) {
            value = node->value_;
            value_assigned = true;
        } else {
            if (start_node->mark_to_put_ == start_node->mark_to_win_ && node->value_ > value) {
                value = node->value_;
            } else if (start_node->mark_to_put_ == start_node->mark_to_lose_ && node->value_ < value) {
                value = node->value_;
            }
        }
    }
    if (value_assigned) {
        start_node->value_ = value;
    }
}

void node::next_move(std::shared_ptr<node>& ptr) {
    for (const auto& nod : ptr->next_nodes_) {
        if (nod->value_ == 1) {
            ptr = nod;
            return;
        }
    }

    for (const auto& nod : ptr->next_nodes_) {
        if (nod->value_ == 0) {
            ptr = nod;
            return;
        }
    }

    for (const auto& nod : ptr->next_nodes_) {
        if (nod->value_ == -1) {
            ptr = nod;
            return;
        }
    }
}

void node::clear_tree(std::shared_ptr<node>& ptr) {
    ptr->next_nodes_.clear();
    ptr->value_ = 0;
}
