#ifndef GUARD_RAKU_IMAGE_H
#define GUARD_RAKU_IMAGE_H

#include <QFile>
#include <QString>
#include <QImage>
#include <QPixmap>
#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>



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
    Image(int width, int height, int ncolors) : QGraphicsPixmapItem(QPixmap(width, height)), QImage(width, height, QImage::Format_Indexed8) {
        this->palette = new QVector<QColor>;
        for (int i = 0; i < ncolors; i++) {
            palette->append(Qt::white);
        }
        //QImage::fill(0);
        fill(0);
        loadFromData(QByteArray(width * height, 0));
    }
    //*
    //*/
    friend class ImageView;

    // TODO: make private and use access function
    QVector<QColor> *palette = nullptr;

    virtual void paint(QGraphicsSceneMouseEvent*);
    //virtual void select(QGraphicsSceneMouseEvent*);
    //virtual void pick(QGraphicsSceneMouseEvent*);
    //virtual void shift(QGraphicsSceneMouseEvent*);
    //virtual void draw();

private:

    void init();
    void loadImage(QString path);
    void loadPalette();

    int mode;// BPP (is this different from num colors in index?)

    QString path;

signals:

    void mouseEvent(QGraphicsSceneMouseEvent *, Image *);

};

#endif // GUARD_RAKU_IMAGE_H
