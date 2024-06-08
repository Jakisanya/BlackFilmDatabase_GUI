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
    tableView.setSelectionMode(QAbstractItemView::SingleSelection);
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);
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
    // pass the results object and split the data into widgets
    model.setQueryResults(resultObject);

    // Resize each column to fit the content after setting the query results
    for (int col = 0; col < model.columnCount(QModelIndex()); ++col) {
        if ((col == 1) || (col == 3) || (col == 5) || (col == 6)) {
            tableView.setColumnWidth(col, 80);
        }
        else tableView.setColumnWidth(col, 300);
    }

    tableView.resizeRowsToContents();

    // Connect the selection changed signal to the slot
    connect(tableView.selectionModel(), &QItemSelectionModel::selectionChanged, this, &ResultsPage::onTitleSelected);
}

[[nodiscard]] std::string ResultsPage::getTitle() const {
    // get title from QTableView row when its film title field is selected

};

[[nodiscard]] std::string ResultsPage::buildQueryString() const {
    std::string builtQuery = std::format(
            "SELECT \"Title\", \"Year\", \"Genre\", \"Rated\", "
            "\"Language\", \"imdbRating\"::DECIMAL, \"rtRating\"::INTEGER "
            "FROM general.complete_movie_data "
            "WHERE \"Title\" = {};", getTitle());
    std::cout << builtQuery << "\n";
    return builtQuery;
}

[[nodiscard]] pqxx::result ResultsPage::queryDatabase() const {
    const std::string connectionString = "host=localhost port=5432 dbname=BFilmDB user=postgres";
    pqxx::connection connectionObject(connectionString.c_str());
    pqxx::work txn{connectionObject};

    // Build the query based on the search parameters
    std::string queryString = buildQueryString();

    // Execute and process some data.
    pqxx::result resultObject{txn.exec(queryString)};
    return resultObject;
}

void ResultsPage::onTitleSelected() { // select title in QTableView; so not a button

};