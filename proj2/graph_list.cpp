#include "graph_list.hpp"
#include <limits>

graph_list::graph_list(std::istream& strm) {
    strm >> edge_count_ >> node_count_ >> start_node_;
    list_ = new node*[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        list_[i] = nullptr;
    }

    size_t first_node, second_node;
    int weight;
    for (size_t i = 0; i < edge_count_; ++i) {
        strm >> first_node >> second_node >> weight;

        list_[first_node] = new node{second_node, weight, list_[first_node]};
        list_[second_node] = new node{first_node, weight, list_[second_node]};
    }
}

graph_list::~graph_list() {
    node* ptr = nullptr;
    node* ptr_to_delete = nullptr;
    for (size_t i = 0; i < node_count_; ++i) {
        ptr = list_[i];
        while (ptr) {
            ptr_to_delete = ptr;
            ptr = ptr->next;
            delete ptr_to_delete;
        }
    }
    delete[] list_;
    delete[] weights_;
    delete[] prev_node_;
}

void graph_list::display_list(std::ostream& strm) const {
    node* ptr;
    for (size_t i = 0; i < node_count_; ++i) {
        ptr = list_[i];
        strm << "Node value: " << i << "\n";
        while (ptr) {
            strm << "\t" << ptr->index << " " << ptr->weight << "\n";
            ptr = ptr->next;
        }
    }
}

void graph_list::display_paths() const {
    for (size_t i = 0; i < node_count_; ++i) {
        std::cout << weights_[i] << " ";
    }
    std::cout << "\n";
    for (size_t i = 0; i < node_count_; ++i) {
        std::cout << prev_node_[i] << " ";
    }
    std::cout << "\n";
}

void graph_list::find_paths() {
    prev_node_ = new size_t[node_count_];
    prev_node_[start_node_] = start_node_;
    this->fill_initial_weights();

    bool* visited_nodes = new bool[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        visited_nodes[i] = false;
    }

    size_t node_index = start_node_;
    while (node_index != std::numeric_limits<size_t>::max()) {
        visited_nodes[node_index] = true;
        node* neighbour = list_[node_index];
        while (neighbour) {
            this->update_weight_and_prev_node(neighbour, node_index, visited_nodes);
            neighbour = neighbour->next;
        }
        node_index = this->get_cheapest_unvisited_index(visited_nodes);
    }

    delete[] visited_nodes;
}

void graph_list::fill_initial_weights() {
    weights_ = new int[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        weights_[i] = std::numeric_limits<int>::max();
    }
    weights_[start_node_] = 0;
}

size_t graph_list::get_cheapest_unvisited_index(bool* visited) const {
    size_t node_index = start_node_;
    for (size_t i = 0; i < node_count_; ++i) {
        if (!visited[i]) {
            node_index = i;
        }
    }
    if(visited[node_index]) {
        return std::numeric_limits<size_t>::max();
    }

    for (size_t i = 0; i < node_count_; ++i) {
        if (!visited[i] && weights_[i] < weights_[node_index]) {
            node_index = i;
        }
    }
    return node_index;
}

void graph_list::update_weight_and_prev_node(node* neighbour, size_t node_index, bool* visited) {
    if (!visited[neighbour->index] && is_new_path_cheaper(neighbour, node_index)) {
        weights_[neighbour->index] = weights_[node_index] + neighbour->weight;
        prev_node_[neighbour->index] = node_index;
    }
}

bool graph_list::is_new_path_cheaper(node* neighbour, size_t node_index) const {
    return weights_[node_index] + neighbour->weight < weights_[neighbour->index];
}
