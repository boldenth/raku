#include "image.h"

#include <QDebug>



void Image::init() {
    //
    //this->setPixmap(QPixmap(path));

    loadImage(this->path);
}

// Initializes the image data from a QByteArray so indexing is respected
void Image::loadImage(QString filename) {
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly)) {
        QByteArray imageData = file.readAll();
        this->loadFromData(imageData);
    } else {
        qDebug().nospace() << "ERROR: cannot load image data from" << filename;
    }

    loadPalette();
}

void Image::loadPalette() {
    //
    if (this->palette) delete palette;

    QVector<QColor> *newPalette = new QVector<QColor>;

    qDebug() << "Bit Planes:" << this->bitPlaneCount();
    qDebug() << "Color Count:" << this->colorCount();//pixmap().toImage().colorCount();

    for (QRgb color : this->colorTable()) {
        newPalette->append(QColor::fromRgb(color));
    }

    this->palette = newPalette;
}

void Image::paint(QGraphicsSceneMouseEvent* event) {
    //
    qDebug() << "paint on image";
}








