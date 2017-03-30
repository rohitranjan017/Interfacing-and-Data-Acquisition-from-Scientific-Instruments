#include "controlpid.h"
#include "ui_controlpid.h"
#include <QFile>
#include <QTextStream>
QFile filepid("/home/phy/ControlVI/script.sh");
QTextStream outpid(&filepid);
void conpid()
{
    //conecting code starts

   filepid.open(QIODevice::WriteOnly| QIODevice::Text);

   outpid<<"#!/usr/bin/expect\n";
   outpid<<"spawn telnet 100.10.19.37\n";
   /*if(sig==true)
       outpid<<"sleep 0.55\n";
   else
   outpid<<"sleep 0.2\n";*/
   outpid<<"send ";
   outpid<<"\"";
   outpid<<"\\n";
   outpid<<"\"";
   outpid<<"\n";
   outpid<<"send ";
   outpid<<"\"";
   outpid<<"\\n";
   outpid<<"\"";
   outpid<<"\n";
   //connecting code ends
}
void clopid()
{

    //connection terminating code starts//

    //if(sig==true)
      //  outpid<<"sleep 0.55\n";
    //else
    //outpid<<"sleep 0.2\n";
   /* outpid<<"send ";
    outpid<<"\"";
    outpid<<"\\";
    outpid<<"x1D";
    outpid<<"\\n";
    outpid<<"\"";
    outpid<<"\n";

    outpid<<"send ";
    outpid<<"\"quit";
    outpid<<"\\n";
    outpid<<"\"";
    outpid<<"\n";
    outpid<<"send ";
    outpid<<"\"";
    outpid<<"\\";
    outpid<<"x1D";
    outpid<<"\\n";
    outpid<<"\"";
    outpid<<"\n";
    outpid<<"expect ";
    outpid<<"\"";
    outpid<<"telnet> ";
    outpid<<"\"";
    outpid<<"\n";*/
    outpid<<"send ";
    outpid<<"\"system.other.reset Ports";
    outpid<<"\\n";
    outpid<<"\"";
    outpid<<"\n";

   // outpid<<"system.other.reset Ports\n";
     outpid<<"interact\n";
    //connection terminating code ends//
    filepid.close();
   system("script -c /home/phy/ControlVI/./script.sh /home/phy/ControlVI/ctc.txt");
}
void prepid()
{
    outpid<<"send ";
    outpid<<"\"";
}
void postpid()
{
    outpid<<"\\n";
    outpid<<"\"";
    outpid<<"\n";
}
void outspid(QString s)
{
    prepid();
    outpid<<s;
    postpid();
}
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
    conpid();

    outspid("Out2.PID.P "+QString::number(ui->pstat->value()));
    outspid("Out1.PID.P "+QString::number(ui->pstat->value()));
    outspid("Out2.PID.I "+QString::number(ui->pint->value()));
    outspid("Out1.PID.I "+QString::number(ui->pint->value()));
    outspid("Out2.PID.D "+QString::number(ui->pDIff->value()));
    outspid("Out1.PID.D "+QString::number(ui->pDIff->value()));

    clopid();
    mode=0;
}

void controlpid::on_Variablemode_clicked()
{
     ui->groupBox_2->setDisabled(true);
     mode=1;
}

void controlpid::on_p150_valueChanged(const QString &arg1)
{

    p150=arg1.toDouble();

    if(setpt<150)
    {
        conpid();

        outspid("Out2.PID.P "+arg1);
        outspid("Out1.PID.P "+arg1);

        clopid();
    }
}


void controlpid::on_p200_valueChanged(const QString &arg1)
{
    p200=arg1.toDouble();

    if(setpt>=150 and setpt<200)
    {
        conpid();

        outspid("Out2.PID.P "+arg1);
        outspid("Out1.PID.P "+arg1);

        clopid();
    }
}

void controlpid::on_p250_valueChanged(const QString &arg1)
{
    p250=arg1.toDouble();

    if(setpt>=200 and setpt<250)
    {
        conpid();

        outspid("Out2.PID.P "+arg1);
        outspid("Out1.PID.P "+arg1);

        clopid();
    }
}

void controlpid::on_p300_valueChanged(const QString &arg1)
{
    p300=arg1.toDouble();

    if(setpt>=250 and setpt<300)
    {
        conpid();

        outspid("Out2.PID.P "+arg1);
        outspid("Out1.PID.P "+arg1);

        clopid();
    }
}

void controlpid::on_p350_valueChanged(const QString &arg1)
{
    p350=arg1.toDouble();

    if(setpt>=300 and setpt<350)
    {
        conpid();

        outspid("Out2.PID.P "+arg1);
        outspid("Out1.PID.P "+arg1);

        clopid();
    }
}

