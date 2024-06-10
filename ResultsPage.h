#ifndef BLACKFILMDATABASE_GUI_2_RESULTSPAGE_H
#define BLACKFILMDATABASE_GUI_2_RESULTSPAGE_H

#include <iostream>
#include <QApplication>
#include <QtWidgets>
#include <QWidget>
#include <QtMultimedia>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPaintEvent>
#include <QObject>
#include <QCheckBox>
#include <pqxx/pqxx>
#include "MovieTableModel.h"
#include "CustomSortFilterProxyModel.h"
#include "CustomItemSelectionModel.h"

class ResultsPage : public QWidget {
Q_OBJECT

public:
    ResultsPage();
    [[nodiscard]] QTableView* getTableView();
    [[nodiscard]] std::string buildQueryString(std::string& selectedTitle) const;
    [[nodiscard]] pqxx::result queryDatabase(std::string& queryString) const;

signals:
    void backToSearchPageButtonClicked();
    void titleQueried(pqxx::result& resultObject);

public slots:
    void handleQueryResults(const pqxx::result& resultObject);
    void onBackToSearchPageButtonClicked();
    void onTitleSelected(const QModelIndex& index);

private:
    // initialise the layouts and widgets that I'll need for the results page
    QVBoxLayout mainLayout;
    QHBoxLayout backToSearchPageButtonLayout;
    QPushButton backToSearchPageButton;
    QSpacerItem sectionGap{0, 10};
    QTableView tableView;
    MovieTableModel model;
    CustomSortFilterProxyModel proxyModel;
    CustomItemSelectionModel customItemSelectionModel{&proxyModel};
    QVBoxLayout tableViewLayout;
};



#endif //BLACKFILMDATABASE_GUI_2_RESULTSPAGE_H
