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
#include <QSlider>
#include <QCheckBox>


class SearchPage : public QWidget {
public:
    SearchPage() {
        setFixedSize(640, 720);

        // Basic Search Fields (Initially disabled)
        basicSectionLayout.addWidget(createLineEditField(titleFieldLayout, "Title", titleFieldLabel, titleEdit, titleWidget));
        basicSectionLayout.addWidget(createLineEditField(releaseYearFieldLayout, "Release Year", releaseYearFieldLabel, yearEdit, yearWidget));
        basicSectionLayout.addWidget(createComboBoxField(genreFieldLayout, "Genre", genreFieldLabel, genreCombo, genreWidget));
        basicSectionLayout.addWidget(createComboBoxField(filmRatingFieldLayout, "Film Rating", filmRatingFieldLabel, filmRatingCombo, filmRatingWidget));
        basicSectionLayout.addWidget(createComboBoxField(languageFieldLayout, "Language", languageFieldLabel, languageCombo, languageWidget));
        basicSectionWidget.setLayout(&basicSectionLayout);
        mainLayout.addWidget(&basicSectionWidget);

        // Advanced Search Checkbox
        advancedCheckbox.setText("Advanced Search");
        connect(&advancedCheckbox, &QCheckBox::toggled, this, &SearchPage::toggleAdvancedSearch);
        mainLayout.addWidget(&advancedCheckbox);

        // Advanced Search Fields (Initially disabled)
        advancedSectionWidget.setEnabled(false);
        advancedSectionWidget.setLayout(&advancedSectionLayout);
        advancedSectionLayout.addWidget(createLineEditField(imdbRatingFieldLayout, "IMDB Rating", imdbRatingFieldLabel, imdbRatingEdit, imdbRatingWidget));
        advancedSectionLayout.addWidget(createLineEditField(rottenTomatoesRatingFieldLayout, "Rotten Tomatoes Rating", rottenTomatoesRatingFieldLabel, rottenTomatoesRatingEdit, rottenTomatoesRatingWidget));
        advancedSectionLayout.addWidget(createLineEditField(keywordFieldLayout, "Keyword", keywordFieldLabel, keywordEdit, keywordWidget));
        advancedSectionLayout.addWidget(createLineEditField(actorFieldLayout, "Actor", actorFieldLabel, actorEdit, actorWidget));
        advancedSectionLayout.addWidget(createLineEditField(directorFieldLayout, "Director", directorFieldLabel, directorEdit, directorWidget));
        advancedSectionLayout.addWidget(createLineEditField(writerFieldLayout, "Writer", writerFieldLabel, writerEdit, writerWidget));
        advancedSectionLayout.addStretch();
        mainLayout.addWidget(&advancedSectionWidget);

        // Search Button
        searchButton.setText("SEARCH");
        searchButton.setFixedSize(200, 50);
        mainLayout.addWidget(&searchButton);

        setLayout(&mainLayout);
    }

    QWidget* createLineEditField(QHBoxLayout& fieldLayout, const QString& labelText, QLabel& fieldLabel, QLineEdit& leWidget, QWidget& widgetContainer) {
        fieldLabel.setText(labelText);
        fieldLayout.addWidget(&fieldLabel);
        leWidget.setFixedSize(400, 30);
        leWidget.setAlignment(Qt::AlignCenter);
        fieldLayout.addWidget(&leWidget);
        widgetContainer.setLayout(&fieldLayout);
        return &widgetContainer;
    }

    QWidget* createComboBoxField(QHBoxLayout& fieldLayout, const QString& labelText, QLabel& fieldLabel, QComboBox& cbWidget, QWidget& widgetContainer) {
        fieldLabel.setText(labelText);
        fieldLayout.addWidget(&fieldLabel);
        cbWidget.setFixedSize(400, 30);
        fieldLayout.addWidget(&cbWidget);
        widgetContainer.setLayout(&fieldLayout);
        return &widgetContainer;
    }

    // Accessors for search fields
    [[nodiscard]] QString getTitle() const { return titleEdit.text(); }
    [[nodiscard]] QString getYear() const { return yearEdit.text(); }
    [[nodiscard]] QString getGenre() const { return genreCombo.currentText(); }
    [[nodiscard]] QString getRating() const { return filmRatingCombo.currentText(); }
    [[nodiscard]] QString getLanguage() const { return languageCombo.currentText(); }
    [[nodiscard]] QString getIMDBRating() const { return imdbRatingEdit.text(); }
    [[nodiscard]] QString getRottenTomatoesRating() const { return rottenTomatoesRatingEdit.text(); }
    [[nodiscard]] QString getKeyword() const { return keywordEdit.text(); }
    [[nodiscard]] QString getActor() const { return actorEdit.text(); }
    [[nodiscard]] QString getDirector() const { return directorEdit.text(); }
    [[nodiscard]] QString getWriter() const { return writerEdit.text(); }

public slots:
    void toggleAdvancedSearch() {
        advancedSectionWidget.setEnabled(advancedCheckbox.isChecked());
    }

private:
    QVBoxLayout mainLayout;
    // Basic Search
    QWidget basicSectionWidget;
    QVBoxLayout basicSectionLayout;
    QHBoxLayout titleFieldLayout;
    QHBoxLayout releaseYearFieldLayout;
    QHBoxLayout genreFieldLayout;
    QHBoxLayout filmRatingFieldLayout;
    QHBoxLayout languageFieldLayout;
    QWidget titleWidget;
    QWidget yearWidget;
    QWidget genreWidget;
    QWidget filmRatingWidget;
    QWidget languageWidget;
    QLineEdit titleEdit;
    QLineEdit yearEdit;
    QComboBox genreCombo;
    QComboBox filmRatingCombo;
    QComboBox languageCombo;
    QLabel titleFieldLabel;
    QLabel releaseYearFieldLabel;
    QLabel genreFieldLabel;
    QLabel filmRatingFieldLabel;
    QLabel languageFieldLabel;
    // Advanced Search
    QWidget advancedSectionWidget;
    QVBoxLayout advancedSectionLayout;
    QHBoxLayout imdbRatingFieldLayout;
    QHBoxLayout rottenTomatoesRatingFieldLayout;
    QHBoxLayout keywordFieldLayout;
    QHBoxLayout actorFieldLayout;
    QHBoxLayout directorFieldLayout;
    QHBoxLayout writerFieldLayout;
    QWidget imdbRatingWidget;
    QWidget rottenTomatoesRatingWidget;
    QWidget keywordWidget;
    QWidget actorWidget;
    QWidget directorWidget;
    QWidget writerWidget;
    QLineEdit imdbRatingEdit;
    QLineEdit rottenTomatoesRatingEdit;
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
    QPushButton searchButton;
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
        QString year = searchPage.getYear();
        QString genre = searchPage.getGenre();
        QString rating = searchPage.getRating();
        QString language = searchPage.getLanguage();
        QString imdbRating = searchPage.getIMDBRating();
        QString rottenTomatoesRating = searchPage.getRottenTomatoesRating();
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
    MainGraphicsView view;
    view.show();
    return app.exec();
}