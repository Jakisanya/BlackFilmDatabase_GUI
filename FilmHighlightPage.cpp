#include "FilmHighlightPage.h"

FilmHighlightPage::FilmHighlightPage() {
    setFixedSize(640, 760);

    mainLayout.addSpacerItem(&sectionGap);

    // Search Button
    backToResultsPageButton.setText("BACK TO SEARCH");
    backToResultsPageButton.setFixedSize(200, 50);
    backToResultsPageButtonLayout.addWidget(&backToResultsPageButton);
    backToResultsPageButtonLayout.setAlignment(Qt::AlignHCenter);
    mainLayout.addLayout(&backToResultsPageButtonLayout);

    mainLayout.addSpacerItem(&sectionGap);

    // Create a label for the image
    imageLabel.setAlignment(Qt::AlignCenter);
    loadImageFromUrl(getPosterUrl(), &imageLabel);

    // Add the image label to the left layout
    leftFilmHighlightContentsVBoxLayout.addWidget(&imageLabel);
    // leftFilmHighlightContentsVBoxLayout.addStretch(); // Add stretch to fill space

    mainLayout.addLayout(&leftFilmHighlightContentsVBoxLayout);

    // Add tableView to the right layout
    tableView.setModel(&model);
    tableView.setSortingEnabled(true);
    // No further selection at the moment
    // tableView.setSelectionMode();
    // tableView.setSelectionBehavior();
    tableView.setWordWrap(true);
    rightFilmHighlightContentsVBoxLayout.addWidget(&tableView);

    mainLayout.addLayout(&rightFilmHighlightContentsVBoxLayout);
    setLayout(&mainLayout);

    QObject::connect(&backToResultsPageButton, &QPushButton::clicked, this,
                     &FilmHighlightPage::onBackToResultsPageButtonClicked);
}

QString FilmHighlightPage::getPosterUrl() const {
    // Get poster URL from query results

}

void FilmHighlightPage::loadImageFromUrl(const QString& url, QLabel* label) {
    manager.setParent(label);

    QObject::connect(&manager, &QNetworkAccessManager::finished, this, [label](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
        }
        reply->deleteLater();
    });
    manager.get(QNetworkRequest(QUrl(url)));
}

void FilmHighlightPage::onBackToResultsPageButtonClicked() {
    emit FilmHighlightPage::backToResultsPageButtonClicked();
}

void FilmHighlightPage::handleQueryResults(const pqxx::result& resultObject) {
    // pass the results object to the model
    originalModel.setQueryResults(resultObject);
    model.transposeModel();

    // Resize each column to fit the content after setting the query results
    tableView.setColumnWidth(0, 80);
    tableView.setColumnWidth(1, 210);

    tableView.resizeRowsToContents();
}