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

    this->editor->openImages.append(new ImageView(this->ui->scrollArea_Image, imgFile));
    this->editor->openImages[editor->openImages.size() - 1]->setAttribute(Qt::WA_DeleteOnClose);
    this->editor->openImages[editor->openImages.size() - 1]->show();
    this->editor->setupPaletteViewer(editor->openImages[editor->openImages.size() - 1]->image->palette);
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




























