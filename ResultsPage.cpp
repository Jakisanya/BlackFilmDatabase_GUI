#include "ResultsPage.h"

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

    tableView = new QTableView(this);
    model = new MovieTableModel(this);

    tableView->setModel(model);
    tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(tableView);

    setLayout(&mainLayout);

    QObject::connect(&backToSearchPageButton, &QPushButton::clicked, this,
                     &ResultsPage::onBackToSearchPageButtonClicked);
    }

void ResultsPage::onBackToSearchPageButtonClicked() {
    emit ResultsPage::backToSearchPageButtonClicked();
}

void ResultsPage::handleQueryResults(const pqxx::result& resultObject) {
    // pass the results object and split the data into widgets
    model->setQueryResults(resultObject);
}