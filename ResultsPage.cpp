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
    /*
    for (auto row: resultObject)
        std::cout
                // Address column by name.  Use c_str() to get C-style string.
                << row["name"].c_str()
                << " makes "
                // Address column by zero-based index.  Use as<int>() to parse as int.
                << row[1].as<int>()
                << "."
                << std::endl;
    */
};
