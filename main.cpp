// --- BlackFilmDatabase_GUI --- \\

#include "MainGraphicsView.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    /*
    app.setStyleSheet(
            QWidget{ background-color: yellow; }
            RangeSlider { background-color: rgba(255,255,255,0); }
    );
    */

    MainGraphicsView view;
    view.move(475, 30);
    view.show();
    return QApplication::exec();
}