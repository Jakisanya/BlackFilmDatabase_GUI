#ifndef BLACKFILMDATABASE_GUI_2_SEARCHPAGE_H
#define BLACKFILMDATABASE_GUI_2_SEARCHPAGE_H


#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLineEdit>
#include <QDoubleValidator>
#include <QLabel>
#include <QSpacerItem>
#include <QKeyEvent>
#include <QString>
#include <vector>
#include <algorithm>
#include <iostream>
#include <pqxx/pqxx>

class SearchPage : public QWidget {
Q_OBJECT

public:
    SearchPage();

    // Accessors to build search query
    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] int getReleaseYearFromValue() const;
    [[nodiscard]] int getReleaseYearToValue() const;
    [[nodiscard]] std::string getGenre() const;
    [[nodiscard]] std::string getLanguage() const;
    [[nodiscard]] std::string getAgeRating() const;
    [[nodiscard]] float getIMDbRating() const;
    [[nodiscard]] int getRottenTomatoesRating() const;

    /*
public slots:
    void toggleAdvancedSearchSection();
    void addKeyword();
    void removeKeyword();
     */

    [[nodiscard]] std::string buildQueryString() const;
    [[nodiscard]] pqxx::result queryDatabase() const;

signals:
    void searchDatabaseButtonClicked();

public slots:
    void selectButton();
    void onSearchDatabaseButtonClicked();

protected:
    void keyPressEvent(QKeyEvent* event) override;

private:
    QVBoxLayout mainLayout;
    QHBoxLayout searchDatabaseButtonLayout;
    QPushButton searchDatabaseButton;
    QSpacerItem sectionGap{0, 10};

    // Basic Search
    QWidget basicSectionWidget;
    QVBoxLayout basicSectionLayout;
    QHBoxLayout titleLineEditLayout;
    QHBoxLayout releaseYearFieldLayout;
    QGridLayout genreGridLayout, ageRatingGridLayout, languageGridLayout;
    QHBoxLayout imdbRatingLineEditLayout;
    QHBoxLayout rottenTomatoesRatingLineEditLayout;
    QWidget titleWidget;
    QWidget releaseYearWidget;
    QWidget genreWidget;
    QWidget ageRatingWidget;
    QWidget languageWidget;
    QWidget imdbRatingWidget;
    QWidget rottenTomatoesRatingWidget;
    QLineEdit titleLineEdit;
    QLineEdit releaseYearFromLineEdit, releaseYearToLineEdit;
    QLineEdit imdbRatingLineEdit;
    QLineEdit rottenTomatoesRatingLineEdit;
    QDoubleValidator imdbRatingDoubleValidator;
    QDoubleValidator releaseYearFromLineEditIntValidator;
    QDoubleValidator releaseYearToLineEditIntValidator;
    QIntValidator rottenTomatoesRatingIntValidator;
    std::vector<QPushButton*> genrePushButtons;
    std::vector<QPushButton*> ageRatingPushButtons;
    std::vector<QPushButton*> languagePushButtons;
    std::vector<QString> genrePushButtonTexts;
    std::vector<QString> ageRatingPushButtonTexts;
    std::vector<QString> languagePushButtonTexts;
    QPushButton ActionPB, ThrillerPB, DramaPB, SciFiPB, HorrorPB, ComedyPB, RomancePB, CrimePB, FantasyPB, AnimationPB,
            AdventurePB, FamilyPB, WesternPB;
    QPushButton U_PB, PG_PB, PG_THIRTEEN_PB, THIRTEEN_PLUS_PB, SIXTEEN_PLUS_PB, R_PB, EIGHTEEN_PLUS_PB, X_PB, UNRATED_PB;
    QPushButton EnglishPB, FrenchPB, SpanishPB, GermanPB, ItalianPB, JapanesePB, CantonesePB, MandarinPB,
            RussianPB, ArabicPB;
    QString ActionPBTextStr = "ACTION", ThrillerPBTextStr = "THRILLER", DramaPBTextStr = "DRAMA",
            SciFiPBTextStr = "SCI-FI", HorrorPBTextStr = "HORROR", ComedyPBTextStr = "COMEDY",
            RomancePBTextStr = "ROMANCE", CrimePBTextStr = "CRIME", FantasyPBTextStr = "FANTASY",
            AnimationPBTextStr = "ANIMATION", AdventurePBTextStr = "ADVENTURE", FamilyPBTextStr = "FAMILY",
            WesternPBTextStr = "WESTERN";
    QString U_PB_TextStr = "U", PG_PB_TextStr = "PG", PG_THIRTEEN_PB_TextStr = "PG 13", THIRTEEN_PLUS_PB_TextStr = "13+",
            SIXTEEN_PLUS_PB_TextStr = "16+", R_PB_TextStr = "R", EIGHTEEN_PLUS_PB_TextStr = "18+", X_PB_TextStr = "X",
            UNRATED_PB_TextStr = "UNRATED";
    QString EnglishPBTextStr = "ENGLISH", FrenchPBTextStr = "FRENCH", SpanishPBTextStr = "SPANISH",
            GermanPBTextStr = "GERMAN", ItalianPBTextStr = "ITALIAN", JapanesePBTextStr = "JAPANESE",
            CantonesePBTextStr = "CANTONESE", MandarinPBTextStr = "MANDARIN", RussianPBTextStr = "RUSSIAN",
            ArabicPBTextStr = "ARABIC";

    QLabel titleFieldLabel;
    QLabel releaseYearFieldLabel, releaseYearToLabel;
    QLabel genreFieldLabel;
    QLabel ageRatingFieldLabel;
    QLabel languageFieldLabel;
    QLabel imdbRatingFieldLabel;
    QLabel rottenTomatoesRatingFieldLabel;

    // Advanced Search: To be updated
    /*
    QToolButton advancedSectionToggleButton;
    QWidget advancedSectionContentsWidget;
    QVBoxLayout advancedSectionLayout;
    QHBoxLayout advancedSectionToggleButtonLayout;
    QHBoxLayout keywordsLineEditLayout, enteredKeywordsLayout;
    QHBoxLayout actorsLineEditLayout;
    QHBoxLayout directorsLineEditLayout;

    QWidget keywordWidget;
    QWidget actorWidget;
    QWidget directorWidget;
    QLineEdit keywordsLineEdit;
    QLineEdit actorsLineEdit;
    QLineEdit directorsLineEdit;

    QLabel keywordsFieldLabel;
    int enteredKeywordCount{0};
    std::vector<QLabel*> enteredKeywordLabels;
    QLabel enteredKeyword1, enteredKeyword2, enteredKeyword3, enteredKeyword4, enteredKeyword5, enteredKeyword6,
           enteredKeyword7;
    std::vector<QPushButton*> removeKeywordButtons;
    QPushButton removeKeywordButton1, removeKeywordButton2, removeKeywordButton3, removeKeywordButton4,
                removeKeywordButton5, removeKeywordButton6, removeKeywordButton7;
    QLabel actorsFieldLabel;
    QLabel directorsFieldLabel;
    QCheckBox advancedCheckbox;
    */
};



#endif //BLACKFILMDATABASE_GUI_2_SEARCHPAGE_H
