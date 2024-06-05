//
// Created by jorda on 02/06/2024.
//
#include "SearchPage.h"

SearchPage::SearchPage() {
        setFixedSize(640, 740);

        // Create PushButton vectors
        genrePushButtons.push_back(&ActionPB);
        genrePushButtons.push_back(&ThrillerPB);
        genrePushButtons.push_back(&DramaPB);
        genrePushButtons.push_back(&SciFiPB);
        genrePushButtons.push_back(&HorrorPB);
        genrePushButtons.push_back(&ComedyPB);
        genrePushButtons.push_back(&RomancePB);
        genrePushButtons.push_back(&CrimePB);
        genrePushButtons.push_back(&FantasyPB);
        genrePushButtons.push_back(&AnimationPB);
        genrePushButtons.push_back(&AdventurePB);
        genrePushButtons.push_back(&FamilyPB);
        genrePushButtons.push_back(&WesternPB);

        for (QPushButton* button: genrePushButtons) {
            button->setCheckable(true);
            connect(button, &QPushButton::clicked, this, &SearchPage::selectButton);
        }

        ageRatingPushButtons.push_back(&U_PB);
        ageRatingPushButtons.push_back(&PG_PB);
        ageRatingPushButtons.push_back(&PG_THIRTEEN_PB);
        ageRatingPushButtons.push_back(&THIRTEEN_PLUS_PB);
        ageRatingPushButtons.push_back(&SIXTEEN_PLUS_PB);
        ageRatingPushButtons.push_back(&R_PB);
        ageRatingPushButtons.push_back(&EIGHTEEN_PLUS_PB);
        ageRatingPushButtons.push_back(&X_PB);
        ageRatingPushButtons.push_back(&UNRATED_PB);

        for (QPushButton* button: ageRatingPushButtons) {
            button->setCheckable(true);
            connect(button, &QPushButton::clicked, this, &SearchPage::selectButton);
        }

        languagePushButtons.push_back(&EnglishPB);
        languagePushButtons.push_back(&FrenchPB);
        languagePushButtons.push_back(&SpanishPB);
        languagePushButtons.push_back(&GermanPB);
        languagePushButtons.push_back(&ItalianPB);
        languagePushButtons.push_back(&JapanesePB);
        languagePushButtons.push_back(&CantonesePB);
        languagePushButtons.push_back(&MandarinPB);
        languagePushButtons.push_back(&RussianPB);
        languagePushButtons.push_back(&ArabicPB);

        for (QPushButton* button: languagePushButtons) {
            button->setCheckable(true);
            connect(button, &QPushButton::clicked, this, &SearchPage::selectButton);
        }

        // Create Push Button Text Vectors
        genrePushButtonTexts.push_back(ActionPBTextStr);
        genrePushButtonTexts.push_back(ThrillerPBTextStr);
        genrePushButtonTexts.push_back(DramaPBTextStr);
        genrePushButtonTexts.push_back(SciFiPBTextStr);
        genrePushButtonTexts.push_back(HorrorPBTextStr);
        genrePushButtonTexts.push_back(ComedyPBTextStr);
        genrePushButtonTexts.push_back(RomancePBTextStr);
        genrePushButtonTexts.push_back(CrimePBTextStr);
        genrePushButtonTexts.push_back(FantasyPBTextStr);
        genrePushButtonTexts.push_back(AnimationPBTextStr);
        genrePushButtonTexts.push_back(AdventurePBTextStr);
        genrePushButtonTexts.push_back(FamilyPBTextStr);
        genrePushButtonTexts.push_back(WesternPBTextStr);

        ageRatingPushButtonTexts.push_back(U_PB_TextStr);
        ageRatingPushButtonTexts.push_back(PG_PB_TextStr);
        ageRatingPushButtonTexts.push_back(PG_THIRTEEN_PB_TextStr);
        ageRatingPushButtonTexts.push_back(THIRTEEN_PLUS_PB_TextStr);
        ageRatingPushButtonTexts.push_back(SIXTEEN_PLUS_PB_TextStr);
        ageRatingPushButtonTexts.push_back(R_PB_TextStr);
        ageRatingPushButtonTexts.push_back(EIGHTEEN_PLUS_PB_TextStr);
        ageRatingPushButtonTexts.push_back(X_PB_TextStr);
        ageRatingPushButtonTexts.push_back(UNRATED_PB_TextStr);

        languagePushButtonTexts.push_back(EnglishPBTextStr);
        languagePushButtonTexts.push_back(FrenchPBTextStr);
        languagePushButtonTexts.push_back(SpanishPBTextStr);
        languagePushButtonTexts.push_back(GermanPBTextStr);
        languagePushButtonTexts.push_back(ItalianPBTextStr);
        languagePushButtonTexts.push_back(JapanesePBTextStr);
        languagePushButtonTexts.push_back(CantonesePBTextStr);
        languagePushButtonTexts.push_back(MandarinPBTextStr);
        languagePushButtonTexts.push_back(RussianPBTextStr);
        languagePushButtonTexts.push_back(ArabicPBTextStr);

        /*
        enteredKeywordLabels.push_back(&enteredKeyword1);
        enteredKeywordLabels.push_back(&enteredKeyword2);
        enteredKeywordLabels.push_back(&enteredKeyword3);
        enteredKeywordLabels.push_back(&enteredKeyword4);
        enteredKeywordLabels.push_back(&enteredKeyword5);
        enteredKeywordLabels.push_back(&enteredKeyword6);
        enteredKeywordLabels.push_back(&enteredKeyword7);
        removeKeywordButtons.push_back(&removeKeywordButton1);
        removeKeywordButtons.push_back(&removeKeywordButton2);
        removeKeywordButtons.push_back(&removeKeywordButton3);
        removeKeywordButtons.push_back(&removeKeywordButton4);
        removeKeywordButtons.push_back(&removeKeywordButton5);
        removeKeywordButtons.push_back(&removeKeywordButton6);
        removeKeywordButtons.push_back(&removeKeywordButton7);
        */

        mainLayout.addSpacerItem(&sectionGap);

        // Basic Search Fields
        mainLayout.addLayout(&basicSectionLayout);
        basicSectionLayout.setSizeConstraint(QLayout::SetMinAndMaxSize);

        // Title
        titleFieldLabel.setText("Title");
        titleFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&titleFieldLabel);
        titleLineEdit.setAlignment(Qt::AlignHCenter);
        titleLineEdit.setFixedSize(500, 40);
        titleLineEditLayout.addWidget(&titleLineEdit);
        basicSectionLayout.addLayout(&titleLineEditLayout);

        // Release Year
        releaseYearFieldLabel.setText("Release Year");
        releaseYearFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&releaseYearFieldLabel);
        releaseYearFromLabel.setText("From");
        releaseYearFromLabel.setFixedSize(70, 50);
        releaseYearFromLabel.setAlignment(Qt::AlignCenter);
        releaseYearFieldLayout.addWidget(&releaseYearFromLabel);
        releaseYearFromLineEdit.setFixedSize(125, 40);
        releaseYearFromLineEdit.setMaxLength(4);
        releaseYearFromLineEdit.setAlignment(Qt::AlignHCenter);
        releaseYearFieldLayout.addWidget(&releaseYearFromLineEdit);
        releaseYearToLabel.setText("To");
        releaseYearToLabel.setFixedSize(70, 50);
        releaseYearToLabel.setAlignment(Qt::AlignCenter);
        releaseYearFieldLayout.addWidget(&releaseYearToLabel);
        releaseYearToLineEdit.setFixedSize(125, 40);
        releaseYearToLineEdit.setMaxLength(4);
        releaseYearToLineEdit.setAlignment(Qt::AlignHCenter);
        releaseYearFieldLayout.addWidget(&releaseYearToLineEdit);
        releaseYearFieldLayout.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addLayout(&releaseYearFieldLayout);

        // Genre
        genreFieldLabel.setText("Genre");
        genreFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&genreFieldLabel);
        basicSectionLayout.addLayout(&genreGridLayout);
        genreGridLayout.setAlignment(Qt::AlignHCenter);
        for (int i{0}; i < genrePushButtons.size(); i++) {
            genrePushButtons[i]->setFixedSize(80, 30);
            genrePushButtons[i]->setText(genrePushButtonTexts[i]);
            if (i <= 4)
                genreGridLayout.addWidget(genrePushButtons[i], i / 5, i % 5);
            if ((i > 4) && (i <= 9))
                genreGridLayout.addWidget(genrePushButtons[i], i / 5, i % 5);
            if (i > 9)
                genreGridLayout.addWidget(genrePushButtons[i], i / 5, i % 5);
        }

        // Film Rating
        ageRatingFieldLabel.setText("Age Rating");
        ageRatingFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&ageRatingFieldLabel);
        basicSectionLayout.addLayout(&ageRatingGridLayout);
        ageRatingGridLayout.setAlignment(Qt::AlignHCenter);
        for (int i{0}; i < ageRatingPushButtons.size(); i++) {
            ageRatingPushButtons[i]->setFixedSize(80, 30);
            ageRatingPushButtons[i]->setText(ageRatingPushButtonTexts[i]);
            if (i <= 4)
                ageRatingGridLayout.addWidget(ageRatingPushButtons[i], i / 5, i % 5);
            if (i > 4)
                ageRatingGridLayout.addWidget(ageRatingPushButtons[i], i / 5, i % 5);
        }

        // Language
        languageFieldLabel.setText("Language");
        languageFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&languageFieldLabel);
        basicSectionLayout.addLayout(&languageGridLayout);
        languageGridLayout.setAlignment(Qt::AlignCenter);
        for (int i{0}; i < languagePushButtons.size(); i++) {
            languagePushButtons[i]->setFixedSize(80, 30);
            languagePushButtons[i]->setText(languagePushButtonTexts[i]);
            if (i <= 4)
                languageGridLayout.addWidget(languagePushButtons[i], i / 5, i % 5);
            if (i > 4)
                languageGridLayout.addWidget(languagePushButtons[i], i / 5, i % 5);
        }

        // IMDb Rating
        imdbRatingFieldLabel.setText("IMDb Minimum Rating (0.0 - 10.0)");
        imdbRatingFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&imdbRatingFieldLabel);
        basicSectionLayout.addLayout(&imdbRatingLineEditLayout);
        imdbRatingLineEdit.setFixedSize(70, 40);
        imdbRatingLineEdit.setAlignment(Qt::AlignHCenter);
        imdbRatingLineEdit.setMaxLength(4);
        imdbRatingLineEditLayout.addWidget(&imdbRatingLineEdit);

        // Rotten Tomatoes Rating
        rottenTomatoesRatingFieldLabel.setText("Rotten Tomatoes Minimum Rating (0 - 100)");
        rottenTomatoesRatingFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&rottenTomatoesRatingFieldLabel);
        basicSectionLayout.addLayout(&rottenTomatoesRatingLineEditLayout);
        rottenTomatoesRatingLineEdit.setFixedSize(70, 40);
        rottenTomatoesRatingLineEdit.setAlignment(Qt::AlignHCenter);
        rottenTomatoesRatingLineEdit.setMaxLength(3);
        rottenTomatoesRatingLineEditLayout.addWidget(&rottenTomatoesRatingLineEdit);

        mainLayout.addSpacerItem(&sectionGap);

        /*
        // Create the advanced section header button with down arrow icon
        mainLayout.addLayout(&advancedSectionToggleButtonLayout);
        advancedSectionToggleButton.setIcon(QIcon(
                R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\down_arrow.png)"));
        advancedSectionToggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        advancedSectionToggleButton.setText("Advanced Search");
        advancedSectionToggleButton.setFixedSize(120, 40);
        advancedSectionToggleButtonLayout.addWidget(&advancedSectionToggleButton);
        advancedSectionToggleButtonLayout.setAlignment(Qt::AlignHCenter);
        // Connect the toggle button's clicked signal to the toggleSection slot
        connect(&advancedSectionToggleButton, &QToolButton::clicked, this,
                &SearchPage::toggleAdvancedSearchSection);

        mainLayout.addSpacerItem(&sectionGap);
        mainLayout.addLayout(&advancedSectionLayout);

        // Keywords
        keywordsFieldLabel.setText("Keywords");
        keywordsFieldLabel.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addWidget(&keywordsFieldLabel);
        keywordsLineEdit.setFixedSize(500, 40);
        keywordsLineEdit.setAlignment(Qt::AlignHCenter);
        keywordsLineEditLayout.addWidget(&keywordsLineEdit);
        advancedSectionLayout.addLayout(&keywordsLineEditLayout);
        enteredKeywordsLayout.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addLayout(&enteredKeywordsLayout);
        connect(&keywordsLineEdit, &QLineEdit::returnPressed, this, &SearchPage::addKeyword);

        // Actors
        actorsFieldLabel.setText("Actors");
        actorsFieldLabel.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addWidget(&actorsFieldLabel);
        actorsLineEdit.setFixedSize(500, 40);
        actorsLineEdit.setAlignment(Qt::AlignHCenter);
        actorsLineEditLayout.addWidget(&actorsLineEdit);
        advancedSectionLayout.addLayout(&actorsLineEditLayout);

        // Directors
        directorsFieldLabel.setText("Directors");
        directorsFieldLabel.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addWidget(&directorsFieldLabel);
        directorsLineEdit.setFixedSize(500, 40);
        directorsLineEdit.setAlignment(Qt::AlignHCenter);
        directorsLineEditLayout.addWidget(&directorsLineEdit);
        advancedSectionLayout.addLayout(&directorsLineEditLayout);

        */

        mainLayout.addSpacerItem(&sectionGap);

        // Search Button
        searchDatabaseButton.setText("SEARCH");
        searchDatabaseButton.setFixedSize(200, 50);
        searchDatabaseButtonLayout.addWidget(&searchDatabaseButton);
        searchDatabaseButtonLayout.setAlignment(Qt::AlignHCenter);
        mainLayout.addLayout(&searchDatabaseButtonLayout);

        mainLayout.addSpacerItem(&sectionGap);

        setLayout(&mainLayout);

        connect(&searchDatabaseButton, &QPushButton::clicked, this, &SearchPage::onSearchDatabaseButtonClicked);
    }

