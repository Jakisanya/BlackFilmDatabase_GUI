// --- BlackFilmDatabase_GUI --- \\

#include <iostream>
#include <QApplication>
#include <QtWidgets>
#include <QWidget>
#include <QtCore>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPaintEvent>
#include <QCheckBox>
#include "RangeSlider.cpp"

class SearchPage : public QWidget {
public:
    SearchPage() {
        setFixedSize(640, 1140);

        // Set up RangeSlider value arrays (minimum_value, maximum_value, starting_value)
        std::array<int, 3> rSliderReleaseYearValues = {1950, 2024, 2008};
        std::array<int, 3> rSliderIMDbRatingValues = {0, 10, 6};
        std::array<int, 3> rSliderRTRatingValues = {0, 100, 85};

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

        filmRatingPushButtons.push_back(&U_PB);
        filmRatingPushButtons.push_back(&PG_PB);
        filmRatingPushButtons.push_back(&PG_THIRTEEN_PB);
        filmRatingPushButtons.push_back(&THIRTEEN_PLUS_PB);
        filmRatingPushButtons.push_back(&SIXTEEN_PLUS_PB);
        filmRatingPushButtons.push_back(&R_PB);
        filmRatingPushButtons.push_back(&EIGHTEEN_PLUS_PB);
        filmRatingPushButtons.push_back(&X_PB);
        filmRatingPushButtons.push_back(&UNRATED_PB);

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

        filmRatingPushButtonTexts.push_back(U_PB_TextStr);
        filmRatingPushButtonTexts.push_back(PG_PB_TextStr);
        filmRatingPushButtonTexts.push_back(PG_THIRTEEN_PB_TextStr);
        filmRatingPushButtonTexts.push_back(THIRTEEN_PLUS_PB_TextStr);
        filmRatingPushButtonTexts.push_back(SIXTEEN_PLUS_PB_TextStr);
        filmRatingPushButtonTexts.push_back(R_PB_TextStr);
        filmRatingPushButtonTexts.push_back(EIGHTEEN_PLUS_PB_TextStr);
        filmRatingPushButtonTexts.push_back(X_PB_TextStr);
        filmRatingPushButtonTexts.push_back(UNRATED_PB_TextStr);

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

        // Set up layout line vectors for pushbutton widgets
        // titleFieldLayouts.push_back(&titleFieldLayout0);
        // titleFieldLayouts.push_back(&titleFieldLayout1);

        // Basic Search Fields (Initially disabled)
        mainLayout.addLayout(&basicSectionLayout);

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
        releaseYearFieldLayout.addWidget(&rangeSliderReleaseYear);
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
        filmRatingFieldLabel.setText("Film Rating");
        filmRatingFieldLabel.setAlignment(Qt::AlignHCenter);
        basicSectionLayout.addWidget(&filmRatingFieldLabel);
        basicSectionLayout.addLayout(&filmRatingGridLayout);
        filmRatingGridLayout.setAlignment(Qt::AlignHCenter);
        for (int i{0}; i < filmRatingPushButtons.size(); i++) {
            filmRatingPushButtons[i]->setFixedSize(80, 30);
            filmRatingPushButtons[i]->setText(filmRatingPushButtonTexts[i]);
            if (i <= 4)
                filmRatingGridLayout.addWidget(filmRatingPushButtons[i], i / 5, i % 5);
            if (i > 4)
                filmRatingGridLayout.addWidget(filmRatingPushButtons[i], i / 5, i % 5);
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

        // Create the advanced section header button with down arrow icon
        advancedSectionToggleButton.setIcon(QIcon(
                R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\down_arrow.png)"));
        advancedSectionToggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        advancedSectionToggleButton.setText("Advanced Search");
        mainLayout.addWidget(&advancedSectionToggleButton);
        // Connect the toggle button's clicked signal to the toggleSection slot
        connect(&advancedSectionToggleButton, &QToolButton::clicked, this,
                &SearchPage::toggleAdvancedSearchSection);

        mainLayout.addLayout(&advancedSectionLayout);

        // IMDb Rating
        imdbRatingFieldLabel.setText("IMDb Rating");
        imdbRatingFieldLabel.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addWidget(&imdbRatingFieldLabel);
        // advancedSectionLayout.addWidget(&) // rangeSlider QtQuick.Controls.rangeSlider

        // Rotten Tomatoes Rating
        rottenTomatoesRatingFieldLabel.setText("Rotten Tomatoes Rating");
        rottenTomatoesRatingFieldLabel.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addWidget(&rottenTomatoesRatingFieldLabel);
        // advancedSectionLayout.addWidget(&) // rangeSlider QtQuick.Controls.rangeSlider

        // Keywords
        keywordsFieldLabel.setText("Keywords");
        keywordsFieldLabel.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addWidget(&keywordsFieldLabel);
        keywordsLineEdit.setFixedSize(500, 40);
        keywordsLineEdit.setAlignment(Qt::AlignHCenter);
        keywordsLineEditLayout.addWidget(&keywordsLineEdit);
        advancedSectionLayout.addLayout(&keywordsLineEditLayout);

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

        // Writers
        writersFieldLabel.setText("Writers");
        writersFieldLabel.setAlignment(Qt::AlignHCenter);
        advancedSectionLayout.addWidget(&writersFieldLabel);
        writersLineEdit.setFixedSize(500, 40);
        writersLineEdit.setAlignment(Qt::AlignHCenter);
        writersLineEditLayout.addWidget(&writersLineEdit);
        advancedSectionLayout.addLayout(&writersLineEditLayout);

        mainLayout.addWidget(&advancedSectionContentsWidget);

        // Search Button
        searchButton.setText("SEARCH");
        searchButton.setFixedSize(200, 50);
        mainLayout.addWidget(&searchButton);

        setLayout(&mainLayout);
    }

    // Accessors for search fields
    [[nodiscard]] QString getTitle() const { return titleLineEdit.text(); }
    // [[nodiscard]] int getReleaseYearRange() const { return rangeSliderReleaseYear.value(); }
    [[nodiscard]] QString getGenre() const {
        // checks whether pushbuttons are pressed...
        // if selected/pressed, add button text to output vector
        // return vector output;
    }
    [[nodiscard]] QString getRating() const {
        // checks whether pushbuttons are pressed...
        // if selected/pressed, add button text to output vector
        // return vector output;
    }
    [[nodiscard]] QString getLanguage() const {
        // checks whether pushbuttons are pressed...
        // if selected/pressed, add button text to output vector
        // return vector output;
    }
    // [[nodiscard]] int getIMDBRatingRange() const { return rangeSliderIMDbRating.value(); }
    // [[nodiscard]] int getRottenTomatoesRatingRange() const { return rangeSliderRTRating.value(); }
    [[nodiscard]] QString getKeyword() const { return keywordsLineEdit.text(); }
    [[nodiscard]] QString getActor() const { return actorsLineEdit.text(); }
    [[nodiscard]] QString getDirector() const { return directorsLineEdit.text(); }
    [[nodiscard]] QString getWriter() const { return writersLineEdit.text(); }

public slots:
    void toggleAdvancedSearchSection() {
        // Toggle the visibility of the advanced section layout
        if (advancedSectionLayout.isEnabled())
            advancedSectionLayout.setEnabled(false);
        else
            advancedSectionLayout.setEnabled(true);

        // Change the icon of the toggle button based on the visibility state
        if (advancedSectionLayout.isEnabled())
            advancedSectionToggleButton.setIcon(QIcon(
                    R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\up_arrow.png)"));
        else
            advancedSectionToggleButton.setIcon(QIcon(
                    R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\up_arrow.png)"));
    }

private:
    QVBoxLayout mainLayout;
    QPushButton searchButton;

    // Basic Search
    QWidget basicSectionWidget;
    QVBoxLayout basicSectionLayout;
    QFrame basicSectionBorderFrame, titleWidgetFrame, releaseYearWidgetFrame, genreWidgetFrame, filmRatingWidgetFrame,
            languageWidgetFrame, keywordWidgetFrame, actorWidgetFrame, directorWidgetFrame, writerWidgetFrame;
    QHBoxLayout titleLineEditLayout;
    QHBoxLayout releaseYearFieldLayout;
    QVBoxLayout titleFieldMainLayout;
    QVBoxLayout releaseYearFieldMainLayout;
    QVBoxLayout genreFieldMainLayout;
    QVBoxLayout filmRatingFieldMainLayout;
    QVBoxLayout languageFieldMainLayout;
    std::vector<QHBoxLayout*> titleFieldLayouts;
    std::vector<QHBoxLayout*> releaseYearFieldLayouts;
    std::vector<QHBoxLayout*> genreFieldLayouts;
    std::vector<QHBoxLayout*> filmRatingFieldLayouts;
    std::vector<QHBoxLayout*> languageFieldLayouts;
    QGridLayout genreGridLayout, filmRatingGridLayout, languageGridLayout;
    QWidget titleWidget;
    QWidget releaseYearWidget;
    QWidget genreWidget;
    QWidget filmRatingWidget;
    QWidget languageWidget;
    QLineEdit titleLineEdit;
    std::vector<QPushButton*> genrePushButtons;
    std::vector<QPushButton*> filmRatingPushButtons;
    std::vector<QPushButton*> languagePushButtons;
    std::vector<QString> genrePushButtonTexts;
    std::vector<QString> filmRatingPushButtonTexts;
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
    RangeSlider rangeSliderReleaseYear;
    QLabel titleFieldLabel;
    QLabel releaseYearFieldLabel;
    QLabel genreFieldLabel;
    QLabel filmRatingFieldLabel;
    QLabel languageFieldLabel;

    // Advanced Search

    // Advanced section expand button
    QToolButton advancedSectionToggleButton;
    QWidget advancedSectionContentsWidget;
    QVBoxLayout advancedSectionLayout;

    QHBoxLayout imdbRatingFieldLayout;
    QHBoxLayout rottenTomatoesRatingFieldLayout;
    QHBoxLayout keywordsLineEditLayout;
    QHBoxLayout actorsLineEditLayout;
    QHBoxLayout directorsLineEditLayout;
    QHBoxLayout writersLineEditLayout;
    QWidget imdbRatingWidget;
    QWidget rottenTomatoesRatingWidget;
    QWidget keywordWidget;
    QWidget actorWidget;
    QWidget directorWidget;
    QWidget writerWidget;
    RangeSlider rangeSliderRTRating;
    RangeSlider rangeSliderIMDbRating;
    QLineEdit keywordsLineEdit;
    QLineEdit actorsLineEdit;
    QLineEdit directorsLineEdit;
    QLineEdit writersLineEdit;
    QLabel imdbRatingFieldLabel;
    QLabel rottenTomatoesRatingFieldLabel;
    QLabel keywordsFieldLabel;
    QLabel actorsFieldLabel;
    QLabel directorsFieldLabel;
    QLabel writersFieldLabel;
    QCheckBox advancedCheckbox;
};

class MainGraphicsView : public QGraphicsView {
public:
    MainGraphicsView() {
        setFixedSize(640, 360);
        setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        setBackgroundBrush(QColor(Qt::black));
        setWindowTitle("Black Film Database Search Tool");
        setScene(&scene);

        // Create a video item
        mediaPlayer.setParent(&videoItem);
        mediaPlayer.setVideoOutput(&videoItem);
        mediaPlayer.setSource(QUrl::fromLocalFile("C:/Users/jorda/Videos/BFD_Film_Clips/Black Panther.mp4"));

        // Set the video item's size to match the view size
        videoItem.setSize(this->size());
        // Add video item to the scene
        scene.addItem(&videoItem);

        // Create central button by wrapping it in a QGraphics proxy widget (allows me to manipulate its properties)
        proxyWidget = scene.addWidget(new QWidget);
        searchButton.setText("SEARCH DATABASE");
        searchButton.setFixedSize(200, 50);
        proxyWidget->setWidget(&searchButton);
        proxyWidget->setPos(static_cast<float>((this->width() - searchButton.width())) / 2.0,
                            static_cast<float>((this->height() - searchButton.height())) / 2.0);

        // Play video
        mediaPlayer.play();

        // Connect button to "Go to Search Page" action
        QObject::connect(&searchButton, &QPushButton::clicked, this,
                         &MainGraphicsView::showSearchPage);
    }

public slots:
    void showSearchPage() {
        // Clear the scene
        scene.removeItem(&videoItem);
        scene.removeItem(proxyWidget);

        // Display the search page
        proxyWidget->setWidget(&searchPage);
        scene.addItem(proxyWidget);

        // Connect search button to perform search function
        QObject::connect(&searchButton, &QPushButton::clicked, this, &MainGraphicsView::performSearch);

        // Change page dimensions
        setFixedSize(640, 720);
    }

    void performSearch() {
        // Gather search parameters from the search page
        QString title = searchPage.getTitle();
        // int releaseYearRange = searchPage.getReleaseYearRange();
        QString genre = searchPage.getGenre();
        QString rating = searchPage.getRating();
        QString language = searchPage.getLanguage();
        // int imdbRatingRange = searchPage.getIMDBRatingRange();
        // int rottenTomatoesRatingRange = searchPage.getRottenTomatoesRatingRange();
        QString keyword = searchPage.getKeyword();
        QString actor = searchPage.getActor();
        QString director = searchPage.getDirector();
        QString writer = searchPage.getWriter();

        // Implement the search functionality, query the database, and display results
    }

private:
    QGraphicsScene scene;
    QGraphicsVideoItem videoItem;
    QMediaPlayer mediaPlayer;
    QPushButton searchButton;
    QGraphicsProxyWidget* proxyWidget;
    SearchPage searchPage;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    /*
    app.setStyleSheet(
            QWidget{ background-color: yellow; }
            RangeSlider { background-color: rgba(255,255,255,0); }
    );
    */

    MainGraphicsView view;
    view.show();
    return app.exec();
}