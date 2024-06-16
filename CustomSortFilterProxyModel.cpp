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

    std::vector<int> textColumns {0};
    std::vector<int> integerColumns {1, 6, 13, 14, 15, 16, 17, 18, 19};
    std::vector<int> doubleColumns {5, 7, 8, 9};
    std::vector<int> bigIntColumns {10, 11, 12};

    if (std::find(textColumns.begin(), textColumns.end(), column) != textColumns.end()) {
        QString leftValue = leftData.toString();
        QString rightValue = rightData.toString();
        return leftValue < rightValue;
    }
    else if (std::find(integerColumns.begin(), integerColumns.end(), column) != integerColumns.end()) {
        int leftValue = leftData.toInt();
        int rightValue = rightData.toInt();
        return leftValue < rightValue;
    }
    else if (std::find(doubleColumns.begin(), doubleColumns.end(), column) != doubleColumns.end()) {
        float leftValue = leftData.toFloat();
        float rightValue = rightData.toFloat();
        return leftValue < rightValue;
    }
    else if (std::find(bigIntColumns.begin(), bigIntColumns.end(), column) != bigIntColumns.end()) {
        unsigned long int leftValue = leftData.toULongLong();
        unsigned long int rightValue = rightData.toULongLong();
        return leftValue < rightValue;
    }
    else {
        return QSortFilterProxyModel::lessThan(left, right);
    }
}
