#include "MovieTableModel.h"

MovieTableModel::MovieTableModel() {std::cout << "MovieTableModel instance created." << "\n";};

void MovieTableModel::setQueryResults(const pqxx::result& resultObject) {
    std::cout << "I get into the setQueryResults function." << "\n";
    beginResetModel();
    allRowData.clear();
    headers.clear();

    if (resultObject.empty()) {
        std::cout << "the resultObject is empty..." << "\n";
        endResetModel();
        return;
    }

    headers.reserve(resultObject.columns());
    for (auto col = 0; col < resultObject.columns(); ++col) {
        std::cout << "col: " << col << " ; name: " << resultObject.column_name(col) << "\n";
        headers.push_back(QString::fromStdString(resultObject.column_name(col)));
    }

    allRowData.reserve(resultObject.size());
    for (const auto& row : resultObject) {
        std::vector<QString> singleRowData;
        singleRowData.reserve(resultObject.columns());
        for (auto col = 0; col < resultObject.columns(); ++col) {
            singleRowData.push_back(QString::fromStdString(row[col].c_str()));
        }
        allRowData.push_back(singleRowData);
    }
    endResetModel();
}

int MovieTableModel::rowCount(const QModelIndex& parent) const {
    return static_cast<int>(allRowData.size());
}

int MovieTableModel::columnCount(const QModelIndex& parent) const {
    return static_cast<int>(headers.size());
}

QVariant MovieTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole) {
        return {};
    }
    return allRowData.at(index.row()).at(index.column());
}

QVariant MovieTableModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return {};
    }
    if (orientation == Qt::Horizontal) {
        return headers.at(section);
    }
    return section + 1; // Row number
}