void controlpid::on_p400_valueChanged(const QString &arg1)
{
    p400=arg1.toDouble();

    if(setpt>=350)
    {
        conpid();

        outspid("Out2.PID.P "+arg1);
        outspid("Out1.PID.P "+arg1);

        clopid();
    }
}

void controlpid::on_I150_valueChanged(const QString &arg1)
{
    i150=arg1.toDouble();

    if(setpt<150)
    {
        conpid();

        outspid("Out2.PID.I "+arg1);
        outspid("Out1.PID.I "+arg1);

        clopid();
    }
}

void controlpid::on_I200_valueChanged(const QString &arg1)
{
    i200=arg1.toDouble();

    if(setpt>=150 and setpt<200)
    {
        conpid();

        outspid("Out2.PID.I "+arg1);
        outspid("Out1.PID.I "+arg1);

        clopid();
    }
}

void controlpid::on_I250_valueChanged(const QString &arg1)
{
    i250=arg1.toDouble();

    if(setpt>=200 and setpt<250)
    {
        conpid();

        outspid("Out2.PID.I "+arg1);
        outspid("Out1.PID.I "+arg1);

        clopid();
    }
}



void controlpid::on_I300_valueChanged(const QString &arg1)
{
    i300=arg1.toDouble();

    if(setpt>=250 and setpt<300)
    {
        conpid();

        outspid("Out2.PID.I "+arg1);
        outspid("Out1.PID.I "+arg1);

        clopid();
    }
}

void controlpid::on_I350_valueChanged(const QString &arg1)
{
    i350=arg1.toDouble();

    if(setpt>=300 and setpt<350)
    {
        conpid();

        outspid("Out2.PID.I "+arg1);
        outspid("Out1.PID.I "+arg1);

        clopid();
    }
}

void controlpid::on_I400_valueChanged(const QString &arg1)
{
    i400=arg1.toDouble();

    if(setpt>=350)
    {
        conpid();

        outspid("Out2.PID.I "+arg1);
        outspid("Out1.PID.I "+arg1);

        clopid();
    }
}

void controlpid::on_D150_valueChanged(const QString &arg1)
{
    d150=arg1.toDouble();

    if(setpt<150)
    {
        conpid();

        outspid("Out2.PID.D "+arg1);
        outspid("Out1.PID.D "+arg1);

        clopid();
    }
}

void controlpid::on_D200_valueChanged(const QString &arg1)
{
    d200=arg1.toDouble();

    if(setpt>=150 and setpt<200)
    {
        conpid();

        outspid("Out2.PID.D "+arg1);
        outspid("Out1.PID.D "+arg1);

        clopid();
    }
}

void controlpid::on_D250_valueChanged(const QString &arg1)
{
    d250=arg1.toDouble();

    if(setpt>=200 and setpt<250)
    {
        conpid();

        outspid("Out2.PID.D "+arg1);
        outspid("Out1.PID.D "+arg1);

        clopid();
    }
}

void controlpid::on_D300_valueChanged(const QString &arg1)
{
    d300=arg1.toDouble();

    if(setpt>=250 and setpt<300)
    {
        conpid();

        outspid("Out2.PID.D "+arg1);
        outspid("Out1.PID.D "+arg1);

        clopid();
    }
}

void controlpid::on_D350_valueChanged(const QString &arg1)
{
    d350=arg1.toDouble();

    if(setpt>=300 and setpt<350)
    {
        conpid();

        outspid("Out2.PID.D "+arg1);
        outspid("Out1.PID.D "+arg1);

        clopid();
    }
}

void controlpid::on_D400_valueChanged(const QString &arg1)
{
    d400=arg1.toDouble();

    if(setpt>=350)
    {
        conpid();

        outspid("Out2.PID.D "+arg1);
        outspid("Out1.PID.D "+arg1);

        clopid();
    }
}

void controlpid::on_pstat_valueChanged(const QString &arg1)
{
    conpid();

    outspid("Out2.PID.P "+arg1);
    outspid("Out1.PID.P "+arg1);

    clopid();
}

void controlpid::on_pint_valueChanged(const QString &arg1)
{
    conpid();

    outspid("Out2.PID.I "+arg1);
    outspid("Out1.PID.I "+arg1);

    clopid();
}

void controlpid::on_pDIff_valueChanged(const QString &arg1)
{
    conpid();

    outspid("Out2.PID.D "+arg1);
    outspid("Out1.PID.D "+arg1);

    clopid();
}
