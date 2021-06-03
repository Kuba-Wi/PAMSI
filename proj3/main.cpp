#include <iostream>
#include "board.hpp"
#include "node.hpp"

int get_depth(const std::unique_ptr<node>& ptr) {
    constexpr int small = 10;
    constexpr int middle = 4 * 4;
    constexpr int large = 5 * 5;
    auto fields_left = ptr->get_board_size() * ptr->get_board_size();
    fields_left -= ptr->get_marks_count();
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

int main() {
    size_t size, marks_in_row;
    std::cout << "Set size and marks in a row: \n";
    std::cin >> size >> marks_in_row;
    auto min_max_ptr = std::make_unique<node>(size, marks_in_row, mark::cross, mark::cross, mark::circle);
    size_t x, y;

    node::make_tree(min_max_ptr, get_depth(min_max_ptr));
    node::next_move(min_max_ptr);
    while (!min_max_ptr->game_end()) {
        min_max_ptr->display();
        std::cout << "\nYour move\n";
        std::cin >> x >> y;
        while (!min_max_ptr->put_mark(x, y, mark::circle)) {
            std::cout << "\nWrong field. Try again\n";
            std::cin >> x >> y;
        }
        min_max_ptr->display();
        std::cout << "\n";
        node::clear_tree(min_max_ptr);
        node::make_tree(min_max_ptr, get_depth(min_max_ptr));
        node::next_move(min_max_ptr);
    }
    min_max_ptr->display();
    std::cout << "Game over.\n";

    return 0;
}
