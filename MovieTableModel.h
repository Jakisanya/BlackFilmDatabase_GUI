#ifndef BLACKFILMDATABASE_GUI_2_MOVIETABLEMODEL_H
#define BLACKFILMDATABASE_GUI_2_MOVIETABLEMODEL_H

#include <QAbstractTableModel>
#include <pqxx/pqxx>
#include <vector>
#include <QString>
#include <iostream>

class MovieTableModel : public QAbstractTableModel {
Q_OBJECT

    MovieTableModel(const MovieTableModel&);

public:
    MovieTableModel();

    void setQueryResults(const pqxx::result& resultObject);

    [[nodiscard]] virtual int rowCount(const QModelIndex& parent) const;
    [[nodiscard]] virtual int columnCount(const QModelIndex& parent) const;

    // role = Qt::DisplayRole for both
    [[nodiscard]] QVariant data(const QModelIndex& index, int role) const override;
    [[nodiscard]] QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

private:
    std::vector<QString> headers;
    std::vector<std::vector<QString>> allRowData;
};


#endif //BLACKFILMDATABASE_GUI_2_MOVIETABLEMODEL_H
