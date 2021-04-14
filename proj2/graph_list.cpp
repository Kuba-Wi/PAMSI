#include "graph_list.hpp"

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
}

void graph_list::build_list(std::istream& strm) {
    strm >> edge_count_ >> node_count_ >> start_node_;
    list_ = new node*[node_count_];
    for (size_t i = 0; i < node_count_; ++i) {
        list_[i] = nullptr;
    }

    size_t first_node, second_node;
    int weight;
    node* nod;
    for (size_t i = 0; i < edge_count_; ++i) {
        strm >> first_node >> second_node >> weight;

        nod = new node{second_node, weight, list_[first_node]};
        list_[first_node] = nod;

        nod = new node{first_node, weight, list_[second_node]};
        list_[second_node] = nod;
    }
}

void graph_list::display_list(std::ostream& strm) {
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
