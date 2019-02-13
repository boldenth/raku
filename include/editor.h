#ifndef GUARD_EDITOR_H
#define GUARD_EDITOR_H

#include <QGraphicsScene>
#include <QMainWindow>
#include <QColorDialog>
#include <QFrame>
#include <QList>
#include <QVector>
#include <math.h>

#include "colorbox.h"
#include "imageview.h"
#include "image.h"
#include "settings.h"
#include "ui_mainwindow.h"

/*
 *    Brushes, palette,
 */

class Editor : public QObject
{

    Q_OBJECT

public:

    Editor(Ui::MainWindow* ui);
    Ui::MainWindow* ui;
    QObject *parent = nullptr;

    QGraphicsScene *scene = nullptr;
    QGraphicsPixmapItem *pixmap_item = nullptr;
    Image *image = nullptr;

    QVector<QRgb> rgbpal;
    QList<ColorBox*> colorBlocks;
    QList<ImageView*> openImages;

    //Settings settings;
    QString editMode;

    int selectedColor = 0;
    int focusedImage = -1;// index of open color

    bool imageOpen = false;

    void save();
    void undo();
    void redo();

    void createNewImage(int width, int height, int ncolors);
    void openImage(QString imgFile);
    void displayImage();
    void updateImage();
    void updateView();
    void zoomInCurrentImage();
    void zoomOutCurrentImage();
    void configureGrid();
    void toggleGrid(bool visible = false);

    void colorClicked(int index);
    void colorChange(int index);

    void setActivePalette(int index);
    void setupPaletteViewer(QVector<QColor> *palette);
    void deletePaletteViewer();
    void updatePaletteColors(int nColors);
    void updatePaletteColor(int i, QColor color);

//private:

//private slots:

//signals:

};

#endif // GUARD_EDITOR_H
