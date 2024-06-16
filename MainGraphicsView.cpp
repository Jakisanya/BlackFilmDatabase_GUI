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

    // Define icons for normal and hover states
    QIcon normalIcon("C:/Users/jorda/Documents/Figma Project Files/Black Film Database Search/enterApplicationButton.png");
    QIcon hoverIcon("C:/Users/jorda/Documents/Figma Project Files/Black Film Database Search/enterApplicationButton_hover.png"); // Example of a different colored icon

    // Set initial icon
    enterApplicationButton.setIcon(normalIcon);

    // Connect hover events to change icon
    QObject::connect(&enterApplicationButton, &QPushButton::enterEvent, [&enterApplicationButton, &hoverIcon]() {
        enterApplicationButton.setIcon(hoverIcon);
    });

    QObject::connect(&enterApplicationButton, &QPushButton::leaveEvent, [&enterApplicationButton, &normalIcon]() {
        enterApplicationButton.setIcon(normalIcon);
    });

    pixmap.load("C:/Users/jorda/Documents/Figma Project Files/Black Film Database Search/enterApplicationButton.png");
    enterApplicationButtonIcon.addPixmap(pixmap);
    enterApplicationButton.setIcon(enterApplicationButtonIcon);
    enterApplicationButton.setIconSize(pixmap.rect().size());
    enterApplicationButton.setStyleSheet(
            "QPushButton {"
            "    background-color: transparent;"  // Set background color to transparent
            "    border: none;"                    // Remove the border
            "}"
    );
    proxyWidget->setWidget(&enterApplicationButton);
    proxyWidget->setPos(static_cast<float>((this->width() - enterApplicationButton.width())) / 2.0,
                        static_cast<float>((this->height() - enterApplicationButton.height())) / 2.0);

    // Play video
    mediaPlayer.play();

    // Connect button to "Go to Search Page" action
    QObject::connect(&enterApplicationButton, &QPushButton::clicked, this,
                     &MainGraphicsView::showSearchPage);

    QObject::connect(&searchPage, &SearchPage::searchDatabaseButtonClicked, this, [this]() {
        showResultsPage();
        resultsPage.handleQueryResults(searchPage.queryDatabase());
    });

    // Connect the showFilmHighlightPage and handleQueryResults slots to tableView::clicked signal
    QObject::connect(&resultsPage, &ResultsPage::titleQueried, this, [this](pqxx::result& resultObject) {
        filmHighlightPage.handleQueryResults(resultObject);
        showFilmHighlightPage();
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
    QObject::disconnect(&enterApplicationButton, &QPushButton::clicked, nullptr, nullptr);
    QObject::connect(&enterApplicationButton, &QPushButton::clicked, &searchPage, &SearchPage::onSearchDatabaseButtonClicked);

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
        filmHighlightPage.handleQueryResults(resultObject);
        showFilmHighlightPage();
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
    setFixedSize(760, 550);
}