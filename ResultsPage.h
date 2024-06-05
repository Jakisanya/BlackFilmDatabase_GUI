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

class ResultsPage : public QWidget {
Q_OBJECT

public:
    ResultsPage();

signals:
    void backToSearchPageButtonClicked();

public slots:
    void handleQueryResults(const pqxx::result& resultObject);
    void onBackToSearchPageButtonClicked();

private:
    // initialise the layouts and widgets that I'll need for the results page
    QVBoxLayout mainLayout;
    QHBoxLayout backToSearchPageButtonLayout;
    QPushButton backToSearchPageButton;
    QSpacerItem sectionGap{0, 10};
    QTableView tableView;
    MovieTableModel model;
    QVBoxLayout tableViewLayout;
};



#endif //BLACKFILMDATABASE_GUI_2_RESULTSPAGE_H
