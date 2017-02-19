#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include<QTimer>
#include <QMainWindow>
#include <measureset.h>
#include <traceset.h>
#include <QtCharts>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
       //wk* ptr=new wk;
       QLineSeries *series[11];
       QChart *chart[11];
       QChartView *chartView[11];

       QValueAxis *axisX[11];
      // QCategoryAxis *axisY[11];
      QValueAxis *axisY[11];
      measureset* meas=new measureset;
      traceset* trace=new traceset;

public slots:
    void showtime();
    //Ui::wk *ptr;


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

  //  void on_pushButton_6_clicked();

    void on_meas_setup_clicked();

    void on_trace_setup_clicked();

    //void on_doubleSpinBox_6_editingFinished();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    void conduct(int temp, int impdel);
    bool checkset(int out);
};

#endif // MAINWINDOW_H
