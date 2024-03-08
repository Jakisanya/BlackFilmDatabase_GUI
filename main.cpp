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

QWidget* createLineEditField(const QString& label, QLineEdit& leWidget, QWidget* widgetContainer) {
    QHBoxLayout layout(widgetContainer);
    QLabel fieldLabel(label);
    layout.addWidget(&fieldLabel);
    layout.addWidget(&leWidget);
    return widgetContainer;
}

QWidget* createComboBoxField(const QString& label, QComboBox& cbWidget, QWidget* widgetContainer) {
    QHBoxLayout layout(widgetContainer);
    QLabel fieldLabel(label);
    layout.addWidget(&fieldLabel);
    layout.addWidget(&cbWidget);
    return widgetContainer;
}

class SearchPage : public QWidget {
public:
    SearchPage(QWidget* parent = nullptr) : QWidget(parent) {
        QVBoxLayout layout(this);

        // Basic Search Fields
        layout.addWidget(createLineEditField("Title", titleEdit, titleWidget));
        layout.addWidget(createLineEditField("Release Year", yearEdit, yearWidget));
        layout.addWidget(createComboBoxField("Genre", genreCombo, genreWidget));
        layout.addWidget(createComboBoxField("Film Rating", filmRatingCombo, filmRatingWidget));
        layout.addWidget(createComboBoxField("Language", languageCombo, languageWidget));

        // Advanced Search Fields (Initially disabled)
        advancedSearchFields.setEnabled(false);
        QVBoxLayout advancedLayout(&advancedSearchFields);
        advancedLayout.addWidget(createLineEditField("IMDB Rating", imdbEdit, imdbRatingWidget));
        advancedLayout.addWidget(createLineEditField("Rotten Tomatoes Rating", rottenTomatoesEdit, rottenTomatoesRatingWidget));
        advancedLayout.addWidget(createLineEditField("Keyword", keywordEdit, keywordWidget));
        advancedLayout.addWidget(createLineEditField("Actor", actorEdit, actorWidget));
        advancedLayout.addWidget(createLineEditField("Director", directorEdit, directorWidget));
        advancedLayout.addWidget(createLineEditField("Writer", writerEdit, writerWidget));
        layout.addWidget(&advancedSearchFields);

        // Advanced Search Checkbox
        advancedCheckbox.setText("Advanced Search");
        connect(advancedCheckbox, &QCheckBox::toggled, advancedSearchFields, &QWidget::setEnabled);
        layout.addWidget(&advancedCheckbox);

        // Search Button
        searchButton.setText("Search");
        layout.addWidget(&searchButton);

        setLayout(&layout);
    }

    // Accessors for search fields
    [[nodiscard]] QString getTitle() const { return titleEdit.text(); }
    [[nodiscard]] QString getYear() const { return yearEdit.text(); }
    [[nodiscard]] QString getGenre() const { return genreCombo.currentText(); }
    [[nodiscard]] QString getRating() const { return filmRatingCombo.currentText(); }
    [[nodiscard]] QString getLanguage() const { return languageCombo.currentText(); }
    [[nodiscard]] QString getIMDBRating() const { return imdbEdit.text(); }
    [[nodiscard]] QString getRottenTomatoesRating() const { return rottenTomatoesEdit.text(); }
    [[nodiscard]] QString getKeyword() const { return keywordEdit.text(); }
    [[nodiscard]] QString getActor() const { return actorEdit.text(); }
    [[nodiscard]] QString getDirector() const { return directorEdit.text(); }
    [[nodiscard]] QString getWriter() const { return writerEdit.text(); }

private:
    QWidget* titleWidget;
    QWidget* yearWidget;
    QWidget* genreWidget;
    QWidget* filmRatingWidget;
    QWidget* languageWidget;
    QWidget* imdbRatingWidget;
    QWidget* rottenTomatoesRatingWidget;
    QWidget* keywordWidget;
    QWidget* actorWidget;
    QWidget* directorWidget;
    QWidget* writerWidget;
    QLineEdit titleEdit;
    QLineEdit yearEdit;
    QLineEdit imdbEdit;
    QLineEdit rottenTomatoesEdit;
    QLineEdit keywordEdit;
    QLineEdit actorEdit;
    QLineEdit directorEdit;
    QLineEdit writerEdit;
    QComboBox genreCombo;
    QComboBox filmRatingCombo;
    QComboBox languageCombo;
    QPushButton searchButton;
    QWidget advancedSearchFields;
    QCheckBox advancedCheckbox;
};

class MainGraphicsView : public QGraphicsView {
public:
    MainGraphicsView() {
        setFixedSize(640, 360);
        setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
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

        // Create and display search page
        searchPage = new SearchPage;
        scene.addWidget(searchPage);

        // Connect search button to perform search function
        QObject::connect(searchPage->searchButton, &QPushButton::clicked, this, &MainGraphicsView::performSearch);
    }

    void performSearch() {
        // Gather search parameters from the search page
        QString title = searchPage->getTitle();
        QString year = searchPage->getYear();
        QString genre = searchPage->getGenre();
        QString rating = searchPage->getRating();
        QString language = searchPage->getLanguage();
        QString imdbRating = searchPage->getIMDBRating();
        QString rottenTomatoesRating = searchPage->getRottenTomatoesRating();
        QString keyword = searchPage->getKeyword();
        QString actor = searchPage->getActor();
        QString director = searchPage->getDirector();
        QString writer = searchPage->getWriter();

        // Implement the search functionality, query the database, and display results
    }

private:
    QGraphicsScene scene;
    QGraphicsVideoItem videoItem;
    QMediaPlayer mediaPlayer;
    QPushButton searchButton;
    QGraphicsProxyWidget* proxyWidget;
    SearchPage *searchPage;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainGraphicsView view;
    view.show();
    return app.exec();
}