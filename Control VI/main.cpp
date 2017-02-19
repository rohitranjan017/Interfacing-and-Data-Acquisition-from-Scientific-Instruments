#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    system("/home/phy/ControlX/./start.sh");
    w.showMaximized();

    return a.exec();
}
