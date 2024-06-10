#include "CustomItemSelectionModel.h"

#include "CustomItemSelectionModel.h"
#include <QDebug>

CustomItemSelectionModel::CustomItemSelectionModel(QAbstractItemModel* model)
        : QItemSelectionModel(model) {}

void CustomItemSelectionModel::select(const QModelIndex& index, QItemSelectionModel::SelectionFlags command) {
    // Only allow selection of the first column
    if (index.isValid() && index.column() == 0) {
        qDebug() << "Selecting index:" << index;
        QItemSelectionModel::select(index, command);
    } else {
        qDebug() << "Ignoring index:" << index;
    }
}

void CustomItemSelectionModel::select(const QItemSelection& selection, QItemSelectionModel::SelectionFlags command) {
    QItemSelection filteredSelection;
    for (const QItemSelectionRange& range : selection) {
        if (range.isValid()) {
            // Filter the selection to include only cells in the first column
            for (int row = range.top(); row <= range.bottom(); ++row) {
                QModelIndex leftIndex = model()->index(row, 0, range.parent());
                QModelIndex rightIndex = model()->index(row, 0, range.parent());
                filteredSelection.select(leftIndex, rightIndex);
            }
        }
    }

    if (!filteredSelection.isEmpty()) {
        qDebug() << "Selecting range:" << filteredSelection;
        QItemSelectionModel::select(filteredSelection, command);
    } else {
        qDebug() << "Ignoring selection:" << selection;
    }
}
