#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setGeometry(50,50,640,480);
    w.show();

    return a.exec();
}
