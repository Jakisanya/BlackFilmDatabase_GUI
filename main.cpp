// --- BlackFilmDatabase_GUI --- \\

#include <QApplication>
#include <QtWidgets>
#include <QWidget>
#include <QtCore>
#include <QtMultimedia>
#include <QtMultimediaWidgets>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <iostream>

class mainGraphicsView : public QGraphicsView {
public:
    mainGraphicsView() {
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
                         &mainGraphicsView::showSearchPage);
    }

public slots:
    void showSearchPage() {
        // Clear the scene
        scene.removeItem(&videoItem);
        scene.removeItem(proxyWidget);

        // Add new content
        QGraphicsTextItem newTextItem("New Content");
        newTextItem.setPos(100, 100);
        scene.addItem(&newTextItem);
    }

private:
    QGraphicsScene scene;
    QGraphicsVideoItem videoItem;
    QMediaPlayer mediaPlayer;
    QPushButton searchButton;
    QGraphicsProxyWidget* proxyWidget;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    mainGraphicsView view;

    view.show();
    return app.exec();
}
