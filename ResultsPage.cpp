//
// Created by jorda on 02/06/2024.
//

#include "ResultsPage.h"

ResultsPage::ResultsPage() {
        // display the results in widgets and layouts etc.
        setFixedSize(640, 740);
    }

void ResultsPage::handleQueryResults(const pqxx::result& resultObject) {
    // pass the results object and split the data into widgets
    for (auto row: resultObject)
        std::cout << "row" << "\n";
};
