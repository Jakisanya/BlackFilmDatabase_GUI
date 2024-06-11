#include "MainGraphicsView.h"
#include "SearchPage.h"
#include "ResultsPage.h"

MainGraphicsView::MainGraphicsView() {
    setFixedSize(640, 360);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setBackgroundBrush(QColor(Qt::black));
    setWindowTitle("Black Film Database Search Tool");
    setScene(&scene);

    // Create a video item
    mediaPlayer.setParent(&videoItem);
    mediaPlayer.setVideoOutput(&videoItem);
    mediaPlayer.setSource(QUrl::fromLocalFile("C:/Users/jorda/Videos/BFD_Film_Clips/Black Panther.mp4"));

    // Set the video item's size to match the view size
    videoItem.setSize(this->size());
    // Add video item to the scene
    scene.addItem(&videoItem);

    // Create central button by wrapping it in a QGraphics proxy widget (allows me to manipulate its properties)
    proxyWidget = scene.addWidget(new QWidget);
    searchPageButton.setText("SEARCH DATABASE");
    searchPageButton.setFixedSize(200, 50);
    proxyWidget->setWidget(&searchPageButton);
    proxyWidget->setPos(static_cast<float>((this->width() - searchPageButton.width())) / 2.0,
                        static_cast<float>((this->height() - searchPageButton.height())) / 2.0);

    // Play video
    mediaPlayer.play();

    // Connect button to "Go to Search Page" action
    QObject::connect(&searchPageButton, &QPushButton::clicked, this,
                     &MainGraphicsView::showSearchPage);

    QObject::connect(&searchPage, &SearchPage::searchDatabaseButtonClicked, this, [this]() {
        showResultsPage();
        resultsPage.handleQueryResults(searchPage.queryDatabase());
    });

    // Connect the showFilmHighlightPage and handleQueryResults slots to tableView::clicked signal
    QObject::connect(&resultsPage, &ResultsPage::titleQueried, this, [this](pqxx::result& resultObject) {
        showFilmHighlightPage();
        filmHighlightPage.handleQueryResults(resultObject);
    });

    // Go back to search page from results page
    QObject::connect(&resultsPage, &ResultsPage::backToSearchPageButtonClicked, this,
                     &MainGraphicsView::goBackToSearchPageFromResultsPage);

    // Go back to results page from film highlight page
    QObject::connect(&filmHighlightPage, &FilmHighlightPage::backToResultsPageButtonClicked, this,
                     &MainGraphicsView::goBackToResultsPageFromFilmHighlightPage);
}

void MainGraphicsView::showSearchPage() {
    // Clear the scene
    scene.removeItem(&videoItem);
    scene.removeItem(proxyWidget);

    // Display the search page
    proxyWidget->setWidget(&searchPage);
    scene.addItem(proxyWidget);

    // Change page dimensions
    setFixedSize(640, 740);
}

void MainGraphicsView::goBackToSearchPageFromResultsPage(){
    // Display the search page
    scene.removeItem(proxyWidget);
    proxyWidget->setWidget(&searchPage);
    scene.addItem(proxyWidget);

    // Reconnect the onSearchDatabaseButtonClicked slot to searchDatabaseButton::clicked signal to prepare to use it again.
    QObject::disconnect(&searchPageButton, &QPushButton::clicked, nullptr, nullptr);
    QObject::connect(&searchPageButton, &QPushButton::clicked, &searchPage, &SearchPage::onSearchDatabaseButtonClicked);

    // Reconnect the showResultsPage and handleQueryResults slots to searchDatabaseButtonClicked signal to prepare to use them again.
    QObject::disconnect(&searchPage, &SearchPage::searchDatabaseButtonClicked, nullptr, nullptr);
    QObject::connect(&searchPage, &SearchPage::searchDatabaseButtonClicked, this, [this]() {
        showResultsPage();
        resultsPage.handleQueryResults(searchPage.queryDatabase());
    });

    // Change page dimensions
    setFixedSize(640, 740);
}

void MainGraphicsView::goBackToResultsPageFromFilmHighlightPage() {
    // Display the search page
    scene.removeItem(proxyWidget);
    proxyWidget->setWidget(&resultsPage);
    scene.addItem(proxyWidget);

    // Reconnect the onTitleSelected slot to tableView::clicked signal to prepare to use it again.
    QObject::disconnect(resultsPage.getTableView(), &QTableView::clicked,nullptr, nullptr);
    QObject::connect(resultsPage.getTableView(), &QTableView::clicked,&resultsPage,
                     &ResultsPage::onTitleSelected);

    // Reconnect the showFilmHighlightPage and handleQueryResults slots to tableView::clicked signal to prepare to use them again.
    QObject::disconnect(&resultsPage, &ResultsPage::titleQueried, nullptr, nullptr);
    QObject::connect(&resultsPage, &ResultsPage::titleQueried, this, [this](pqxx::result& resultObject) {
        showFilmHighlightPage();
        filmHighlightPage.handleQueryResults(resultObject);
    });

    // Change page dimensions
    setFixedSize(1280, 740);
}

void MainGraphicsView::showResultsPage() {
    scene.removeItem(proxyWidget);
    proxyWidget->setWidget(&resultsPage);
    scene.addItem(proxyWidget);

    // Change page dimensions
    setFixedSize(1280, 740);
}

void MainGraphicsView::showFilmHighlightPage() {
    scene.removeItem(proxyWidget);
    proxyWidget->setWidget(&filmHighlightPage);
    scene.addItem(proxyWidget);
    // Change page dimensions
    setFixedSize(760, 640);
}