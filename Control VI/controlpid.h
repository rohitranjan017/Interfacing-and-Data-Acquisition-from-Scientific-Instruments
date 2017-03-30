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
    double p150,p200,p250,p300,p350,p400,i150,i200,i250,i300,i350,i400,d150,d200,d250,d300,d350,d400;
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
