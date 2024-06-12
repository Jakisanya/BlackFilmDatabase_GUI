#include "FilmHighlightPage.h"

FilmHighlightPage::FilmHighlightPage()
    : originalModel(nullptr) {
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

void FilmHighlightPage::initialiseOriginalModel() {
    // Ensure models are allocated
    if (originalModel == nullptr) {
        originalModel = new MovieTableModel();
    }
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
    // initialise models
    initialiseOriginalModel();
    // pass the results object to the model
    originalModel->setQueryResults(resultObject);
    posterUrl = originalModel->data(originalModel->index(0, 15), Qt::DisplayRole).toString();
    qDebug() << "PosterURL: " << posterUrl << "\n";

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

    // Create the transpose proxy model and set the source model
    transposeProxyModel.setSourceModel(originalModel);

    // Set QTableView to the transpose proxy model
    tableView.setModel(&transposeProxyModel);
    tableView.resizeRowsToContents();
    tableView.setColumnWidth(0, 216);
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


