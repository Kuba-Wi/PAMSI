#pragma once

#include <qqml.h>
#include <QAbstractTableModel>
#include <memory>
#include "node.hpp"

class TicTacModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, [[maybe_unused]] int role) const override;
    QHash<int, QByteArray> roleNames() const override { return {{Qt::DisplayRole, "mark"}}; }
    bool setData(const QModelIndex &index, [[maybe_unused]] const QVariant &value, int role) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

public slots:
    void new_game_computer(int size, int marks_in_row);
    void new_game_user(int size, int marks_in_row);
    void next_move();

signals:
    void gameOver();
    void makeNextMove();

private:
    void compute_next_move();
    bool check_game_over() { return min_max_ptr_->game_end();}

    std::unique_ptr<node> min_max_ptr_;
};
