#ifndef KE2182A_H
#define KE2182A_H

#include <QDialog>

namespace Ui {
class ke2182a;
}

class ke2182a : public QDialog
{
    Q_OBJECT

public:
    explicit ke2182a(QWidget *parent = 0);
    int total_points=5;
    int sample_points=5;
    int total_points2=5;
    double lo_lmt;
    double hi_lmt;
    bool mode=0;
    ~ke2182a();

private slots:

    void on_NoofPoints_valueChanged(double arg1);

    void on_ok_clicked();

    void on_NoofPoints_2_valueChanged(double arg1);

    void on_SetAmplitude_valueChanged(const QString &arg1);

    void on_RangeType_2_currentIndexChanged(int index);

    void on_SetAmplitude_2_valueChanged(const QString &arg1);

    void on_RangeType_3_currentIndexChanged(int index);

    void on_NoofPoints_3_valueChanged(double arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::ke2182a *ui;
};

#endif // KE2182A_H
