#include "colorbox.h"

ColorBox::ColorBox(QWidget * parent) : QFrame(parent) {}

void ColorBox::mousePressEvent(QMouseEvent *event)
{
    switch (event->button())
    {
        case Qt::LeftButton:
            emit leftButtonClicked();
            break;
        case Qt::RightButton:
            emit rightButtonClicked();
            break;
        case Qt::MiddleButton:
            emit centerButtonClicked();
            break;
        default:
            break;
    }

    QFrame::mousePressEvent(event);
}
