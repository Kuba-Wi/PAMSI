#include <iostream>
#include "board.hpp"
#include "node.hpp"

int main() {
    size_t size, marks_in_row;
    std::cout << "Set size and marks in a row: \n";
    std::cin >> size >> marks_in_row;
    auto min_max_ptr = std::make_unique<node>(size, marks_in_row, mark::cross, mark::cross, mark::circle);
    size_t x, y;

    node::make_tree(min_max_ptr);
    node::next_move(min_max_ptr);
    while (!min_max_ptr->game_end()) {
        min_max_ptr->display();
        std::cout << "\nYour move\n";
        std::cin >> x >> y;
        std::cout << min_max_ptr->put_mark(x, y, mark::circle) << "\n";
        min_max_ptr->display();
        std::cout << "\n";
        node::clear_tree(min_max_ptr);
        node::make_tree(min_max_ptr);
        node::next_move(min_max_ptr);
    }
    min_max_ptr->display();
    std::cout << "Game over.\n";

    return 0;
}
