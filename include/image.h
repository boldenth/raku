#ifndef GUARD_RAKU_IMAGE_H
#define GUARD_RAKU_IMAGE_H

#include <QFile>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>



enum ImageMode {
    BITDEPTH_1  = 1,
    BITDEPTH_2  = 2,
    BITDEPTH_4  = 4,
    BITDEPTH_8  = 8,
    BITDEPTH_16 = 16,
    BITDEPTH_24 = 24,
};

class Image : public QObject, public QGraphicsPixmapItem, public QImage {

    Q_OBJECT

public:
    Image(QString path_) : QGraphicsPixmapItem(QPixmap(path_)), QImage(path_) {//, QImage::Format_Indexed8) {
        this->path = path_;
        setAcceptHoverEvents(true);
        init();
    }
    //*
    //*/
    friend class ImageView;

    // TODO: make private and use access function
    QVector<QColor> *palette = nullptr;

    //virtual void paint(QGraphicsSceneMouseEvent*);
    //virtual void select(QGraphicsSceneMouseEvent*);
    //virtual void pick(QGraphicsSceneMouseEvent*);
    //virtual void shift(QGraphicsSceneMouseEvent*);
    //virtual void draw();

private:

    void init();
    void loadImage(QString);
    void loadPalette();

    int mode;// BPP (is this different from num colors in index?)

    QString path;


};

#endif // GUARD_RAKU_IMAGE_H
