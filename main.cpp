// --- BlackFilmDatabase_GUI --- \\

#include "MainGraphicsView.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainGraphicsView view;
    view.move(475, 30);
    view.show();
    return QApplication::exec();
}