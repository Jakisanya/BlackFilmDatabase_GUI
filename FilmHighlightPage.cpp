#include "FilmHighlightPage.h"

FilmHighlightPage::FilmHighlightPage()
    : originalModel(nullptr) {

    setFixedSize(760, 740);
    setStyleSheet("background-color: #292A32;");

    // Search Button
    backToResultsPageButton.setText("BACK TO RESULTS");
    backToResultsPageButton.setFixedSize(200, 50);
    backToResultsPageButton.setStyleSheet(
            "QPushButton {"
            "   border: 1.5px solid #6B0E82;" // Border color
            "   border-radius: 8px;"         // Rounded corners
            "   padding: 2px 4px;"           // Padding inside the QLineEdit
            "   background: #ffffff;"        // Background color
            "   font: 14px 'Patrick Hand SC';"
            "   color: #6B0E82;"
            "}"
    );
    backToResultsPageButtonLayout.addWidget(&backToResultsPageButton);
    backToResultsPageButtonLayout.setAlignment(Qt::AlignCenter);
    pageLayout.addLayout(&backToResultsPageButtonLayout);
    pageLayout.addSpacerItem(&sectionGap);

    scrollArea.setWidgetResizable(true); // Allow the scroll area to resize its contents
    QString styleSheet = R"(
            QScrollArea { border: none; }
            QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical,
            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
                    height: 0px;
                    width: 0px;
            }
            QScrollBar:vertical {
                border: 2px solid #292A32;
                background: #292A32;
                width: 20px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:vertical {
                    background: #6B0E82;
                    border-radius: 8px;
                    min-height: 80px;
            }
            QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
                    background: none;
            })";

    scrollArea.setStyleSheet(styleSheet);
    scrollArea.setAlignment(Qt::AlignCenter);
    scrollWidget.setLayout(&mainLayout);
    scrollArea.setWidget(&scrollWidget);
    scrollArea.setFixedSize(738, 650);
    setLayout(&pageLayout);
    pageLayout.addWidget(&scrollArea);
    pageLayout.addSpacerItem(&sectionGap);

    mainLayout.setSizeConstraint(QLayout::SetMinAndMaxSize);

    // Set label as image
    imageLabel.setAlignment(Qt::AlignCenter);
    // Set image size (300x424)
    QSize imageSize;
    imageSize.setWidth(300);
    imageSize.setHeight(424);
    // Set the size of the QLabel to match the poster image size
    imageLabel.setFixedSize(imageSize);

    // Add the image label to the left layout
    leftFilmHighlightContentsVBoxLayout.addWidget(&imageLabel);
    leftFilmHighlightContentsVBoxLayout.setSizeConstraint(QLayout::SetFixedSize);
    filmHighlightContentsLayout.addLayout(&leftFilmHighlightContentsVBoxLayout);

    rightFilmHighlightContentsVBoxLayout.addWidget(&tableView);
    rightFilmHighlightContentsVBoxLayout.setSizeConstraint(QLayout::SetFixedSize);

    filmHighlightContentsLayout.addLayout(&rightFilmHighlightContentsVBoxLayout);
    filmHighlightContentsLayout.setSizeConstraint(QLayout::SetFixedSize);

    mainLayout.addLayout(&filmHighlightContentsLayout);
    mainLayout.addSpacing(10);
    plotLayout.addWidget(&plotLabel);
    mainLayout.addLayout(&plotLayout);
    mainLayout.addStretch(50);

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

    posterUrl = originalModel->data(originalModel->index(0, 36), Qt::DisplayRole).toString();
    loadImageFromUrl(posterUrl, &imageLabel);

    // Set label as plot
    plot = originalModel->data(originalModel->index(0, 12), Qt::DisplayRole).toString();
    // plotLabel.setAlignment(Qt::AlignCenter);
    plotLabel.setText(plot);
    plotLabel.setWordWrap(true);
    plotLabel.setAlignment(Qt::AlignJustify);
    plotLabel.setStyleSheet(
            "QLabel {"
            "font: 16px 'Patrick Hand SC';"
            "color: #ffffff;"
            "}"
    );

    // Create the transpose proxy model and set the source model
    transposeProxyModel.setSourceModel(originalModel);

    // Set QTableView to the transpose proxy model
    tableView.setModel(&transposeProxyModel);
    tableView.verticalScrollBar()->setSingleStep(1);
    tableView.setWordWrap(true);
    tableView.setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    tableView.horizontalHeader()->hide();
    QString styleSheet = R"(
            QTableView {
                background-color: #ffffff;
                border-radius: 8px;
                font: 14px 'Patrick Hand SC';
            }
            QHeaderView::section {
                background-color: #292A32;
                font: 16px 'Patrick Hand SC';
                color: #ffffff;
            }
            QTableView::corner {
                background: #292A32;
            }
            QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical,
            QScrollBar::add-line:vertical, QScrollBar::sub-line:vertical {
                height: 0px;
                width: 0px;
            }
            QScrollBar::left-arrow:horizontal, QScrollBar::right-arrow:horizontal,
            QScrollBar::add-line:horizontal, QScrollBar::sub-line:horizontal {
                height: 0px;
                width: 0px;
            }
            QScrollBar:vertical {
                border: 2px solid #292A32;
                background: #292A32;
                width: 20px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:vertical {
                background: #6B0E82;
                border-radius: 8px;
                min-height: 80px;
            }
            QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {
                background: none;
            }
            QScrollBar:horizontal {
                border: 2px solid #292A32;
                background: #292A32;
                height: 20px;
                margin: 0px 0px 0px 0px;
            }
            QScrollBar::handle:horizontal {
                background: #6B0E82;
                border-radius: 8px;
                min-width: 20px;
            }
            QScrollBar::add-page:horizontal, QScrollBar::sub-page:horizontal {
                background: none;
            }
        )";
    tableView.setStyleSheet(styleSheet);
    tableView.resizeRowsToContents();
    tableView.setColumnWidth(0, 150);

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


