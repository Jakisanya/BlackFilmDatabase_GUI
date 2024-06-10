//
// Created by jorda on 10/06/2024.
//

#ifndef BLACKFILMDATABASE_GUI_2_CUSTOMITEMSELECTIONMODEL_H
#define BLACKFILMDATABASE_GUI_2_CUSTOMITEMSELECTIONMODEL_H


#include <QItemSelectionModel>
#include <QAbstractItemModel>
#include <QObject>
#include <QDebug>

class CustomItemSelectionModel : public QItemSelectionModel {
Q_OBJECT

public:
    explicit CustomItemSelectionModel(QAbstractItemModel* parent = nullptr);
    void select(const QModelIndex &index, QItemSelectionModel::SelectionFlags command) override;
    void select(const QItemSelection &selection, QItemSelectionModel::SelectionFlags command) override;
};

#endif //BLACKFILMDATABASE_GUI_2_CUSTOMITEMSELECTIONMODEL_H
