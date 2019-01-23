#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>

#include "editor.h"
#include "colorbox.h"
#include "imageview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    Editor *editor;

    QList<QColor>  palette;
    QList<ColorBox*> colorBlocks;

    QList<ImageView*> openImages;

    void initialize();
    void restore();

    void setupWidgets();

    void setupPaletteViewer(int nColors);
    void setupPaletteViewer(QVector<QColor> *palette);

    int selectedColor = 0;

    void updatePaletteColors(int nColors);
    void updatePaletteColor(int index);

private slots:
    void on_action_New_triggered();
    void on_action_Open_triggered();
    void on_action_SaveAll_triggered();
    //void on_action_SaveAs_triggered();
    void colorClicked(int index);
};

#endif // MAINWINDOW_H
