#ifndef KE6221_H
#define KE6221_H

#include <QDialog>

namespace Ui {
class ke6221;
}

class ke6221 : public QDialog
{
    Q_OBJECT

public:
    explicit ke6221(QWidget *parent = 0);
    double current;
    ~ke6221();

private slots:
    void on_Output_clicked();

    void on_SetFilter_clicked();

    void on_RangeType_currentIndexChanged(const QString &arg1);

    void on_SetAmplitude_valueChanged(QString arg1);



    void on_SetAmplitude_valueChanged(double arg1);

    void on_SetRange_currentIndexChanged(int index);

    void on_RangeType_2_currentIndexChanged(int index);

    void on_ok_clicked();



    void on_SetCompliance_valueChanged(double arg1);

    void on_buttonBox_accepted();

private:
    Ui::ke6221 *ui;
};

#endif // KE6221_H
