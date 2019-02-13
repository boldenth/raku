#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QColorDialog>
#include <QFrame>
#include <QList>
#include <QVector>

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

    void initialize();
    void restore();

    void setupWidgets();
    void checkToolButtons();

private slots:
    void on_action_New_triggered();
    void on_action_Open_triggered();
    void on_action_SaveAll_triggered();
    //void on_action_SaveAs_triggered();
    void on_actionShow_Grid_toggled();
    void on_actionConfigure_triggered();

    void on_toolButton_Pencil_clicked();
    void on_toolButton_Dropper_clicked();
    void on_toolButton_Bucket_clicked();
    void on_toolButton_Crop_clicked();
    void on_toolButton_Shift_clicked();
};

#endif // MAINWINDOW_H
