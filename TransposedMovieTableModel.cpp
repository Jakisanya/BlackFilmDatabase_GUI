#include "TransposedMovieTableModel.h"

TransposedMovieTableModel::TransposedMovieTableModel() :
    originalModel(nullptr) {};

void TransposedMovieTableModel::initialiseOriginalModel(MovieTableModel& model) {
    originalModel = &model;
    rows = originalModel->rowCount(QModelIndex());
    cols = originalModel->columnCount(QModelIndex());
}

void TransposedMovieTableModel::transpose() {
    // set data
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            setData(createIndex(j, i), originalModel->data(createIndex(i, j),
                                                          Qt::DisplayRole));
        }
    }

    // Set the vertical header values
    for (int row = 0; row < cols; ++row) {
        QString header = originalModel->headerData(row, Qt::Vertical, Qt::DisplayRole).toString();
        setHeaderData(row, Qt::Vertical, header);
    }

    // Set the horizontal header values
    setHeaderData(0, Qt::Horizontal, QString("Column 1"));
};

