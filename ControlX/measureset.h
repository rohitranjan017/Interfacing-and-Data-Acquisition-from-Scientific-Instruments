#ifndef MEASURESET_H
#define MEASURESET_H

#include <QDialog>
//#include "allfun.h"
namespace Ui {
class measureset;
}

class measureset : public QDialog
{
    Q_OBJECT

public:
    explicit measureset(QWidget *parent = 0);
    ~measureset();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void on_speed_activated(const QString &arg1);

    void on_range_activated(const QString &arg1);

    void on_combi_activated(const QString &arg1);

    void on_trace2_activated(const QString &arg1);

    void on_trace1_activated(const QString &arg1);

    void on_combi_activated(int index);

    void on_speed_activated(int index);





    void on_doubleSpinBox_valueChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_comboBox_3_activated(int index);

    void on_doubleSpinBox_2_valueChanged(const QString &arg1);

private:
    Ui::measureset *ui;
};

#endif // MEASURESET_H
