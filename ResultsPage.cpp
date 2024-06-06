#include "ResultsPage.h"

ResultsPage::ResultsPage() {
    // display the results in widgets and layouts etc.
    setFixedSize(640, 760);

    mainLayout.addSpacerItem(&sectionGap);

    // Search Button
    backToSearchPageButton.setText("BACK TO SEARCH");
    backToSearchPageButton.setFixedSize(200, 50);
    backToSearchPageButtonLayout.addWidget(&backToSearchPageButton);
    backToSearchPageButtonLayout.setAlignment(Qt::AlignHCenter);
    mainLayout.addLayout(&backToSearchPageButtonLayout);

    mainLayout.addSpacerItem(&sectionGap);

    tableView.setModel(&model);
    tableView.setSelectionMode(QAbstractItemView::SingleSelection);
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);

    tableViewLayout.addWidget(&tableView);

    mainLayout.addLayout(&tableViewLayout);
    setLayout(&mainLayout);

    QObject::connect(&backToSearchPageButton, &QPushButton::clicked, this,
                     &ResultsPage::onBackToSearchPageButtonClicked);
}

void ResultsPage::onBackToSearchPageButtonClicked() {
    emit ResultsPage::backToSearchPageButtonClicked();
}

void ResultsPage::handleQueryResults(const pqxx::result& resultObject) {
    // pass the results object and split the data into widgets
    std::cout << "In handleQueryResults function." << "\n";
    model.setQueryResults(resultObject);

    /*
    // Resize each column to fit the content after setting the query results
    for (int col = 0; col < model.columnCount(QModelIndex()); ++col) {
        tableView.resizeColumnToContents(col);
    }
    */
}