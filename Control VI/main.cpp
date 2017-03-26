#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>

using namespace QtCharts;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    system("/home/phy/ControlVI/./start.sh");
    MainWindow w;

    w.showMaximized();

    return a.exec();
}
