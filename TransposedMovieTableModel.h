#ifndef BLACKFILMDATABASE_GUI_2_TRANSPOSEDMOVIETABLEMODEL_H
#define BLACKFILMDATABASE_GUI_2_TRANSPOSEDMOVIETABLEMODEL_H

#include <QStandardItemModel>
#include "MovieTableModel.h"
#include <QAbstractTableModel>
#include <pqxx/pqxx>
#include <vector>
#include <QString>
#include <iostream>

class TransposedMovieTableModel : public MovieTableModel {
Q_OBJECT

public:
    explicit TransposedMovieTableModel();
    void initialiseOriginalModel(MovieTableModel* model);
    void transpose();

private:
    MovieTableModel* originalModel;
    std::vector<QString> headers;
    std::vector<std::vector<QString>> allRowData;
    int rows{};
    int cols{};
};

#endif //BLACKFILMDATABASE_GUI_2_TRANSPOSEDMOVIETABLEMODEL_H
