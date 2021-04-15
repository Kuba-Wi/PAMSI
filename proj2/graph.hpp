#pragma once
#include <ostream>

class graph {
public:
    virtual ~graph() = default;
    virtual void display_graph(std::ostream& strm) const = 0;
    virtual void find_paths() = 0;

    void display_result(std::ostream& strm) const;

private:
    void display_path(std::ostream& strm, size_t node_index) const;

protected:
    int* weights_ = nullptr;
    size_t* prev_node_ = nullptr;
    size_t node_count_;
    size_t start_node_;
};
