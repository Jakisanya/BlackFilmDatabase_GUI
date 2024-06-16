#include "ResultsPage.h"

ResultsPage::ResultsPage() {
    // display the results in widgets and layouts etc.
    setFixedSize(1280, 740);
    setStyleSheet("background-color: #292A32;");

    mainLayout.addSpacerItem(&sectionGap);

    // Search Button
    backToSearchPageButton.setText("BACK TO SEARCH");
    backToSearchPageButton.setFixedSize(200, 50);
    backToSearchPageButton.setStyleSheet(
            "QPushButton {"
            "   border: 1.5px solid #6B0E82;" // Border color
            "   border-radius: 8px;"         // Rounded corners
            "   padding: 2px 4px;"           // Padding inside the QLineEdit
            "   background: #ffffff;"        // Background color
            "   font: 14px 'Patrick Hand SC';"
            "   color: #6B0E82;"
            "}"
    );
    backToSearchPageButtonLayout.addWidget(&backToSearchPageButton);
    backToSearchPageButtonLayout.setAlignment(Qt::AlignHCenter);
    mainLayout.addLayout(&backToSearchPageButtonLayout);

    mainLayout.addSpacerItem(&sectionGap);

    proxyModel.setSourceModel(&model);
    tableView.setModel(&proxyModel);
    tableView.setSortingEnabled(true);
    tableView.setSelectionModel(&customItemSelectionModel);
    tableView.setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView.setSelectionMode(QAbstractItemView::SingleSelection);
    tableView.setWordWrap(true);
    tableView.setStyleSheet(
            "QTableView {"
            "    background-color: #ffffff;"
            "    font: 14px 'Patrick Hand SC';"
            "}"
            "QHeaderView::section {"
            "    background-color: #ffffff;"
            "    font: 14px 'Patrick Hand SC';"
            "}"
    );
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

std::string ResultsPage::escapeSingleQuotes(std::string& input) const {
    std::string output;
    for (char ch : input) {
        if (ch == '\'') {
            output += "''";
        } else {
            output += ch;
        }
    }
    return output;
}

[[nodiscard]] QTableView* ResultsPage::getTableView() {
    return &tableView;
};

[[nodiscard]] std::string ResultsPage::buildQueryString(std::string& selectedTitle, int& selectedYear) const {
    selectedTitle = "'" + escapeSingleQuotes(selectedTitle) + "'";
    std::string builtQuery = std::format(
            "SELECT \"Black_Lead_Proportion\", \"Black_Support_Proportion\", \"Black_Cast_Proportion\", \"Title\", "
            "\"Year\", \"Rated\", \"Released\", \"Runtime\", \"Genre\" , \"Director\", \"Writer\", \"Lead_Actors\", "
            "\"Plot\", \"Language\", \"Country\", \"Metascore\", \"imdbRating\", \"imdbVotes\", \"Type\", \"DVD\", "
            "\"BoxOffice\", \"Production\", \"rtRating\", \"Keyword_List\", \"Budget\", \"worldwide_gross\", "
            "\"movie_cast\", \"movie_crew\", \"Supporting_Actors\", \"Total_Awards_Lead_Actors\", "
            "\"Total_Awards_Supporting_Actors\", \"Total_Awards_Movie_Cast\", \"Total_Awards_Director\", "
            "\"Total_Awards_Writer\", \"Total_Awards_Movie_Crew\", \"Total_Awards_Soundtrack_Credits\", \"Poster\" "
            "FROM general.complete_movie_data "
            "WHERE \"Title\" = {} "
            "AND \"Year\"::INTEGER = {};", selectedTitle, selectedYear);
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
    QModelIndex titleIndex = index.sibling(index.row(), 0);
    QModelIndex yearIndex = index.sibling(index.row(), 1);
    std::cout << "title index: row -> " << titleIndex.row() << " col -> " << titleIndex.column() << "\n";
    std::cout << "year index: row -> " << yearIndex.row() << " col -> " << yearIndex.column() << "\n";
    std::string titleText = proxyModel.data(titleIndex, Qt::DisplayRole).toString().toStdString();
    int yearValue = proxyModel.data(yearIndex, Qt::DisplayRole).toString().toInt();
    qDebug() << "titleText (std::string): " << titleText << "\n";
    qDebug() << "yearValue (int): " << yearValue << "\n";
    std::string builtQuery;
    builtQuery = buildQueryString(titleText, yearValue);
    pqxx::result result;
    result = queryDatabase(builtQuery);
    emit titleQueried(result);
};

