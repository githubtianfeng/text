#include "mainwindow.h"
#include <QApplication>
#include <QSplashScreen>
#include <QPixmap>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    QPixmap pixmap("1.png");
//    QSplashScreen splash(pixmap);
//    splash.show();
//  //  a.processEvents();
//    for(long index=0;index<=500000000;index++);

    MainWindow w;
    w.setWindowTitle("记事本");
    w.resize(800,500);
    w.show();
 //   splash.finish(&w);
    return a.exec();
}
