#include "controlpid.h"
#include "ui_controlpid.h"

controlpid::controlpid(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::controlpid)
{
    ui->setupUi(this);
}

controlpid::~controlpid()
{
    delete ui;
}

void controlpid::on_Staticmode_clicked()
{
    ui->groupBox_3->setDisabled(true);
}

void controlpid::on_Variablemode_clicked()
{
     ui->groupBox_2->setDisabled(true);
}

void controlpid::on_p150_valueChanged(const QString &arg1)
{


    if(setpt<150)
    {
        con();

        outs("Out2.PID.P "+arg1);
        outs("Out1.PID.P "+arg1);

        clo();
    }
}


void controlpid::on_p200_valueChanged(const QString &arg1)
{
    if(setpt>=150 and setpt<200)
    {
        con();

        outs("Out2.PID.P "+arg1);
        outs("Out1.PID.P "+arg1);

        clo();
    }
}

void controlpid::on_p250_valueChanged(const QString &arg1)
{
    if(setpt>=200 and setpt<250)
    {
        con();

        outs("Out2.PID.P "+arg1);
        outs("Out1.PID.P "+arg1);

        clo();
    }
}

void controlpid::on_p300_valueChanged(const QString &arg1)
{
    if(setpt>=250 and setpt<300)
    {
        con();

        outs("Out2.PID.P "+arg1);
        outs("Out1.PID.P "+arg1);

        clo();
    }
}

void controlpid::on_p350_valueChanged(const QString &arg1)
{
    if(setpt>=300 and setpt<350)
    {
        con();

        outs("Out2.PID.P "+arg1);
        outs("Out1.PID.P "+arg1);

        clo();
    }
}

void controlpid::on_p400_valueChanged(const QString &arg1)
{
    if(setpt>=350)
    {
        con();

        outs("Out2.PID.P "+arg1);
        outs("Out1.PID.P "+arg1);

        clo();
    }
}

void controlpid::on_I150_valueChanged(const QString &arg1)
{
    if(setpt<150)
    {
        con();

        outs("Out2.PID.I "+arg1);
        outs("Out1.PID.I "+arg1);

        clo();
    }
}

void controlpid::on_I200_valueChanged(const QString &arg1)
{
    if(setpt>=150 and setpt<200)
    {
        con();

        outs("Out2.PID.I "+arg1);
        outs("Out1.PID.I "+arg1);

        clo();
    }
}

void controlpid::on_I250_valueChanged(const QString &arg1)
{
    if(setpt>=200 and setpt<250)
    {
        con();

        outs("Out2.PID.I "+arg1);
        outs("Out1.PID.I "+arg1);

        clo();
    }
}



void controlpid::on_I300_valueChanged(const QString &arg1)
{
    if(setpt>=250 and setpt<300)
    {
        con();

        outs("Out2.PID.I "+arg1);
        outs("Out1.PID.I "+arg1);

        clo();
    }
}

void controlpid::on_I350_valueChanged(const QString &arg1)
{
    if(setpt>=300 and setpt<350)
    {
        con();

        outs("Out2.PID.I "+arg1);
        outs("Out1.PID.I "+arg1);

        clo();
    }
}

void controlpid::on_I400_valueChanged(const QString &arg1)
{
    if(setpt>=350)
    {
        con();

        outs("Out2.PID.I "+arg1);
        outs("Out1.PID.I "+arg1);

        clo();
    }
}

void controlpid::on_D150_valueChanged(const QString &arg1)
{
    if(setpt<150)
    {
        con();

        outs("Out2.PID.D "+arg1);
        outs("Out1.PID.D "+arg1);

        clo();
    }
}

void controlpid::on_D200_valueChanged(const QString &arg1)
{
    if(setpt>=150 and setpt<200)
    {
        con();

        outs("Out2.PID.D "+arg1);
        outs("Out1.PID.D "+arg1);

        clo();
    }
}

void controlpid::on_D250_valueChanged(const QString &arg1)
{
    if(setpt>=200 and setpt<250)
    {
        con();

        outs("Out2.PID.D "+arg1);
        outs("Out1.PID.D "+arg1);

        clo();
    }
}

void controlpid::on_D300_valueChanged(const QString &arg1)
{
    if(setpt>=250 and setpt<300)
    {
        con();

        outs("Out2.PID.D "+arg1);
        outs("Out1.PID.D "+arg1);

        clo();
    }
}

void controlpid::on_D350_valueChanged(const QString &arg1)
{
    if(setpt>=300 and setpt<350)
    {
        con();

        outs("Out2.PID.D "+arg1);
        outs("Out1.PID.D "+arg1);

        clo();
    }
}

void controlpid::on_D400_valueChanged(const QString &arg1)
{
    if(setpt>=350)
    {
        con();

        outs("Out2.PID.D "+arg1);
        outs("Out1.PID.D "+arg1);

        clo();
    }
}

void controlpid::on_pstat_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.PID.P "+arg1);
    outs("Out1.PID.P "+arg1);

    clo();
}

void controlpid::on_pint_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.PID.I "+arg1);
    outs("Out1.PID.I "+arg1);

    clo();
}

void controlpid::on_pDIff_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.PID.D "+arg1);
    outs("Out1.PID.D "+arg1);

    clo();
}
