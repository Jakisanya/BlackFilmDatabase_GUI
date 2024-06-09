#include "TransposedMovieTableModel.h"

TransposedMovieTableModel::TransposedMovieTableModel(MovieTableModel& model) :
    originalModel(model),
    rows(originalModel.columnCount(QModelIndex())),
    cols(originalModel.rowCount(QModelIndex()) + 1){
};

void TransposedMovieTableModel::transposeModel() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            setData(createIndex(j, i), originalModel.data(createIndex(i, j),
                                                          Qt::DisplayRole));
        }
    }
};

