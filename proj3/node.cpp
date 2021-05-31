#include "node.hpp"
#include <functional>
#include <iostream>

node::node(size_t board_size, size_t board_marks_to_win, mark mark_to_put, mark win, mark lose) : 
    board_(board_size, board_marks_to_win), 
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

void node::make_tree(std::shared_ptr<node>& start_node, 
                     size_t index_x, 
                     size_t index_y, 
                     int depth,
                     int alpha,
                     int beta) {

    if (start_node->board_.check_win_condition(start_node->mark_to_win_)) {
        start_node->value_ = game_won_;
        return;
    }
    if (start_node->board_.check_win_condition(start_node->mark_to_lose_)) {
        start_node->value_ = game_lost_;
        return;
    }
    if (start_node->board_.mark_count_full()) {
        start_node->value_ = draw_;
        return;
    }
    if (depth <= 0) {
        start_node->value_ = draw_;
        return;
    }

    make_subtree(start_node, index_x, index_y, depth, alpha, beta);
}

void node::make_subtree(std::shared_ptr<node>& start_node,
                        size_t index_x,
                        size_t index_y, 
                        int depth, 
                        int alpha,
                        int beta) {

    auto size = start_node->board_.get_size();
    auto board_copy = start_node->board_;
    error_code error;
    std::function<void(std::shared_ptr<node>&, int&, int&)> assign_values;
    assign_values = make_subtree_setup(start_node);

    for (size_t i = index_x; i < size; ++i) {
        for (size_t j = index_y; j < size; ++j) {
            error = board_copy.put_mark(i, j, start_node->mark_to_put_);

            if (error == error_code::ok) {
                start_node->next_nodes_.emplace_back(std::make_shared<node>(board_copy, start_node));

                make_tree(start_node->next_nodes_.back(), index_x, index_y, depth - 1, alpha, beta);
                assign_values(start_node, alpha, beta);
                // if (beta <= alpha) {
                //     return;
                // }
                board_copy = start_node->board_;
            }
        }
    }
}

auto node::make_subtree_setup(std::shared_ptr<node>& start_node) -> 
        std::function<void(std::shared_ptr<node>&, int&, int&)> {
    
    if (start_node->mark_to_put_ == start_node->mark_to_win_) {
        start_node->value_ = game_lost_;
        return [](std::shared_ptr<node>& nod, [[maybe_unused]] int& alpha, [[maybe_unused]] int& beta){
            nod->value_ = std::max(nod->next_nodes_.back()->value_, nod->value_);
            alpha = std::max(nod->next_nodes_.back()->value_, alpha);
        };
    } else {
        start_node->value_ = game_won_;
        return [](std::shared_ptr<node>& nod, [[maybe_unused]] int& alpha, [[maybe_unused]] int& beta){
            nod->value_ = std::min(nod->next_nodes_.back()->value_, nod->value_);
            beta = std::min(nod->next_nodes_.back()->value_, beta);
        };
    }
}

void node::next_move(std::shared_ptr<node>& ptr) {
    std::cout << ptr->value_ << ".\n";
    for (const auto& nod : ptr->next_nodes_) {
        if (nod->value_ == game_won_) {
            ptr = nod;
            std::cout << ptr->value_ << ".\n";
            return;
        }
    }

    for (const auto& nod : ptr->next_nodes_) {
        if (nod->value_ == draw_) {
            ptr = nod;
            std::cout << ptr->value_ << ".\n";
            return;
        }
    }

    for (const auto& nod : ptr->next_nodes_) {
        if (nod->value_ == game_lost_) {
            ptr = nod;
            std::cout << ptr->value_ << ".\n";
            return;
        }
    }
}

void node::clear_tree(std::shared_ptr<node>& ptr) {
    ptr->next_nodes_.clear();
    ptr->value_ = 0;
}

bool node::game_end() const {
    return board_.check_win_condition(mark_to_win_) ||
           board_.check_win_condition(mark_to_lose_) ||
           board_.mark_count_full();
}
