//
// Created by jorda on 08/06/2024.
//

#ifndef BLACKFILMDATABASE_GUI_2_FILMHIGHLIGHTPAGE_H
#define BLACKFILMDATABASE_GUI_2_FILMHIGHLIGHTPAGE_H

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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>

class FilmHighlightPage : QWidget {
    Q_OBJECT

public:
    FilmHighlightPage();
    void loadImageFromUrl(const QString& url, QLabel* label);
    QString getPosterUrl() const;

signals:
    void backToResultsPageButtonClicked();
    void titleSelected();

public slots:
    void handleQueryResults(const pqxx::result& resultObject);
    void onBackToResultsPageButtonClicked();

private:
    QVBoxLayout mainLayout;
    QHBoxLayout backToResultsPageButtonLayout;
    QPushButton backToResultsPageButton;
    QHBoxLayout filmHighlightContentsLayout;
    QVBoxLayout leftFilmHighlightContentsVBoxLayout, rightFilmHighlightContentsVBoxLayout;
    QSpacerItem sectionGap{0, 10};
    QTableView tableView;
    MovieTableModel model;
    QNetworkAccessManager manager;
    QLabel imageLabel;
};


#endif //BLACKFILMDATABASE_GUI_2_FILMHIGHLIGHTPAGE_H
