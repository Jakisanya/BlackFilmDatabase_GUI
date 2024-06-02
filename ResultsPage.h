//
// Created by jorda on 02/06/2024.
//

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

class ResultsPage : public QWidget {
Q_OBJECT
public:
    ResultsPage();

public slots:
    void handleQueryResults(const pqxx::result& resultObject);

private:
    // initialise the layouts and widgets that I'll need for the results page

};



#endif //BLACKFILMDATABASE_GUI_2_RESULTSPAGE_H
