#include "mainwindow.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMainWindow>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QDesktopWidget dw;
    MainWindow w;

    int width = 1100;
    int height = 600;
    int x = int((width - w.width()) / 2.0);
    int y = int((height - w.height()) / 2.0);
    w.setGeometry(x,y,width,height);

    w.show();

    return a.exec();
}
