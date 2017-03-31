#ifndef CONTROLPID_H
#define CONTROLPID_H

#include <QWidget>

namespace Ui {
class controlpid;
}

class controlpid : public QWidget
{
    Q_OBJECT

public:
    double setpt;
    double p150=11.35,p200=17.5,p250=22.5,p300=27.5,p350=32.5,p400=37.5,i150=0.567,i200=0.875,i250=1.125,i300=1.375,i350=1.625,i400=1.875,d150=0.378,d200=0.583,d250=0.750,d300=0.917,d350=1.083,d400=1.250;
    bool mode=1;
    explicit controlpid(QWidget *parent = 0);
    ~controlpid();

private slots:
    void on_Staticmode_clicked();

    void on_Variablemode_clicked();

    void on_p150_valueChanged(const QString &arg1);

    void on_p200_valueChanged(const QString &arg1);

    void on_p250_valueChanged(const QString &arg1);

    void on_p300_valueChanged(const QString &arg1);

    void on_p350_valueChanged(const QString &arg1);

    void on_p400_valueChanged(const QString &arg1);

    void on_I150_valueChanged(const QString &arg1);

    void on_I250_valueChanged(const QString &arg1);

    void on_I200_valueChanged(const QString &arg1);

    //void on_I250_2_editingFinished();

    void on_I300_valueChanged(const QString &arg1);

    void on_I350_valueChanged(const QString &arg1);

    void on_I400_valueChanged(const QString &arg1);

    void on_D150_valueChanged(const QString &arg1);

    void on_D200_valueChanged(const QString &arg1);

    void on_D250_valueChanged(const QString &arg1);

    void on_D300_valueChanged(const QString &arg1);

    void on_D350_valueChanged(const QString &arg1);

    void on_D400_valueChanged(const QString &arg1);

    void on_pstat_valueChanged(const QString &arg1);

    void on_pint_valueChanged(const QString &arg1);

    void on_pDIff_valueChanged(const QString &arg1);

private:
    Ui::controlpid *ui;
};

#endif // CONTROLPID_H
