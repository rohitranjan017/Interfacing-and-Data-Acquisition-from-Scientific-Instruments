#include "power.h"
#include "ui_power.h"
#include <QFile>
#include<QTextStream>
QFile filepower("/home/phy/ControlVI/script.sh");
QTextStream outpower(&filepower);
void conpower()
{
    //conecting code starts

   filepower.open(QIODevice::WriteOnly| QIODevice::Text);

   outpower<<"#!/usr/bin/expect\n";
   outpower<<"spawn telnet 100.10.19.37\n";
   /*if(sig==true)
       outpower<<"sleep 0.55\n";
   else
   outpower<<"sleep 0.2\n";*/
   outpower<<"send ";
   outpower<<"\"";
   outpower<<"\\n";
   outpower<<"\"";
   outpower<<"\n";
   outpower<<"send ";
   outpower<<"\"";
   outpower<<"\\n";
   outpower<<"\"";
   outpower<<"\n";
   //connecting code ends
}
void clopower()
{

    //connection terminating code starts//

    //if(sig==true)
      //  outpower<<"sleep 0.55\n";
    //else
    //outpower<<"sleep 0.2\n";
   /* outpower<<"send ";
    outpower<<"\"";
    outpower<<"\\";
    outpower<<"x1D";
    outpower<<"\\n";
    outpower<<"\"";
    outpower<<"\n";

    outpower<<"send ";
    outpower<<"\"quit";
    outpower<<"\\n";
    outpower<<"\"";
    outpower<<"\n";
    outpower<<"send ";
    outpower<<"\"";
    outpower<<"\\";
    outpower<<"x1D";
    outpower<<"\\n";
    outpower<<"\"";
    outpower<<"\n";
    outpower<<"expect ";
    outpower<<"\"";
    outpower<<"telnet> ";
    outpower<<"\"";
    outpower<<"\n";*/
    outpower<<"send ";
    outpower<<"\"system.other.reset Ports";
    outpower<<"\\n";
    outpower<<"\"";
    outpower<<"\n";

   // outpower<<"system.other.reset Ports\n";
     outpower<<"interact\n";
    //connection terminating code ends//
    filepower.close();
   system("script -c /home/phy/ControlVI/./script.sh /home/phy/ControlVI/ctc.txt");
}
void prepower()
{
    outpower<<"send ";
    outpower<<"\"";
}
void postpower()
{
    outpower<<"\\n";
    outpower<<"\"";
    outpower<<"\n";
}
void outspower(QString s)
{
    prepower();
    outpower<<s;
    postpower();
}
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
        conpower();

        outspower("Out2.HiLmt "+arg1);
        outspower("Out1.HiLmt "+arg1);

        clopower();
    }
}

void power::on_p200_valueChanged(const QString &arg1)
{
    pow200=arg1.toDouble();

    if(setpoint>=150 and setpoint<200)
    {
        conpower();

        outspower("Out2.HiLmt "+arg1);
        outspower("Out1.HiLmt "+arg1);

        clopower();
    }
}

void power::on_p250_valueChanged(const QString &arg1)
{
    pow250=arg1.toDouble();

    if(setpoint>=200 and setpoint<250)
    {
        conpower();

        outspower("Out2.HiLmt "+arg1);
        outspower("Out1.HiLmt "+arg1);

        clopower();
    }
}

void power::on_p300_valueChanged(const QString &arg1)
{
    pow300=arg1.toDouble();

    if(setpoint>=250 and setpoint<300)
    {
        conpower();

        outspower("Out2.HiLmt "+arg1);
        outspower("Out1.HiLmt "+arg1);

        clopower();
    }
}

void power::on_p350_valueChanged(const QString &arg1)
{
    pow350=arg1.toDouble();

    if(setpoint>=300 and setpoint<350)
    {
        conpower();

        outspower("Out2.HiLmt "+arg1);
        outspower("Out1.HiLmt "+arg1);

        clopower();
    }
}

void power::on_p400_valueChanged(const QString &arg1)
{
    pow400=arg1.toDouble();

    if(setpoint>=350)
    {
        conpower();

        outspower("Out2.HiLmt "+arg1);
        outspower("Out1.HiLmt "+arg1);

        clopower();
    }
}
