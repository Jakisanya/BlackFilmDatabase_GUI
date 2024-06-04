//
// Created by jorda on 02/06/2024.
//

#include "ResultsPage.h"
#include "MainGraphicsView.h"

ResultsPage::ResultsPage() {
        // display the results in widgets and layouts etc.
        setFixedSize(640, 740);

    mainLayout.addSpacerItem(&sectionGap);

    // Search Button
    backToSearchPageButton.setText("BACK TO SEARCH");
    backToSearchPageButton.setFixedSize(200, 50);
    backToSearchPageButtonLayout.addWidget(&backToSearchPageButton);
    backToSearchPageButtonLayout.setAlignment(Qt::AlignHCenter);
    mainLayout.addLayout(&backToSearchPageButtonLayout);

    mainLayout.addSpacerItem(&sectionGap);

    setLayout(&mainLayout);

    QObject::connect(&backToSearchPageButton, &QPushButton::clicked, this,
                     &ResultsPage::onBackToSearchPageButtonClicked);
    }

void ResultsPage::onBackToSearchPageButtonClicked() {
    emit backToSearchPageButtonClicked();
}

void ResultsPage::handleQueryResults(const pqxx::result& resultObject) {
    // pass the results object and split the data into widgets
    std::cout << "count: " << resultObject.size() << "\n";
    for (auto row: resultObject)
        std::cout << row[2].c_str() << "\n";
}