// KeyPressEvents function
void SearchPage::keyPressEvent(QKeyEvent* event) {
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        // addKeyword();
    } else {
        QWidget::keyPressEvent(event);
    }
}

// Accessors to build search query
[[nodiscard]] std::string SearchPage::getTitle() const {
    std::string inputtedTitle = titleLineEdit.text().toStdString();
    std::transform(inputtedTitle.begin(), inputtedTitle.end(),
                   inputtedTitle.begin(), ::toupper);
    return inputtedTitle;
}

[[nodiscard]] std::string SearchPage::getReleaseYearFromValue() const {
    return releaseYearFromLineEdit.text().toStdString();
}

[[nodiscard]] std::string SearchPage::getReleaseYearToValue() const {
    return releaseYearToLineEdit.text().toStdString();
}

[[nodiscard]] std::string SearchPage::getGenre() const {
    std::vector<std::string> selectedGenres;
    for (QPushButton* genrePB: genrePushButtons) {
        if (genrePB->isChecked()) {
            selectedGenres.push_back("'%" + genrePB->text().toStdString() + "%'");
        }
    }

    std::string selectedGenresFormatted;
    for (int i{0}; i < selectedGenres.size(); i++) {
        std::transform(selectedGenres[i].begin(), selectedGenres[i].end(), selectedGenres[i].begin(), ::toupper);
        if (i == 0) {
            selectedGenresFormatted += selectedGenres[i];
        }
        if (i > 0) {
            selectedGenresFormatted += " OR \"Genre\" LIKE " + selectedGenres[i];
        }
    }
    return selectedGenresFormatted;
}

