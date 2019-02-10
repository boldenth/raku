#include "editor.h"

#include <QDebug>
#include <QMatrix>
#include <math.h>

Editor::Editor(Ui::MainWindow* ui)
{
    this->ui = ui;
}



void Editor::openImage(QString imgFile) {
    //
    this->openImages.append(new ImageView(this->ui->scrollArea_Image, imgFile));
    this->openImages.last()->setAttribute(Qt::WA_DeleteOnClose);
    this->openImages.last()->show();
    this->setupPaletteViewer(this->openImages.last()->image->palette);
    this->focusedImage++;
    this->imageOpen = true;

    connect(this->openImages.last(), &ImageView::shouldDeletePalette, this, &Editor::deletePaletteViewer);
}

void Editor::deletePaletteViewer() {
    QLayout *layout = ui->groupBox_Palette->layout();

    for (auto widget : ui->groupBox_Palette->findChildren<QWidget*>())
        delete widget;

    delete layout;
    // TODO: call setupPaletteViewer on new last image?
}

void Editor::setupPaletteViewer(QVector<QColor> *palette) {
    //
    int nColors = palette->size();

    QGridLayout *paletteViewer = new QGridLayout;
    paletteViewer->setSpacing(0);
    paletteViewer->setContentsMargins(0,0,0,0);

    // TODO: find good formulas for this
    int size = 512 / nColors;
    int width = nColors / 8 ? nColors / 8 : 2;

    // connect to mouseGrabber for reordering?
    for (int i = 0; i < nColors; i++) {
        //
        colorBlocks.append(new ColorBox);
        colorBlocks[i]->setFixedSize(size, size);
        paletteViewer->addWidget(colorBlocks[i], i / width, i % width);

        connect(colorBlocks[i], &ColorBox::leftButtonClicked, this, [=]() {
            this->colorClicked(i);
        });
        connect(colorBlocks[i], &ColorBox::rightButtonClicked, this, [=]() {
            this->colorChange(i);
        });

        QColor color = palette->at(i);
        //if (color == Qt::black) color = Qt::darkGray;
        QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());

        colorBlocks[i]->setStyleSheet(stylesheet);
        colorBlocks[i]->setMidLineWidth(3);

        this->rgbpal.append(color.rgb());
    }

    this->ui->groupBox_Palette->setLayout(paletteViewer);
}

void Editor::updatePaletteColors(int nColors) {
    //
    for (int i = 0; i < nColors; i++) {
        updatePaletteColor(i, Qt::white);
    }
}

void Editor::updatePaletteColor(int i, QColor color) {
    //
    QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
    this->colorBlocks[i]->setStyleSheet(stylesheet);
    this->openImages.last()->image->setColorTable(this->rgbpal);
}

void Editor::colorClicked(int index) {
    // "highlight" the color box and clear the currently highlighted
    if (index > colorBlocks.size() - 1) return;// should never happen but just in case

    colorBlocks[selectedColor]->setFrameStyle(QFrame::NoFrame);
    colorBlocks[index]->setFrameStyle(QFrame::Box | QFrame::Raised);
    this->selectedColor = index;
}

// use open image member
void Editor::colorChange(int index) {
    //
    colorClicked(index);
    QColor newColor = QColorDialog::getColor(this->openImages.last()->image->palette->at(index));
    updatePaletteColor(index, newColor);
}
/*
    double scale = pow(3.0, static_cast<double>(value - 30) / 30.0);

    QMatrix matrix;
    matrix.scale(scale, scale);
    QSize size(editor->metatile_selector_item->pixmap().width(), 
               editor->metatile_selector_item->pixmap().height());
    size *= scale;

    ui->graphicsView_Metatiles->setResizeAnchor(QGraphicsView::NoAnchor);
    ui->graphicsView_Metatiles->setMatrix(matrix);
    ui->graphicsView_Metatiles->setFixedSize(size.width() + 2, size.height() + 2);

    //

    bool zoom_in = val > scaleCityMapTiles ? true : false;
    scaleCityMapTiles = val;

    this->ui->graphicsView_City_Map_Tiles->setFixedSize(this->city_map_selector_item->pixelWidth * pow(scaleUpFactor, scaleCityMapTiles - 1) + 2,
                                                        this->city_map_selector_item->pixelHeight * pow(scaleUpFactor, scaleCityMapTiles - 1) + 2);

    if (zoom_in) {
        this->ui->graphicsView_City_Map_Tiles->scale(scaleUpFactor, scaleUpFactor);
    } else {
        this->ui->graphicsView_City_Map_Tiles->scale(scaleDownFactor, scaleDownFactor);
    }
}
*/
void Editor::zoomInCurrentImage() {
    //
    if (imageOpen) {
        //
        ImageView *img = openImages[focusedImage];

        img->scale_exp += 1.0;
        double scale = pow(img->scale_base, img->scale_exp);
        QMatrix matrix;
        matrix.scale(scale, scale);
        QSize size(img->image->pixmap().size());
        size *= scale;

        img->view->setMatrix(matrix);
        img->view->setFixedSize(size.width() + 2, size.height() + 2);
        // TODO: dont grow larger than the available space in the parent
        //img->view->scale(2.0, 2.0);
    }
}

void Editor::zoomOutCurrentImage() {
    //
    if (imageOpen) {
        //
        ImageView *img = openImages[focusedImage];

        img->scale_exp -= 1.0;
        double scale = pow(img->scale_base, img->scale_exp);
        QMatrix matrix;
        matrix.scale(scale, scale);
        QSize size(img->image->size());
        size *= scale;

        img->view->setMatrix(matrix);
        img->view->setFixedSize(size.width() + 2, size.height() + 2);
        //img->view->scale(2.0, 2.0);
    }
}




