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
#include <math.h>

#include <QDebug>

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
    QPixmap pixmap;

    double scale_exp  = 1.0;
    double scale_base = 2.0;

    int gridWidth = 1;
    int gridHeight = 1;
    QColor gridColor = Qt::darkGray;
    bool showGrid = false;
    void configureGrid(int w, int h, QColor c);
    void drawGrid(bool visible = false);

    QVector<QGraphicsLineItem*> gridlines;

    bool eventFilter(QObject *object, QEvent *event)
    {
        //if (object == this->sizeGrip)
        if (event->type() == QMouseEvent::HoverEnter) {
            //if (event->localPos().y() > 22) return true;
            setCursor(Qt::OpenHandCursor);
        }
        else if (event->type() == QMouseEvent::HoverLeave) {
            unsetCursor();
        }
        else if (event->type() == QEvent::MouseButtonPress) {
            //qDebug() << event->type();
            //image->scene
            return true;
        }
        return false;
    }

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

private slots:

    void mouseEvent_image(QGraphicsSceneMouseEvent *, Image *);
    //void mousePressEvent_titleBar(QMouseEvent *event);

signals:
    void shouldDeletePalette();
};

#endif // IMAGEVIEW_H
