#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    system("/home/phy/ControlX/./start.sh");
    MainWindow w;

    w.showMaximized();

    return a.exec();
}
