#include <iostream>
#include "board.hpp"
#include "node.hpp"

void user_move(std::unique_ptr<node>& min_max_ptr) {
    size_t row, column;
    std::cout << "Your move\n";
        std::cin >> row >> column;
        while (!min_max_ptr->put_mark(row, column, mark::circle)) {
            std::cout << "\nWrong field. Try again\n";
            std::cin >> row >> column;
        }
}

void computer_move(std::unique_ptr<node>& min_max_ptr) {
    min_max_ptr->clear_tree();
    node::make_tree(min_max_ptr, min_max_ptr->get_depth());
    node::next_move(min_max_ptr);
}

int main() {
    size_t size, marks_in_row;
    std::cout << "Set size and marks in a row: \n";
    std::cin >> size >> marks_in_row;
    std::cout << "Who has first move?\n";
    std::cout << "0 - You\nOther number - Computer\n";
    int who_starts;
    std::cin >> who_starts;
    std::unique_ptr<node> min_max_ptr;
    if (who_starts == 0) {
        min_max_ptr = std::make_unique<node>(size, marks_in_row, mark::circle, mark::cross, mark::circle);
    } else {
        min_max_ptr = std::make_unique<node>(size, marks_in_row, mark::cross, mark::cross, mark::circle);
        computer_move(min_max_ptr);
    }

    while (!min_max_ptr->game_end()) {
        min_max_ptr->display();
        user_move(min_max_ptr);
        min_max_ptr->display();
        computer_move(min_max_ptr);
    }
    min_max_ptr->display();
    std::cout << "Game over.\n";

    return 0;
}
