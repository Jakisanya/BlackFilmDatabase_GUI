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
#include "FilmHighlightPage.h"

class MainGraphicsView : public QGraphicsView {
    Q_OBJECT

public:
    MainGraphicsView();

public slots:
    void showSearchPage();
    void showResultsPage();
    void goBackToSearchPageFromResultsPage();
    void goBackToResultsPageFromFilmHighlightPage();

private:
    QGraphicsScene scene;
    QGraphicsVideoItem videoItem;
    QMediaPlayer mediaPlayer;
    QPushButton searchPageButton;
    QGraphicsProxyWidget* proxyWidget;
    SearchPage searchPage;
    ResultsPage resultsPage;
    FilmHighlightPage filmHighlightPage;
};


#endif //BLACKFILMDATABASE_GUI_2_MAINGRAPHICSVIEW_H
