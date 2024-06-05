#ifndef BLACKFILMDATABASE_GUI_2_MOVIETABLEMODEL_H
#define BLACKFILMDATABASE_GUI_2_MOVIETABLEMODEL_H

#include <QAbstractTableModel>
#include <pqxx/pqxx>
#include <vector>
#include <QString>

class MovieTableModel : public QAbstractTableModel {
Q_OBJECT

public:
    MovieTableModel();

    void setQueryResults(const pqxx::result& resultObject);

    int rowCount() const;
    int columnCount() const;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

private:
    std::vector<QString> headers;
    std::vector<std::vector<QString>> allRowData;
};


#endif //BLACKFILMDATABASE_GUI_2_MOVIETABLEMODEL_H
