#include "CustomSortFilterProxyModel.h"

CustomSortFilterProxyModel::CustomSortFilterProxyModel(QObject *parent)
        : QSortFilterProxyModel(parent)
{
}

bool CustomSortFilterProxyModel::lessThan(const QModelIndex &left, const QModelIndex &right) const
{
    QVariant leftData = sourceModel()->data(left);
    QVariant rightData = sourceModel()->data(right);

    int column = left.column();

    switch (column) {
        case 0: { // "Title"
            QString leftValue = leftData.toString();
            QString rightValue = rightData.toString();
            return leftValue < rightValue;
        }
        case 1: { // "Year"
            int leftValue = leftData.toInt();
            int rightValue = rightData.toInt();
            return leftValue < rightValue;
        }
        case 5: { // "imdbRating"
            float leftValue = leftData.toFloat();
            float rightValue = rightData.toFloat();
            return leftValue < rightValue;
        }
        case 6: { // "rtRating"
            int leftValue = leftData.toInt();
            int rightValue = rightData.toInt();
            return leftValue < rightValue;
        }
        default: // For other columns, use default comparison
            return QSortFilterProxyModel::lessThan(left, right);
    }
}
