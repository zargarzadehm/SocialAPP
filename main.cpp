#include "mainwindow.h"
#include "interface.h"
#include <QApplication>
#include <QFile>
#include "send_group.h"

extern QString User_src;
extern QString token;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setGeometry(50,50,640,480);
       QFile file("info/information.txt");
    if(file.open(QIODevice::ReadWrite|QIODevice::Text)){
        QString data = file.readAll();
        if(file.pos()!=0){
            QStringList stringlist = data.split(',');
            token = stringlist[0];
            User_src = stringlist[1];
            file.close();
            interface* inter = new interface;
            inter->show();
        }
        else w.show();
    }

    return a.exec();
}
