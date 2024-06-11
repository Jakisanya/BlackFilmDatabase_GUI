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
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrl>
#include <QAbstractTableModel>
#include "MovieTableModel.h"
#include "TransposedMovieTableModel.h"

class FilmHighlightPage : public QWidget {
Q_OBJECT

public:
    FilmHighlightPage();
    void initialiseModels(MovieTableModel&, TransposedMovieTableModel&);
    void loadImageFromUrl(const QString& url, QLabel* label);

signals:
    void backToResultsPageButtonClicked();

public slots:
    void handleQueryResults(pqxx::result& resultObject);
    void onBackToResultsPageButtonClicked();

private:
    QVBoxLayout mainLayout;
    QHBoxLayout backToResultsPageButtonLayout;
    QPushButton backToResultsPageButton;
    QHBoxLayout filmHighlightContentsLayout;
    QVBoxLayout leftFilmHighlightContentsVBoxLayout, rightFilmHighlightContentsVBoxLayout;
    QSpacerItem sectionGap{0, 10};
    QTableView tableView;
    MovieTableModel* originalModel;
    TransposedMovieTableModel* transposedModel;
    QNetworkAccessManager manager;
    QLabel imageLabel;
    QString posterUrl;
};


#endif //BLACKFILMDATABASE_GUI_2_FILMHIGHLIGHTPAGE_H
