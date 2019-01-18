#ifndef GUARD_COLORBOX_H
#define GUARD_COLORBOX_H

#include <QFrame>
#include <QMouseEvent>

class ColorBox : public QFrame
{

    Q_OBJECT

public:

    ColorBox(QWidget *parent = Q_NULLPTR);

private slots:

    void mousePressEvent(QMouseEvent *event);

signals:

    void leftButtonClicked();
    void rightButtonClicked();
    void centerButtonClicked();

};

#endif // GUARD_COLORBOX_H
