#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QShortcut>

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
    delete editor;
    delete ui;
}

void MainWindow::initialize() {
    //
    this->setupWidgets();
    //this->setupEditor();
}

void MainWindow::setupWidgets() {
    //
    this->editor = new Editor(ui);

    QShortcut *shortcut_zoom_in = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Plus), this);
    connect(shortcut_zoom_in, &QShortcut::activated, this->editor, &Editor::zoomInCurrentImage);
    QShortcut *shortcut_zoom_out = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Minus), this);
    connect(shortcut_zoom_out, &QShortcut::activated, this->editor, &Editor::zoomOutCurrentImage);
    //setupPaletteViewer(16);

    //this->ui->scrollArea_Image->setDockNestingEnabled(true);
}

void MainWindow::on_action_New_triggered() {
    //
}

void MainWindow::on_action_Open_triggered() {
    QString imgFile = QFileDialog::getOpenFileName(this, "Open File", ".", "Images (*.png *.bmp)");// *.*bpp 
    if (imgFile.isEmpty()) return;

    this->editor->openImage(imgFile);
}

void MainWindow::on_action_SaveAll_triggered() {
    //
}

//void MainWindow::on_action_SaveAs_triggered() {
    //
//}

void MainWindow::on_actionShow_Grid_toggled() {
    //qDebug() << "on_actionShow_Grid_toggled" << ui->actionShow_Grid->isChecked();
    this->editor->toggleGrid(ui->actionShow_Grid->isChecked());//ui->action_ToggleGrid->isChecked());
}

void MainWindow::on_actionConfigure_triggered() {
    //qDebug() << "on_actionConfigure_triggered";
    this->editor->configureGrid();
}
























