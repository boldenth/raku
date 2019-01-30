#ifndef IMAGEVIEW_H
#define IMAGEVIEW_H

#include "image.h"

#include <QWidget>
#include <QDockWidget>
#include <QGraphicsPixmapItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QCloseEvent>

namespace Ui {
class ImageView;
}

class ImageView : public QDockWidget
{
    Q_OBJECT

public:
    explicit ImageView(QWidget *parent = nullptr, QString imgFile = QString());
    ~ImageView();

    QGraphicsView  *view  = nullptr;
    QGraphicsScene *scene = nullptr;

    Image *image = nullptr;
    QImage img;
    QPixmap pixmap;

private:
    Ui::ImageView *ui;

    QPoint origin;

    void close();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void hoverEnterEvent(QHoverEvent *event);
    void hoverLeaveEvent(QHoverEvent *event);

public slots:

    void closeEvent(QCloseEvent *event);

signals:
    void shouldDeletePalette();
};

#endif // IMAGEVIEW_H
