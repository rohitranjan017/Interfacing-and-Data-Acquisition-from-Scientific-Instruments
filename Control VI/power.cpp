#include "power.h"
#include "ui_power.h"

power::power(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::power)
{
    ui->setupUi(this);
}

power::~power()
{
    delete ui;
}

void power::on_p150_valueChanged(const QString &arg1)
{
    pow150=arg1.toDouble();

    if(setpoint<150)
    {
        con();

        outs("Out2.HiLmt "+arg1);
        outs("Out1.HiLmt "+arg1);

        clo();
    }
}

void power::on_p200_valueChanged(const QString &arg1)
{
    pow200=arg1.toDouble();

    if(setpoint>=150 and setpoint<200)
    {
        con();

        outs("Out2.HiLmt "+arg1);
        outs("Out1.HiLmt "+arg1);

        clo();
    }
}

void power::on_p250_valueChanged(const QString &arg1)
{
    pow250=arg1.toDouble();

    if(setpoint>=200 and setpoint<250)
    {
        con();

        outs("Out2.HiLmt "+arg1);
        outs("Out1.HiLmt "+arg1);

        clo();
    }
}

void power::on_p300_valueChanged(const QString &arg1)
{
    pow300=arg1.toDouble();

    if(setpoint>=250 and setpoint<300)
    {
        con();

        outs("Out2.HiLmt "+arg1);
        outs("Out1.HiLmt "+arg1);

        clo();
    }
}

void power::on_p350_valueChanged(const QString &arg1)
{
    pow350=arg1.toDouble();

    if(setpoint>=300 and setpoint<350)
    {
        con();

        outs("Out2.HiLmt "+arg1);
        outs("Out1.HiLmt "+arg1);

        clo();
    }
}

void power::on_p400_valueChanged(const QString &arg1)
{
    pow400=arg1.toDouble();

    if(setpoint>=350)
    {
        con();

        outs("Out2.HiLmt "+arg1);
        outs("Out1.HiLmt "+arg1);

        clo();
    }
}
