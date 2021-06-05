#pragma once

#include <qqml.h>
#include <QAbstractTableModel>
#include <memory>
#include "node.hpp"

class TicTacModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override
    {
        if (parent.isValid() || !min_max_ptr_)
            return 0;

        return min_max_ptr_->get_board_size();
    }

    int columnCount(const QModelIndex& parent = QModelIndex()) const override
    {
        if (parent.isValid() || !min_max_ptr_)
            return 0;

        return min_max_ptr_->get_board_size();
    }

    QVariant data(const QModelIndex &index, [[maybe_unused]] int role) const override
    {
        if (!min_max_ptr_) {
            return QVariant{};
        }
        mark m = min_max_ptr_->get_mark(index.row(), index.column());
        if (m == mark::circle) {
            return "O";
        }
        if (m == mark::cross) {
            return "X";
        }
        return QVariant{};
    }

    QHash<int, QByteArray> roleNames() const override
    {
        return {{Qt::DisplayRole, "mark"}};
    }

    bool
    setData(const QModelIndex &index, [[maybe_unused]] const QVariant &value, int role) override
    {
        if (!min_max_ptr_) {
            return false;
        }
        auto mark_put = min_max_ptr_->put_mark(index.row(), index.column(), min_max_ptr_->get_mark_to_put());
        if (mark_put) {
            emit dataChanged(index, index, {role});
            if (check_game_over()) {
                emit gameOver();
            }
            emit makeNextMove();
            return true;
        }
        return false;
    }

    Qt::ItemFlags
    flags(const QModelIndex &index) const override
    {
        if (!index.isValid())
            return Qt::NoItemFlags;

        return Qt::ItemIsEditable;
    }

public slots:
    void new_game_computer(int size, int marks_in_row) {
        this->beginResetModel();
        min_max_ptr_ = std::make_unique<node>(size, marks_in_row, mark::cross, mark::cross, mark::circle);
        compute_next_move();
        if (check_game_over()) {
            emit gameOver();
        }
        this->endResetModel();
    }

    void new_game_user(int size, int marks_in_row) {
        this->beginResetModel();
        min_max_ptr_ = std::make_unique<node>(size, marks_in_row, mark::circle, mark::cross, mark::circle);
        if (check_game_over()) {
            emit gameOver();
        }
        this->endResetModel();
    }

    void next_move() {
        this->beginResetModel();
        compute_next_move();
        if (check_game_over()) {
            emit gameOver();
        }
        this->endResetModel();
    }

signals:
    void gameOver();
    void makeNextMove();

private:
    void compute_next_move() {
        min_max_ptr_->clear_tree();
        node::make_tree(min_max_ptr_, min_max_ptr_->get_depth());
        node::next_move(min_max_ptr_);
    }

    bool check_game_over() {
        return min_max_ptr_->game_end();
    }

    std::unique_ptr<node> min_max_ptr_;
};
