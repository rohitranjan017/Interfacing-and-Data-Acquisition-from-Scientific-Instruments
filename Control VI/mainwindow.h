#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QMainWindow>
#include <ke6221.h>
#include <ke2182a.h>
#include <QtCharts>
#include <power.h>
#include <controlpid.h>
using namespace QtCharts;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
      ~MainWindow();
       QLineSeries *series;

       QChart *chart;
       QChartView *chartView;

       QValueAxis *axisX;

      QValueAxis *axisY;
      ke2182a* ke2=new ke2182a;
      ke6221* ke6=new ke6221;
      power* powtab=new power;
      controlpid* pidtab=new controlpid;

public slots:
    void showtime();



private slots:
    void on_pushButton_2_clicked();

    void on_connect_clicked();

    void on_out1mode_clicked();

    void on_comboBox_currentIndexChanged(const QString &arg1);

    void on_doubleSpinBox_valueChanged(const QString &arg1);

    void on_doubleSpinBox_2_valueChanged(const QString &arg1);


    void on_comboBox_2_currentIndexChanged(const QString &arg1);

  void on_doubleSpinBox_6_valueChanged(const QString &arg1);

    void on_doubleSpinBox_9_valueChanged(const QString &arg1);

    void on_doubleSpinBox_11_valueChanged(const QString &arg1);

    void on_doubleSpinBox_12_valueChanged(const QString &arg1);

    void on_doubleSpinBox_13_valueChanged(const QString &arg1);

    void on_out2mode_clicked();

    void on_comboBox_5_currentIndexChanged(const QString &arg1);

    void on_doubleSpinBox_14_valueChanged(const QString &arg1);

    void on_doubleSpinBox_15_valueChanged(const QString &arg1);

    void on_comboBox_6_currentIndexChanged(const QString &arg1);

    void on_doubleSpinBox_17_valueChanged(const QString &arg1);

    void on_doubleSpinBox_20_valueChanged(const QString &arg1);

    void on_doubleSpinBox_22_valueChanged(const QString &arg1);

    void on_doubleSpinBox_23_valueChanged(const QString &arg1);

    void on_doubleSpinBox_24_valueChanged(const QString &arg1);

    void on_out2mode_2_clicked();

    void on_out2mode_6_clicked();

    void on_out2mode_10_clicked();

    void on_out2mode_9_clicked();

    void on_comboBox_7_currentIndexChanged(const QString &arg1);

    void on_comboBox_15_currentIndexChanged(const QString &arg1);

    void on_comboBox_23_currentIndexChanged(const QString &arg1);

    void on_comboBox_21_currentIndexChanged(const QString &arg1);


    void on_comboBox_8_activated(const QString &arg1);

    void on_comboBox_24_activated(const QString &arg1);

    void on_comboBox_16_activated(const QString &arg1);

    void on_comboBox_22_activated(const QString &arg1);


    void on_out2mode_5_clicked();

    void on_out2mode_4_clicked();


    void on_keithley_clicked();

    void on_keithley6_clicked();

    void on_powlmt2_clicked();

    void on_powlmt1_clicked();

    void on_pidctrl1_clicked();

    void on_pidctrl2_clicked();
    void configure_power(double setpoint);
    void configure_pid(double setpoint);

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    void conduct(int temp);
    bool checkset(int out);
};

#endif // MAINWINDOW_H
