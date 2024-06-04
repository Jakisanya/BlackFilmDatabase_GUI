//
// Created by jorda on 02/06/2024.
//

#ifndef BLACKFILMDATABASE_GUI_2_MAINGRAPHICSVIEW_H
#define BLACKFILMDATABASE_GUI_2_MAINGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QPushButton>
#include <QMediaPlayer>
#include <QGraphicsProxyWidget>

#include "SearchPage.h"
#include "ResultsPage.h"

class MainGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    MainGraphicsView();
    void setupConnections();

public slots:
    void showSearchPage();
    void showResultsPage();
    void goBackToSearchPageFromResultsPage();

private:
    QGraphicsScene scene;
    QGraphicsVideoItem videoItem;
    QMediaPlayer mediaPlayer;
    QPushButton searchPageButton;
    QGraphicsProxyWidget* proxyWidget;
    SearchPage searchPage;
    ResultsPage resultsPage;
};


#endif //BLACKFILMDATABASE_GUI_2_MAINGRAPHICSVIEW_H
