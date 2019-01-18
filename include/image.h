#ifndef GUARD_RAKU_IMAGE_H
#define GUARD_RAKU_IMAGE_H

#include <QString>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>



class Image : public QObject, public QGraphicsPixmapItem {

    Q_OBJECT

public:
    Image(QString path_) {
        this->path = path_;
        setAcceptHoverEvents(true);
    }

    //virtual void paint(QGraphicsSceneMouseEvent*);
    //virtual void select(QGraphicsSceneMouseEvent*);
    //virtual void pick(QGraphicsSceneMouseEvent*);
    //virtual void shift(QGraphicsSceneMouseEvent*);
    //virtual void draw();

private:

    QString path;


};

#endif // GUARD_RAKU_IMAGE_H
