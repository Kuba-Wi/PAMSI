#pragma once
#include <iostream>
#include "graph.hpp"

struct node {
    size_t index;
    int weight;
    node* next = nullptr;

    node(size_t ind, int w, node* n = nullptr) : index(ind), weight(w), next(n) {}
};

class graph_list : public graph {
public:
    graph_list(std::istream& strm);
    graph_list(const graph_list&) = delete;
    graph_list& operator=(const graph_list&) = delete;
    ~graph_list() override;
    
    void display_graph(std::ostream& strm) const override;
    void find_paths() override;

private:
    size_t get_cheapest_index(bool* visited) const;
    void update_weight_and_prev_node(node* neighbour, size_t node_index, bool* visited);
    bool is_new_path_cheaper(node* neighbour, size_t node_index) const;

protected:
    graph_list() = default;
    
    node** list_ = nullptr;
    size_t edge_count_;
};
