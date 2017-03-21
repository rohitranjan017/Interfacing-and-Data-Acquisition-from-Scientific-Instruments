#include "mainwindow.h"
#include <QApplication>
#include <QtCharts>

using namespace QtCharts;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    system("/home/phy/ControlVI/./start.sh");
    w.showMaximized();

    return a.exec();
}
