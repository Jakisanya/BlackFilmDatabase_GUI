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
// #include <QSlider>
#include <QPaintEvent>
#include <QCheckBox>

class RangeSlider : public QSlider {

public:
    RangeSlider() = default;

    void paintEvent(QPaintEvent *) override {
        QPainter p(this);

        QStyleOptionSlider opt1, opt2; // Separate options for each handle
        initStyleOption(&opt1);
        initStyleOption(&opt2);

        // First handle.
        opt1.sliderPosition = slider.minimum();
        opt1.subControls = QStyle::SC_SliderHandle;
        style()->drawComplexControl(QStyle::CC_Slider, &opt1, &p, this);

        // Second handle.
        opt2.sliderPosition = slider.maximum();
        opt2.subControls = QStyle::SC_SliderHandle;
        style()->drawComplexControl(QStyle::CC_Slider, &opt2, &p, this);
    }

protected:
    QSlider slider;
};

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
        titleFieldLayouts.push_back(&titleFieldLayout0);
        titleFieldLayouts.push_back(&titleFieldLayout1);
        releaseYearFieldLayouts.push_back(&releaseYearFieldLayout0);
        releaseYearFieldLayouts.push_back(&releaseYearFieldLayout1);
        genreFieldLayouts.push_back(&genreFieldLayoutLine0);
        genreFieldLayouts.push_back(&genreFieldLayoutLine1);
        genreFieldLayouts.push_back(&genreFieldLayoutLine2);
        genreFieldLayouts.push_back(&genreFieldLayoutLine3);
        filmRatingFieldLayouts.push_back(&filmRatingFieldLayoutLine0);
        filmRatingFieldLayouts.push_back(&filmRatingFieldLayoutLine1);
        filmRatingFieldLayouts.push_back(&filmRatingFieldLayoutLine2);
        filmRatingFieldLayouts.push_back(&filmRatingFieldLayoutLine3);
        languageFieldLayouts.push_back(&languageFieldLayoutLine0);
        languageFieldLayouts.push_back(&languageFieldLayoutLine1);
        languageFieldLayouts.push_back(&languageFieldLayoutLine2);
        languageFieldLayouts.push_back(&languageFieldLayoutLine3);
        imdbRatingFieldLayouts.push_back(&imdbRatingFieldLayout0);
        imdbRatingFieldLayouts.push_back(&imdbRatingFieldLayout1);
        rottenTomatoesRatingFieldLayouts.push_back(&rottenTomatoesRatingFieldLayout0);
        rottenTomatoesRatingFieldLayouts.push_back(&rottenTomatoesRatingFieldLayout1);
        keywordFieldLayouts.push_back(&keywordFieldLayout0);
        keywordFieldLayouts.push_back(&keywordFieldLayout1);
        actorFieldLayouts.push_back(&actorFieldLayout0);
        actorFieldLayouts.push_back(&actorFieldLayout1);
        directorFieldLayouts.push_back(&directorFieldLayout0);
        directorFieldLayouts.push_back(&directorFieldLayout1);
        writerFieldLayouts.push_back(&writerFieldLayout0);
        writerFieldLayouts.push_back(&writerFieldLayout1);

        // Basic Search Fields (Initially disabled)
        basicSectionLayout.addWidget(createLineEditField(titleFieldMainLayout, titleFieldLayouts,
                                                         "Title", titleFieldLabel,titleEdit,
                                                         titleWidget));
        basicSectionLayout.addWidget(createRangeSliderField(releaseYearFieldMainLayout, releaseYearFieldLayouts,
                                                            "Release Year", releaseYearFieldLabel,
                                                            rSliderReleaseYear, releaseYearWidget,
                                                            rSliderReleaseYearValues));
        basicSectionLayout.addWidget(createMultiButtonField(genreFieldMainLayout, genreFieldLayouts,
                                                            "Genre",genreFieldLabel,
                                                            genrePushButtons,genrePushButtonTexts,
                                                            genreWidget));
        basicSectionLayout.addWidget(createMultiButtonField(filmRatingFieldMainLayout, filmRatingFieldLayouts,
                                                            "Film Rating", filmRatingFieldLabel,
                                                            filmRatingPushButtons,
                                                            filmRatingPushButtonTexts,filmRatingWidget));
        basicSectionLayout.addWidget(createMultiButtonField(languageFieldMainLayout, languageFieldLayouts,
                                                            "Language",languageFieldLabel,
                                                            languagePushButtons,
                                                            languagePushButtonTexts, languageWidget));
        basicSectionWidget.setLayout(&basicSectionLayout);
        mainLayout.addWidget(&basicSectionWidget);

        // Create the advanced section header button with down arrow icon
        advancedSectionToggleButton.setIcon(QIcon(
                R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\down_arrow.png)"));
        advancedSectionToggleButton.setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        advancedSectionToggleButton.setText("Advanced Search");
        mainLayout.addWidget(&advancedSectionToggleButton);

        // Create the contents widget
        advancedSectionContentsWidget.setVisible(false); // Initially hidden
        advancedSectionContentsWidget.setLayout(&advancedSectionContentsLayout);
        mainLayout.addWidget(&advancedSectionContentsWidget);

        // Connect the toggle button's clicked signal to the toggleSection slot
        connect(&advancedSectionToggleButton, &QToolButton::clicked, this,
                &SearchPage::toggleAdvancedSearchSection);

        advancedSectionContentsLayout.addWidget(createRangeSliderField(imdbRatingFieldMainLayout, imdbRatingFieldLayouts,
                                                               "IMDB Rating", imdbRatingFieldLabel,
                                                               rSliderIMDbRating, imdbRatingWidget,
                                                               rSliderIMDbRatingValues));
        advancedSectionContentsLayout.addWidget(createRangeSliderField(rottenTomatoesRatingFieldMainLayout,
                                                               rottenTomatoesRatingFieldLayouts,
                                                               "Rotten Tomatoes Rating",
                                                               rottenTomatoesRatingFieldLabel, rSliderRTRating,
                                                               rottenTomatoesRatingWidget,
                                                               rSliderRTRatingValues));
        advancedSectionContentsLayout.addWidget(createLineEditField(keywordFieldMainLayout, keywordFieldLayouts,
                                                            "Keyword", keywordFieldLabel, keywordEdit,
                                                            keywordWidget));
        advancedSectionContentsLayout.addWidget(createLineEditField(actorFieldMainLayout, actorFieldLayouts,
                                                            "Actor", actorFieldLabel, actorEdit,
                                                            actorWidget));
        advancedSectionContentsLayout.addWidget(createLineEditField(directorFieldMainLayout, directorFieldLayouts,
                                                            "Director", directorFieldLabel, directorEdit,
                                                            directorWidget));
        advancedSectionContentsLayout.addWidget(createLineEditField(writerFieldMainLayout, writerFieldLayouts,
                                                            "Writer", writerFieldLabel, writerEdit, writerWidget));
        mainLayout.addWidget(&advancedSectionContentsWidget);

        // Search Button
        searchButton.setText("SEARCH");
        searchButton.setFixedSize(200, 50);
        mainLayout.addWidget(&searchButton);

        setLayout(&mainLayout);
    }

    QWidget* createLineEditField(QVBoxLayout& mainFieldLayout, std::vector<QHBoxLayout*> fieldLayouts,
                                 const QString &labelText, QLabel &fieldLabel,
                                 QLineEdit &leWidget, QWidget &widgetContainer) {
        fieldLabel.setText(labelText);
        fieldLayouts[0]->addWidget(&fieldLabel);
        fieldLayouts[0]->setAlignment(Qt::AlignHCenter);
        fieldLayouts[1]->setAlignment(Qt::AlignHCenter);

        leWidget.setFixedSize(400, 30);
        leWidget.setAlignment(Qt::AlignCenter);
        fieldLayouts[1]->addWidget(&leWidget);
        widgetContainer.setLayout(&mainFieldLayout);
        mainFieldLayout.addLayout(fieldLayouts[0]);
        mainFieldLayout.addLayout(fieldLayouts[1]);
        return &widgetContainer;
    }

    QWidget* createMultiButtonField(QVBoxLayout& mainFieldLayout, std::vector<QHBoxLayout*> fieldLayouts,
                                    const QString& labelText, QLabel& fieldLabel,
                                    const std::vector<QPushButton*>& pbWidgets,
                                    const std::vector<QString>& pbWidgetTexts, QWidget& widgetContainer) {
        fieldLabel.setText(labelText);
        fieldLayouts[0]->addWidget(&fieldLabel);
        fieldLayouts[0]->setAlignment(Qt::AlignHCenter);
        fieldLayouts[1]->setAlignment(Qt::AlignHCenter);
        fieldLayouts[2]->setAlignment(Qt::AlignHCenter);
        fieldLayouts[3]->setAlignment(Qt::AlignHCenter);

        for (int i{0}; i < pbWidgets.size(); i++) {
            pbWidgets[i]->setFixedSize(80, 30);
            pbWidgets[i]->setText(pbWidgetTexts[i]);
            // pbWidgets[i]->setStyleSheet("QPushButton {border-radius: 10px; background-color: gray}");
            if (i < 5) {
                fieldLayouts[1]->addWidget(pbWidgets[i]);
            }
            if ((i >= 5) && (i < 10)) {
                fieldLayouts[2]->addWidget(pbWidgets[i]);
            }
            if (i >= 10) {
                fieldLayouts[3]->addWidget(pbWidgets[i]);
            }
        }

        widgetContainer.setLayout(&mainFieldLayout);
        mainFieldLayout.addLayout(fieldLayouts[0]);
        mainFieldLayout.addLayout(fieldLayouts[1]);
        mainFieldLayout.addLayout(fieldLayouts[2]);
        mainFieldLayout.addLayout(fieldLayouts[3]);
        return &widgetContainer;
    }

    QWidget* createRangeSliderField(QVBoxLayout& mainFieldLayout, std::vector<QHBoxLayout*>& fieldLayouts,
                                    const QString& labelText, QLabel& fieldLabel, RangeSlider& rsWidget,
                                    QWidget& widgetContainer, std::array<int, 3> sliderValues) {
        fieldLabel.setText(labelText);
        fieldLayouts[0]->addWidget(&fieldLabel);
        fieldLayouts[0]->setAlignment(Qt::AlignHCenter);
        fieldLayouts[1]->setAlignment(Qt::AlignHCenter);
        rsWidget.setFixedSize(400, 30);
        rsWidget.setOrientation(Qt::Horizontal);
        rsWidget.setMinimum(sliderValues[0]); // slider's minimum value
        rsWidget.setMaximum(sliderValues[1]); // slider's maximum value
        rsWidget.setValue(sliderValues[2]);   // slider's starting position
        fieldLayouts[1]->addWidget(&rsWidget);
        widgetContainer.setLayout(&mainFieldLayout);
        mainFieldLayout.addLayout(fieldLayouts[0]);
        mainFieldLayout.addLayout(fieldLayouts[1]);
        return &widgetContainer;
    }

    // Accessors for search fields
    [[nodiscard]] QString getTitle() const { return titleEdit.text(); }
    [[nodiscard]] int getReleaseYearRange() const { return rSliderReleaseYear.value(); }
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
    [[nodiscard]] int getIMDBRatingRange() const { return rSliderIMDbRating.value(); }
    [[nodiscard]] int getRottenTomatoesRatingRange() const { return rSliderRTRating.value(); }
    [[nodiscard]] QString getKeyword() const { return keywordEdit.text(); }
    [[nodiscard]] QString getActor() const { return actorEdit.text(); }
    [[nodiscard]] QString getDirector() const { return directorEdit.text(); }
    [[nodiscard]] QString getWriter() const { return writerEdit.text(); }

