#include "FilmHighlightPage.h"

FilmHighlightPage::FilmHighlightPage() {
    setFixedSize(760, 640);

    mainLayout.addSpacerItem(&sectionGap);

    // Search Button
    backToResultsPageButton.setText("BACK TO SEARCH");
    backToResultsPageButton.setFixedSize(200, 50);
    backToResultsPageButtonLayout.addWidget(&backToResultsPageButton);
    backToResultsPageButtonLayout.setAlignment(Qt::AlignCenter);
    mainLayout.addLayout(&backToResultsPageButtonLayout);

    mainLayout.addSpacerItem(&sectionGap);

    filmHighlightContentsLayout.addLayout(&leftFilmHighlightContentsVBoxLayout);
    filmHighlightContentsLayout.addLayout(&rightFilmHighlightContentsVBoxLayout);
    mainLayout.addLayout(&filmHighlightContentsLayout);

    setLayout(&mainLayout);

    QObject::connect(&backToResultsPageButton, &QPushButton::clicked, this,
                     &FilmHighlightPage::onBackToResultsPageButtonClicked);
}

void FilmHighlightPage::loadImageFromUrl(const QString& url, QLabel* label) {
    manager.setParent(label);

    QObject::connect(&manager, &QNetworkAccessManager::finished, this, [label](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            label->setPixmap(pixmap.scaled(label->size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            std::cout << "Image successfully loaded into QLabel." << "\n";
        }
        reply->deleteLater();
    });

    manager.get(QNetworkRequest(QUrl(url)));
}

void FilmHighlightPage::onBackToResultsPageButtonClicked() {
    emit FilmHighlightPage::backToResultsPageButtonClicked();
}

void FilmHighlightPage::handleQueryResults(pqxx::result& resultObject) {
    // pass the results object to the model
    originalModel.setQueryResults(resultObject);
    posterUrl = originalModel.data(originalModel.index(0, 15), Qt::DisplayRole).toString();
    qDebug() << "PosterURL: " << posterUrl << "\n";
    transposedModel.setQueryResults(resultObject);
    transposedModel.transposeModel();

    // Resize each column to fit the content after setting the query results
    // tableView.setColumnWidth(0, 80);
    // tableView.setColumnWidth(1, 210);

    tableView.resizeRowsToContents();

    // Create a label for the image
    imageLabel.setAlignment(Qt::AlignCenter);
    // Set image size (300x424)
    QSize imageSize;
    imageSize.setWidth(300);
    imageSize.setHeight(424);
    // Set the size of the QLabel to match the poster image size
    imageLabel.setFixedSize(imageSize);
    loadImageFromUrl(posterUrl, &imageLabel);

    // Add the image label to the left layout
    leftFilmHighlightContentsVBoxLayout.addWidget(&imageLabel);
    leftFilmHighlightContentsVBoxLayout.addStretch(); // Add stretch to fill space

    // Add tableView to the right layout
    tableView.setModel(&transposedModel);
    tableView.setWordWrap(true);
    rightFilmHighlightContentsVBoxLayout.addWidget(&tableView);

    QObject::disconnect(&manager, &QNetworkAccessManager::finished, nullptr, nullptr);
    QObject::connect(&manager, &QNetworkAccessManager::finished, this, [this](QNetworkReply* reply) {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray imageData = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(imageData);
            imageLabel.setPixmap(pixmap.scaled(imageLabel.size(), Qt::KeepAspectRatio, Qt::SmoothTransformation));
            std::cout << "Image successfully loaded into QLabel." << "\n";
        }
        reply->deleteLater();
    });
}