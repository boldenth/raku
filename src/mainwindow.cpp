#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QDebug>
#include <QShortcut>
#include <QDialog>
#include <QDialogButtonBox>
#include <QMessageBox>
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QFont>

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

    QFont font("Font Awesome 5 Free");
    font.setPixelSize(64);
    this->ui->toolButton_Pencil->setStyleSheet("font-family: Font Awesome 5 Free");
    this->ui->toolButton_Pencil->setText("\uf303");
    this->ui->toolButton_Dropper->setStyleSheet("font-family: Font Awesome 5 Free");
    this->ui->toolButton_Dropper->setText("\uf1fb");
    this->ui->toolButton_Bucket->setStyleSheet("font-family: Font Awesome 5 Free");
    this->ui->toolButton_Bucket->setText("\uf576");

    //this->ui->scrollArea_Image->setDockNestingEnabled(true);
}

void MainWindow::on_action_New_triggered() {
    QDialog popup(this, Qt::WindowTitleHint | Qt::WindowCloseButtonHint);
    popup.setWindowTitle("Create New Image");
    popup.setWindowModality(Qt::NonModal);

    QFormLayout form(&popup);

    int width, height, ncolors;

    QSpinBox *width_box = new QSpinBox();
    width_box->setMinimum(1);
    form.addRow(new QLabel("new image width (pixels):"), width_box);

    QSpinBox *height_box = new QSpinBox();
    height_box->setMinimum(1);
    form.addRow(new QLabel("new image height (pixels):"), height_box);

    QSpinBox *color_box = new QSpinBox();
    color_box->setMinimum(1);
    form.addRow(new QLabel("number of colors:"), color_box);

    QDialogButtonBox button_box(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, &popup);
    form.addRow(&button_box);

    connect(&button_box, SIGNAL(rejected()), &popup, SLOT(reject()));
    connect(&button_box, &QDialogButtonBox::accepted, [&popup, &width_box, &height_box, &color_box, &width, &height, &ncolors](){
        width = width_box->value();
        height = height_box->value();
        ncolors = color_box->value();
        popup.accept();
    });

    if (popup.exec() == QDialog::Accepted) {
        editor->createNewImage(width, height, ncolors);
    }
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
    this->editor->toggleGrid(ui->actionShow_Grid->isChecked());//ui->action_ToggleGrid->isChecked());
}

void MainWindow::on_actionConfigure_triggered() {
    this->editor->configureGrid();
}
























