#ifndef WK_H
#define WK_H

#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QCategoryAxis>
#include <QLogValueAxis>
#include <QtCharts>
#include <QString>
QT_CHARTS_USE_NAMESPACE
namespace Ui {
class wk;
}

class wk : public QMainWindow
{
    Q_OBJECT


public:
    explicit wk(QWidget *parent = 0);
    ~wk();
     //Ui::wk *ptr;
    QLineSeries *series[11];
    QChart *chart[11];
    QChartView *chartView[11];

    QValueAxis *axisX[11];
   // QCategoryAxis *axisY[11];
   QValueAxis *axisY[11];
private slots:

    void on_pushButton_2_clicked();

    void on_meas_setup_clicked();

    void on_trace_setup_clicked();

    void on_pushButton_clicked();

    void on_trig_clicked();

    //void on_add_clicked();

private:
    Ui::wk *ui;
    void writelog();
};

#endif // WK_H
