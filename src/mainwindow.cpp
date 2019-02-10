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
    //
    QString imgFile = QFileDialog::getOpenFileName(this, "Open File", ".", "Images (*.png *.bmp)");// *.*bpp 
    if (imgFile.isEmpty()) return;

    this->editor->openImage(imgFile);
    //this->editor->openImages.append(new ImageView(this->ui->scrollArea_Image, imgFile));
    //this->editor->openImages.last()->setAttribute(Qt::WA_DeleteOnClose);
    //this->editor->openImages.last()->show();
    //this->editor->setupPaletteViewer(editor->openImages.last()->image->palette);

    ///// use .last() instead of editor->openImages[editor->openImages.size() - 1]
    //connect(editor->openImages.last(), &ImageView::shouldDeletePalette, this->editor, &Editor::deletePaletteViewer);
/*
    if (!this->editor->openImages[editor->openImages.size() - 1]->isVisible()) {
        this->editor->openImages[editor->openImages.size() - 1]->show();
    } else if (this->editor->openImages[editor->openImages.size() - 1]->isMinimized()) {
        this->editor->openImages[editor->openImages.size() - 1]->showNormal();
    } else {
        this->editor->openImages[editor->openImages.size() - 1]->activateWindow();
    }
//*/
}

void MainWindow::on_action_SaveAll_triggered() {
    //
}

//void MainWindow::on_action_SaveAs_triggered() {
    //
//}




























