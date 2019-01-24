#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QCoreApplication::setOrganizationName("boldenth");
    QCoreApplication::setApplicationName("raku");
    QApplication::setApplicationDisplayName("raku");

    this->initialize();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initialize() {
    //
    this->setupWidgets();
}

void MainWindow::setupWidgets() {
    //
    this->editor = new Editor(ui);
    //setupPaletteViewer(16);

    //this->ui->scrollArea_Image->setDockNestingEnabled(true);
}

// TODO: move to editor scope
void MainWindow::setupPaletteViewer(int nColors) {
    //
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

        QColor rcolor = Qt::gray;
        QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(rcolor.red())
            .arg(rcolor.green())
            .arg(rcolor.blue());

        colorBlocks[i]->setStyleSheet(stylesheet);
    }

    this->ui->groupBox_Palette->setLayout(paletteViewer);
}

void MainWindow::setupPaletteViewer(QVector<QColor> *palette) {
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

void MainWindow::updatePaletteColors(int nColors) {
    //
    for (int i = 0; i < nColors; i++) {
        updatePaletteColor(i, Qt::white);
    }
}

void MainWindow::updatePaletteColor(int i, QColor color) {
    //
    QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(color.red())
            .arg(color.green())
            .arg(color.blue());
    this->colorBlocks[i]->setStyleSheet(stylesheet);
    this->openImages[openImages.size() - 1]->image->setColorTable(this->rgbpal);
}
















































void MainWindow::colorClicked(int index) {
    // "highlight" the color box and clear the currently highlighted
    if (index > colorBlocks.size() - 1) return;// should never happen but just in case

    colorBlocks[selectedColor]->setFrameStyle(QFrame::NoFrame);
    colorBlocks[index]->setFrameStyle(QFrame::Box | QFrame::Raised);
    this->selectedColor = index;
}

// use open image member
void MainWindow::colorChange(int index) {
    //
    colorClicked(index);
    QColor newColor = QColorDialog::getColor(this->openImages[openImages.size() - 1]->image->palette->at(index));
    updatePaletteColor(index, newColor);
}

void MainWindow::on_action_New_triggered() {
    //
}

void MainWindow::on_action_Open_triggered() {
    //
    QString imgFile = QFileDialog::getOpenFileName(this, "Open File", ".", "Images (*.png *.bmp)");// *.*bpp 
    if (imgFile.isEmpty()) return;

    this->openImages.append(new ImageView(this->ui->scrollArea_Image, imgFile));
    this->openImages[openImages.size() - 1]->setAttribute(Qt::WA_DeleteOnClose);
    this->openImages[openImages.size() - 1]->show();
    this->setupPaletteViewer(openImages[openImages.size() - 1]->image->palette);
/*
    if (!this->openImages[openImages.size() - 1]->isVisible()) {
        this->openImages[openImages.size() - 1]->show();
    } else if (this->openImages[openImages.size() - 1]->isMinimized()) {
        this->openImages[openImages.size() - 1]->showNormal();
    } else {
        this->openImages[openImages.size() - 1]->activateWindow();
    }
//*/
}

void MainWindow::on_action_SaveAll_triggered() {
    //
}

//void MainWindow::on_action_SaveAs_triggered() {
    //
//}




























