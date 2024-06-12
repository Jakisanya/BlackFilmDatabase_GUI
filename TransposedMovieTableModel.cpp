#include "TransposedMovieTableModel.h"

TransposedMovieTableModel::TransposedMovieTableModel() :
    originalModel(nullptr) {};

void TransposedMovieTableModel::initialiseOriginalModel(MovieTableModel* model) {
    originalModel = model;
    rows = originalModel->rowCount(QModelIndex());
    std::cout << "rows: " << rows << "\n";
    cols = originalModel->columnCount(QModelIndex());
    std::cout << "cols: " << cols << "\n";

}

void TransposedMovieTableModel::transpose() {
    // set data
    for (int j = 0; j < cols; ++j) {
        setData(createIndex(j, 0), originalModel->data(createIndex(0, j),Qt::DisplayRole));
        qDebug() << "index data: " << itemData(createIndex(j, 0)) << "\n";
    }
    std::cout << "\n\n";

    // Set the vertical header values
    for (int row = 0; row < cols; ++row) {
        QString header = originalModel->headerData(row, Qt::Vertical, Qt::DisplayRole).toString();
        setHeaderData(row, Qt::Vertical, header);
        qDebug() << MovieTableModel::headerData(row, Qt::Vertical, Qt::DisplayRole) << "\n";
    }

    std::cout << "\n\n";

    // Set the horizontal header values
    setHeaderData(0, Qt::Horizontal, QString("Column 1"));
    qDebug() << MovieTableModel::headerData(0, Qt::Horizontal, Qt::DisplayRole) << "\n";
};

