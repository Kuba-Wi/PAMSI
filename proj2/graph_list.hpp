#pragma once
#include <iostream>

struct node {
    size_t index;
    int weight;
    node* next = nullptr;

    node(size_t ind, int w, node* n = nullptr) : index(ind), weight(w), next(n) {}
};

class graph_list {
public:
    graph_list(std::istream& strm);
    graph_list(const graph_list&) = delete;
    graph_list& operator=(const graph_list&) = delete;
    ~graph_list();
    void display_list(std::ostream& strm) const;
    void display_paths() const;
    void find_paths();

private:
    void fill_initial_weights();
    size_t get_cheapest_unvisited_index(bool* visited) const;
    void update_weight_and_prev_node(node* neighbour, size_t node_index, bool* visited);
    bool is_new_path_cheaper(node* neighbour, size_t node_index) const;

    node** list_ = nullptr;
    int* weights_ = nullptr;
    size_t* prev_node_ = nullptr;
    size_t start_node_;
    size_t node_count_;
    size_t edge_count_;
};
