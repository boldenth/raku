#include "mainwindow.h"
#include <QApplication>
#include <QFontDatabase>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    QFontDatabase::addApplicationFont(":/FontAwesome.otf");
    MainWindow window;
    window.show();

    return app.exec();
}