[[nodiscard]] std::string SearchPage::getLanguage() const {
    std::vector<std::string> selectedLanguages;
    for (QPushButton* languagePB: languagePushButtons) {
        if (languagePB->isChecked()) {
            selectedLanguages.push_back("'%" + languagePB->text().toStdString() + "%'");
        }
    }

    std::string selectedLanguagesFormatted;
    for (int i{0}; i < selectedLanguages.size(); i++) {
        std::transform(selectedLanguages[i].begin(), selectedLanguages[i].end(), selectedLanguages[i].begin(), ::toupper);
        if (i == 0) {
            selectedLanguagesFormatted += selectedLanguages[i];
        }
        if (i > 0) {
            selectedLanguagesFormatted += " OR \"Language\" LIKE " + selectedLanguages[i];
        }
    }
    return selectedLanguagesFormatted;
}

[[nodiscard]] std::string SearchPage::getAgeRating() const {
    std::vector<std::string> selectedAgeRatings;
    for (QPushButton* ageRatingPB: ageRatingPushButtons) {
        if (ageRatingPB->isChecked()) {
            selectedAgeRatings.push_back("'%" + ageRatingPB->text().toStdString() + "%'");
        }
    }

    std::string selectedAgeRatingsFormatted;
    for (int i{0}; i < selectedAgeRatings.size(); i++) {
        std::transform(selectedAgeRatings[i].begin(), selectedAgeRatings[i].end(), selectedAgeRatings[i].begin(), ::toupper);
        if (i == 0) {
            selectedAgeRatingsFormatted += selectedAgeRatings[i];
        }
        if (i > 0) {
            selectedAgeRatingsFormatted += " OR \"Rated\" LIKE " + selectedAgeRatings[i];
        }
    }
    return selectedAgeRatingsFormatted;
}

