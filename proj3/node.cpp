#include "node.hpp"
#include <algorithm>
#include <functional>
#include <iostream>

node::node(uint8_t board_size, uint8_t board_marks_to_win, mark mark_to_put, mark win, mark lose) : 
    board_(board_size, board_marks_to_win), 
    mark_to_put_(mark_to_put), 
    mark_to_win_(win),
    mark_to_lose_(lose) {}

node::node(const board& board, const std::unique_ptr<node>& ptr) : 
    board_(board),
    mark_to_win_(ptr->mark_to_win_),
    mark_to_lose_(ptr->mark_to_lose_) {
    mark_to_put_ = ptr->mark_to_put_ == mark::circle ? mark::cross : mark::circle;
}

bool node::put_mark(uint8_t x, uint8_t y, mark m) {
    if (board_.put_mark(x, y, m) == error_code::ok) {
        mark_to_put_ = mark_to_put_ == mark::circle ? mark::cross : mark::circle;
        return true;
    }
    return false;
}

void node::make_tree(std::unique_ptr<node>& start_node, int depth, int alpha, int beta) {
    if (start_node->board_.check_win_condition(start_node->mark_to_win_)) {
        start_node->value_ = game_won_;
        return;
    }
    if (start_node->board_.check_win_condition(start_node->mark_to_lose_)) {
        start_node->value_ = game_lost_;
        return;
    }
    if (start_node->board_.mark_count_full() || depth <= 0) {
        start_node->value_ = start_node->board_.sum_of_distance_from_center(start_node->mark_to_win_);
        start_node->value_ = start_node->value_ > draw_max_ ? draw_max_ : start_node->value_;
        start_node->value_ = start_node->value_ < draw_min_ ? draw_min_ : start_node->value_;
        return;
    }
    make_subtree(start_node, depth, alpha, beta);
}

void node::make_subtree(std::unique_ptr<node>& start_node, int depth, int alpha, int beta) {
    auto size = start_node->board_.get_size();
    auto board_copy = start_node->board_;
    error_code error;
    std::function<void(std::unique_ptr<node>&, int&, int&)> assign_values;
    assign_values = make_subtree_setup(start_node);

    for (uint8_t i = 0; i < size; ++i) {
        for (uint8_t j = 0; j < size; ++j) {
            error = board_copy.put_mark(i, j, start_node->mark_to_put_);

            if (error == error_code::ok) {
                start_node->next_nodes_.emplace_back(std::make_unique<node>(board_copy, start_node));

                make_tree(start_node->next_nodes_.back(), depth - 1, alpha, beta);
                assign_values(start_node, alpha, beta);
                board_copy = start_node->board_;
                if (start_node->next_nodes_.back()) {
                    start_node->next_nodes_.back()->next_nodes_.clear();
                }
                if (beta <= alpha) {
                    if (start_node->mark_to_put_ == start_node->mark_to_win_)
                        start_node->value_ = game_won_;
                    else 
                        start_node->value_ = game_lost_;
                    return;
                }
            }
        }
    }
}

auto node::make_subtree_setup(std::unique_ptr<node>& start_node) -> 
        std::function<void(std::unique_ptr<node>&, int&, int&)> {
    
    if (start_node->mark_to_put_ == start_node->mark_to_win_) {
        start_node->value_ = game_lost_;
        return [](std::unique_ptr<node>& nod, int& alpha, [[maybe_unused]] int& beta){
            nod->value_ = std::max(nod->next_nodes_.back()->value_, nod->value_);
            alpha = std::max(nod->next_nodes_.back()->value_, alpha);
        };
    } else {
        start_node->value_ = game_won_;
        return [](std::unique_ptr<node>& nod, [[maybe_unused]] int& alpha, int& beta){
            nod->value_ = std::min(nod->next_nodes_.back()->value_, nod->value_);
            beta = std::min(nod->next_nodes_.back()->value_, beta);
        };
    }
}

void node::next_move(std::unique_ptr<node>& ptr) {
    std::cout << ptr->value_ << ".\n";
    auto it = std::max_element(ptr->next_nodes_.begin(), ptr->next_nodes_.end(), [](auto& lhs, auto& rhs){
        return lhs->value_ < rhs->value_;
    });
    if (it != ptr->next_nodes_.end()) {
        ptr = std::move(*it);
    }
}

void node::clear_tree() {
    next_nodes_.clear();
    value_ = 0;
}

bool node::game_end() const {
    return board_.check_win_condition(mark_to_win_) ||
           board_.check_win_condition(mark_to_lose_) ||
           board_.mark_count_full();
}

mark node::get_mark(uint8_t x, uint8_t y) const {
    return board_.get_mark(x, y);
}

int node::get_depth() const {
    constexpr int small = 10;
    constexpr int middle = 4 * 4;
    constexpr int large = 5 * 5;
    auto fields_left = board_.get_size() * board_.get_size();
    fields_left -= board_.get_mark_count();
    if (fields_left <= small) {
        return 10;
    }
    if (fields_left <= middle) {
        return 6;
    }
    if (fields_left <= large) {
        return 5;
    }
    return 4;
}
