#include "HoverButton.h"

HoverButton::HoverButton() = default;

void HoverButton::enterEvent(QEnterEvent* event) {
    QPushButton::enterEvent(event);
    emit entered(); // Emit custom signal for hover enter
}

void HoverButton::leaveEvent(QEvent* event) {
    QPushButton::leaveEvent(event);
    emit left(); // Emit custom signal for hover leave
}