[[nodiscard]] std::string SearchPage::getIMDbRating() const { return imdbRatingLineEdit.text().toStdString(); }
[[nodiscard]] std::string SearchPage::getRottenTomatoesRating() const { return rottenTomatoesRatingLineEdit.text().toStdString(); }

/*
void SearchPage::toggleAdvancedSearchSection() {
    // Toggle the visibility of the advanced section layout
    if (advancedSectionLayout.isEnabled()) {
        imdbRatingFieldLabel.hide();
        imdbRatingLineEdit.hide();
        rottenTomatoesRatingFieldLabel.hide();
        rottenTomatoesRatingLineEdit.hide();
        keywordsFieldLabel.hide();
        keywordsLineEdit.hide();
        actorsFieldLabel.hide();
        actorsLineEdit.hide();
        directorsFieldLabel.hide();
        directorsLineEdit.hide();
        advancedSectionLayout.setEnabled(false);
    }
    else {
        imdbRatingFieldLabel.show();
        imdbRatingLineEdit.show();
        rottenTomatoesRatingFieldLabel.show();
        rottenTomatoesRatingLineEdit.show();
        keywordsFieldLabel.show();
        keywordsLineEdit.show();
        actorsFieldLabel.show();
        actorsLineEdit.show();
        directorsFieldLabel.show();
        directorsLineEdit.show();
        advancedSectionLayout.setEnabled(true);
    }
    // Change the icon of the toggle button based on the visibility state
    if (advancedSectionLayout.isEnabled())
        advancedSectionToggleButton.setIcon(QIcon(
                R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\up_arrow.png)"));
    else
        advancedSectionToggleButton.setIcon(QIcon(
                R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\down_arrow.png)"));
}

void SearchPage::addKeyword() {
    QString enteredKeywordText = keywordsLineEdit.text().trimmed();
    if (!enteredKeywordText.isEmpty()) {
        enteredKeywordLabels[enteredKeywordCount]->setStyleSheet("border: 1px solid black; padding: 2px; "
                                                                 "margin-right: 5px;");
        enteredKeywordLabels[enteredKeywordCount]->setText(enteredKeywordText);
        enteredKeywordsLayout.addWidget(enteredKeywordLabels[enteredKeywordCount]);

        std::cout << enteredKeywordCount << "\n";
        removeKeywordButtons[enteredKeywordCount]->show();
        removeKeywordButtons[enteredKeywordCount]->setText("x");
        removeKeywordButtons[enteredKeywordCount]->setStyleSheet("padding: 0;");
        enteredKeywordsLayout.addWidget(removeKeywordButtons[enteredKeywordCount]);

        connect(removeKeywordButtons[enteredKeywordCount], &QPushButton::clicked, this,
                &SearchPage::removeKeyword);

        keywordsLineEdit.clear();
        enteredKeywordCount++;
        if (enteredKeywordCount == 7) {
            keywordsLineEdit.setStyleSheet("QLineEdit { background-color: f1f1f1; }");
            keywordsLineEdit.setEnabled(false);
        }
    }
}

void SearchPage::removeKeyword() {
    std::cout << "Incremented keyword count: " << enteredKeywordCount << "\n";
    enteredKeywordCount--;
    std::cout << "Updated keyword count after 1 removal: " << enteredKeywordCount << "\n";
    QPushButton* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton) {
        // Find the index of the clicked button in the removeKeywordButtons array
        int index = -1;
        for (int i = 0; i <= enteredKeywordCount; ++i) {
            if (clickedButton == removeKeywordButtons[i]) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            enteredKeywordLabels[index]->clear();
            enteredKeywordLabels[index]->setStyleSheet("");
            removeKeywordButtons[index]->hide();
            enteredKeywordsLayout.removeWidget(enteredKeywordLabels[index]);

            if (enteredKeywordCount < 7) {
                std::cout << "do i go here?" << "\n";
                keywordsLineEdit.setEnabled(true);
                keywordsLineEdit.setStyleSheet("");
            }
        }
    }
}

 */
