#ifndef GUARD_EDITOR_H
#define GUARD_EDITOR_H

#include <QGraphicsScene>
#include <math.h>

#include "image.h"
#include "ui_mainwindow.h"



class Editor : public QObject
{

    Q_OBJECT

public:

    Editor(Ui::MainWindow* ui);
    Ui::MainWindow* ui;
    QObject *parent = nullptr;

    void save();
    void undo();
    void redo();

    void displayImage();
    void updateImage();
    void updateView();

    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *pixmap_item = nullptr;
    Image *image = nullptr;
    
    double scale_exp  = 0;
    double scale_base = sqrt(2); // adjust scale factor with this

//private:

//private slots:

//signals:

};

#endif // GUARD_EDITOR_H
