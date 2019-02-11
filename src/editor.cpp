#include "editor.h"

#include <QDebug>
#include <QMatrix>
#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
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

// TODO: does this not scale properly when not square?
void Editor::zoomInCurrentImage() {
    if (imageOpen) {
        ImageView *img = openImages[focusedImage];

        img->scale_exp += 1.0;
        double scale = pow(img->scale_base, img->scale_exp);
        QMatrix matrix;
        matrix.scale(scale, scale);
        QSize size(img->image->pixmap().size());
        size *= scale;

        img->view->setMatrix(matrix);

        int new_width = size.width() + 2;
        int new_height = size.height() + 2;

        if (new_width > ui->scrollArea_Image->size().width())
            new_width = ui->scrollArea_Image->size().width();

        if (new_height > ui->scrollArea_Image->size().height())
            new_height = ui->scrollArea_Image->size().height();

        img->view->setFixedSize(new_width, new_height);
    }
}

void Editor::zoomOutCurrentImage() {
    if (imageOpen) {
        ImageView *img = openImages[focusedImage];

        img->scale_exp -= 1.0;
        double scale = pow(img->scale_base, img->scale_exp);
        QMatrix matrix;
        matrix.scale(scale, scale);
        QSize size(img->image->size());
        size *= scale;

        img->view->setMatrix(matrix);
        
        int new_width = size.width() + 2;
        int new_height = size.height() + 2;

        if (new_width > ui->scrollArea_Image->size().width())
            new_width = ui->scrollArea_Image->size().width();

        if (new_height > ui->scrollArea_Image->size().height())
            new_height = ui->scrollArea_Image->size().height();

        img->view->setFixedSize(new_width, new_height);
    }
}

void Editor::toggleGrid(bool visible) {
    if (focusedImage < 0) return;

    openImages[focusedImage]->drawGrid(visible);
}

void Editor::configureGrid() {
    if (focusedImage < 0) return;

    QDialog popup(nullptr, Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    popup.setWindowTitle("Configure Grid");
    popup.setWindowModality(Qt::NonModal);

    QFormLayout form(&popup);

    ImageView *focus = openImages[focusedImage];
    int grid_width, grid_height;
    QColor grid_color;

    QSpinBox *width_box = new QSpinBox();
    width_box->setMinimum(1);
    width_box->setMaximum(focus->image->pixmap().width() / 2);
    form.addRow(new QLabel("grid horizontal spacing (pixels):"), width_box);

    QSpinBox *height_box = new QSpinBox();
    height_box->setMinimum(1);
    height_box->setMaximum(focus->image->pixmap().height() / 2);
    form.addRow(new QLabel("grid vertical spacing (pixels):"), height_box);

    // TODO: add grid pattern on this button
    QPushButton *color_box = new QPushButton();
    color_box->setAutoFillBackground(true);
    grid_color = focus->gridColor;
    QString stylesheet = QString("background-color: rgb(%1, %2, %3); color: rgb(%1, %2, %3)")
                                 .arg(grid_color.red())
                                 .arg(grid_color.green())
                                 .arg(grid_color.blue());;
    color_box->setStyleSheet(stylesheet);
    form.addRow(new QLabel("grid line color:"), color_box);
    color_box->show();

    QDialogButtonBox button_box(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &popup);

    form.addRow(&button_box);

    connect(color_box, &QPushButton::pressed, [&grid_color, &color_box](){
        grid_color = QColorDialog::getColor(grid_color);
        QString stylesheet = QString("background-color: rgb(%1, %2, %3); color: rgb(%1, %2, %3)")
                                 .arg(grid_color.red())
                                 .arg(grid_color.green())
                                 .arg(grid_color.blue());;
        color_box->setStyleSheet(stylesheet);
    });
    connect(&button_box, SIGNAL(rejected()), &popup, SLOT(reject()));
    connect(&button_box, &QDialogButtonBox::accepted, [&popup, &width_box, &height_box, &color_box, 
                                                       &grid_width, &grid_height, &grid_color](){
        grid_width = width_box->value();
        grid_height = height_box->value();
        grid_color = grid_color;
        popup.accept();
    });

    if (popup.exec() == QDialog::Accepted) {
        focus->configureGrid(grid_width, grid_height, grid_color);
    }
}