[[nodiscard]] std::string SearchPage::buildQueryString() const {
    std::cout << "I reach the SearchPage::buildQueryString function again." << "\n";
    std::string builtQuery = std::format("SELECT COUNT(*) "
               "FROM general.complete_movie_data "
               "WHERE \"Title\" LIKE '{}' "
               "AND \"Year\" BETWEEN '{}' AND '{}' "
               "AND \"Genre\" LIKE {} "
               "AND \"Rated\" LIKE {} "
               "AND \"Language\" LIKE {};", getTitle(), getReleaseYearFromValue(), getReleaseYearToValue(),
                       getGenre(), getAgeRating(), getLanguage());
    std::cout << builtQuery << "\n";
    return builtQuery;
}

[[nodiscard]] pqxx::result SearchPage::queryDatabase() const {
    std::cout << "I reach the SearchPage::queryDatabase() function again." << "\n";
    const std::string connectionString = "host=localhost port=5432 dbname=BFilmDB user=postgres";
    pqxx::connection connectionObject(connectionString.c_str());
    pqxx::work txn{connectionObject};

    // Build the query based on the search parameters
    std::string queryString = buildQueryString();

    // Execute and process some data.
    pqxx::result resultObject{txn.exec(queryString)};
    return resultObject;
}

void SearchPage::onSearchDatabaseButtonClicked() {
    std::cout << "I get to the SearchPage::onSearchDatabaseButtonClicked() again." << "\n";
    pqxx::result queryResults = queryDatabase();
    emit searchDatabaseButtonClicked(queryResults);
};

void SearchPage::selectButton() {
    auto* clickedButton = qobject_cast<QPushButton*>(sender());
    if (clickedButton->isChecked()) {
        // Apply a different style when button is checked
        clickedButton->setStyleSheet("background-color: blue");
    } else {
        // Apply the default style when button is unchecked
        clickedButton->setStyleSheet(""); // Clearing stylesheet to revert to default
    }
};