public slots:
    void toggleAdvancedSearchSection() {
        // Toggle the visibility of the contents widget
        advancedSectionContentsWidget.setVisible(!advancedSectionContentsWidget.isVisible());
        // Change the icon of the toggle button based on the visibility state
        if (advancedSectionContentsWidget.isVisible())
            advancedSectionToggleButton.setIcon(QIcon(
                    R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\up_arrow.png)"));
        else
            advancedSectionToggleButton.setIcon(QIcon(
                    R"(C:\Users\jorda\CLionProjects\BlackFilmDatabase_GUI_2\up_arrow.png)"));
    }

private:
    QVBoxLayout mainLayout;
    QPushButton searchButton;

    // Advanced section expand button
    QToolButton advancedSectionToggleButton;
    QWidget advancedSectionContentsWidget;
    QVBoxLayout advancedSectionContentsLayout;

    // Basic Search
    QWidget basicSectionWidget;
    QVBoxLayout basicSectionLayout;
    QHBoxLayout titleFieldLayout0, titleFieldLayout1;
    QHBoxLayout releaseYearFieldLayout0, releaseYearFieldLayout1;
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
    QHBoxLayout genreFieldLayoutLine0, genreFieldLayoutLine1, genreFieldLayoutLine2, genreFieldLayoutLine3;
    QHBoxLayout filmRatingFieldLayoutLine0, filmRatingFieldLayoutLine1, filmRatingFieldLayoutLine2, filmRatingFieldLayoutLine3;
    QHBoxLayout languageFieldLayoutLine0, languageFieldLayoutLine1, languageFieldLayoutLine2, languageFieldLayoutLine3;
    QWidget titleWidget;
    QWidget releaseYearWidget;
    QWidget genreWidget;
    QWidget filmRatingWidget;
    QWidget languageWidget;
    QLineEdit titleEdit;
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
    RangeSlider rSliderReleaseYear;
    QLabel titleFieldLabel;
    QLabel releaseYearFieldLabel;
    QLabel genreFieldLabel;
    QLabel filmRatingFieldLabel;
    QLabel languageFieldLabel;

    // Advanced Search
    QVBoxLayout imdbRatingFieldMainLayout;
    QVBoxLayout rottenTomatoesRatingFieldMainLayout;
    QVBoxLayout keywordFieldMainLayout;
    QVBoxLayout actorFieldMainLayout;
    QVBoxLayout directorFieldMainLayout;
    QVBoxLayout writerFieldMainLayout;
    std::vector<QHBoxLayout*> imdbRatingFieldLayouts;
    std::vector<QHBoxLayout*> rottenTomatoesRatingFieldLayouts;
    std::vector<QHBoxLayout*> keywordFieldLayouts;
    std::vector<QHBoxLayout*> actorFieldLayouts;
    std::vector<QHBoxLayout*> directorFieldLayouts;
    std::vector<QHBoxLayout*> writerFieldLayouts;
    QHBoxLayout imdbRatingFieldLayout0, imdbRatingFieldLayout1;
    QHBoxLayout rottenTomatoesRatingFieldLayout0, rottenTomatoesRatingFieldLayout1;
    QHBoxLayout keywordFieldLayout0, keywordFieldLayout1;
    QHBoxLayout actorFieldLayout0, actorFieldLayout1;
    QHBoxLayout directorFieldLayout0, directorFieldLayout1;
    QHBoxLayout writerFieldLayout0, writerFieldLayout1;
    QWidget imdbRatingWidget;
    QWidget rottenTomatoesRatingWidget;
    QWidget keywordWidget;
    QWidget actorWidget;
    QWidget directorWidget;
    QWidget writerWidget;
    RangeSlider rSliderRTRating;
    RangeSlider rSliderIMDbRating;
    QLineEdit keywordEdit;
    QLineEdit actorEdit;
    QLineEdit directorEdit;
    QLineEdit writerEdit;
    QLabel imdbRatingFieldLabel;
    QLabel rottenTomatoesRatingFieldLabel;
    QLabel keywordFieldLabel;
    QLabel actorFieldLabel;
    QLabel directorFieldLabel;
    QLabel writerFieldLabel;
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
        int releaseYearRange = searchPage.getReleaseYearRange();
        QString genre = searchPage.getGenre();
        QString rating = searchPage.getRating();
        QString language = searchPage.getLanguage();
        int imdbRatingRange = searchPage.getIMDBRatingRange();
        int rottenTomatoesRatingRange = searchPage.getRottenTomatoesRatingRange();
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