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
    ~graph_list();
    void build_list(std::istream& strm);
    void display_list(std::ostream& strm);

private:
    node** list_ = nullptr;
    size_t start_node_;
    size_t node_count_;
    size_t edge_count_;
};
