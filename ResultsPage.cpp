#include "ResultsPage.h"

ResultsPage::ResultsPage() {
    // display the results in widgets and layouts etc.
    setFixedSize(1280, 760);

    mainLayout.addSpacerItem(&sectionGap);

    // Search Button
    backToSearchPageButton.setText("BACK TO SEARCH");
    backToSearchPageButton.setFixedSize(200, 50);
    backToSearchPageButtonLayout.addWidget(&backToSearchPageButton);
    backToSearchPageButtonLayout.setAlignment(Qt::AlignHCenter);
    mainLayout.addLayout(&backToSearchPageButtonLayout);

    mainLayout.addSpacerItem(&sectionGap);

    proxyModel.setSourceModel(&model);
    tableView.setModel(&proxyModel);
    tableView.setSortingEnabled(true);
    tableView.setSelectionBehavior(QAbstractItemView::SelectItems);
    tableView.setSelectionMode(QAbstractItemView::SingleSelection);
    tableView.setWordWrap(true);
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
    // pass the results object to the model
    model.setQueryResults(resultObject);

    // Resize each column to fit the content after setting the query results
    for (int col = 0; col < model.columnCount(QModelIndex()); ++col) {
        if ((col == 1) || (col == 3) || (col == 5) || (col == 6)) {
            tableView.setColumnWidth(col, 80);
        }
        else tableView.setColumnWidth(col, 300);
    }

    tableView.resizeRowsToContents();

    // Connect the clicked signal to the slot
    QObject::connect(&tableView, &QTableView::clicked, this, &ResultsPage::onTitleSelected);
}

[[nodiscard]] QTableView* ResultsPage::getTableView() {
    return &tableView;
};

[[nodiscard]] std::string ResultsPage::buildQueryString(std::string& selectedTitle) const {
    selectedTitle = "'" + selectedTitle + "'";
    std::string builtQuery = std::format(
            "SELECT * "
            "FROM general.complete_movie_data "
            "WHERE \"Title\" = {};", selectedTitle);
    std::cout << builtQuery << "\n";
    return builtQuery;
}

[[nodiscard]] pqxx::result ResultsPage::queryDatabase(std::string& queryString) const {
    const std::string connectionString = "host=localhost port=5432 dbname=BFilmDB user=postgres";
    pqxx::connection connectionObject(connectionString.c_str());
    pqxx::work txn{connectionObject};

    // Execute and process some data.
    pqxx::result resultObject{txn.exec(queryString)};
    return resultObject;
}

void ResultsPage::onTitleSelected(const QModelIndex& index) { // select title in QTableView; so not a button
    // search database for title
    std::cout << "title index: row -> " << index.row() << " col -> " << index.column() << "\n";
    std::string itemText = model.data(index, Qt::DisplayRole).toString().toStdString();
    qDebug() << "itemText (std::string): " << itemText << "\n";
    std::string builtQuery;
    builtQuery = buildQueryString(itemText);
    pqxx::result result;
    result = queryDatabase(builtQuery);
    emit titleQueried(result);
};

