#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    // QApplication a(argc, argv);
    // MainWindow w;
    // w.show();
    // return a.exec();
    QApplication a(argc, argv);
    MainWindow w;
    QPalette palette = w.palette();
    palette.setColor(QPalette::Window, QColor(102, 0, 51));
    w.setPalette(palette);
    w.setAutoFillBackground(true);
    w.show();
    return a.exec();
}
