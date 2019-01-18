#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QRandomGenerator>
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
    setupPaletteViewer(16);
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

        QColor rcolor = QColor::fromRgb(QRandomGenerator::global()->generate());// temp
        QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(rcolor.red())
            .arg(rcolor.green())
            .arg(rcolor.blue());

        colorBlocks[i]->setStyleSheet(stylesheet);
    }

    this->ui->groupBox_Palette->setLayout(paletteViewer);
}

void MainWindow::updatePaletteColors(int nColors) {
    //
    for (int i = 0; i < nColors; i++) {
        updatePaletteColor(i);
    }
}

void MainWindow::updatePaletteColor(int i) {
    //
    int red, green, blue;
    QString stylesheet = QString("background-color: rgb(%1, %2, %3);")
            .arg(red)
            .arg(green)
            .arg(blue);
    this->colorBlocks[i]->setStyleSheet(stylesheet);
}
















































void MainWindow::colorClicked(int index) {
    //
    qDebug() << "clicked on color" << index;
}

void MainWindow::on_action_New_triggered() {
    //
}

void MainWindow::on_action_Open_triggered() {
    //
}

void MainWindow::on_action_Save_triggered() {
    //
}

void MainWindow::on_action_SaveAs_triggered() {
    //
}




























