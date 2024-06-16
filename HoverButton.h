#ifndef BLACKFILMDATABASE_GUI_2_HOVERBUTTON_H
#define BLACKFILMDATABASE_GUI_2_HOVERBUTTON_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QDebug>

class HoverButton : public QPushButton {
    Q_OBJECT
public:
    explicit HoverButton();
    void enterEvent(QEnterEvent* event) override;
    void leaveEvent(QEvent* event) override;

signals:
    void entered(); // Custom signal for hover enter
    void left();    // Custom signal for hover leave

private:
    QString hoverButtonType;
};


#endif //BLACKFILMDATABASE_GUI_2_HOVERBUTTON_H
