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
#include <QRegularExpression>

class FilmHighlightPage : public QWidget {
Q_OBJECT

public:
    FilmHighlightPage();
    void initialiseOriginalModel();
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
    QTransposeProxyModel transposeProxyModel;
    QNetworkAccessManager manager;
    QLabel imageLabel;
    QLabel plotLabel;
    QString posterUrl;
    QString plot;
    QHBoxLayout plotLayout;
    QScrollArea scrollArea;
    QVBoxLayout pageLayout;
    QWidget scrollWidget;
};


#endif //BLACKFILMDATABASE_GUI_2_FILMHIGHLIGHTPAGE_H
