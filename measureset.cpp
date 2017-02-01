#include "measureset.h"
#include "ui_measureset.h"
#include "allfun.h"
#include <QDebug>
#include <QInputDialog>
measureset::measureset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::measureset)
{
   // qDebug()<<"%%%%";
    ui->setupUi(this);


    sta();

    read("ANA:PROP1?");
    read("ANA:PROP2?");
    read("ANA:EQU-CCT?");
    read("ANA:SPEED?");
    read("ANA:RANGE?");
    read("ANA:LEVEL?");
    read("ANA:DRIVE?");
    read("ANA:BIAS-TYPE?");
    read("ANA:BIAS?");

    sto();

    QFile file("/home/phy/ControlX/wk.txt");

    QVector< QString > v;

    file.open(QIODevice::ReadOnly);

    while(!file.atEnd())
    {
        char a[1025];

            file.readLine(a,sizeof(a));

            if(a[0]=='r' and a[1]=='e')
            {
                QString temp;

                int x=strlen(a);

                for(int i=18;i<x-2;i++)
                {
                    temp=temp+a[i];

                }

                v.push_back(temp);
                qDebug()<<temp;
            }
    }

    ui->trace1->setCurrentIndex(v[0].toInt());
    ui->trace2->setCurrentIndex(v[1].toInt());
    ui->combi->setCurrentIndex(v[2].toInt());
    ui->speed->setCurrentIndex(qMin(v[3].toInt()+4,4));
    ui->range->setCurrentIndex(v[4].toInt());
    ui->doubleSpinBox->setValue(v[5].toDouble());
    ui->comboBox->setCurrentIndex(v[6].toInt());
    ui->comboBox_3->setCurrentIndex(v[7].toInt());

    if(v[7]=="0")
    ui->pushButton->setText("C");
    else
    ui->pushButton->setText("V");

    ui->doubleSpinBox_2->setValue(v[8].toDouble());




}

measureset::~measureset()
{
    delete ui;
}

void measureset::on_buttonBox_accepted()
{

}

void measureset::on_buttonBox_rejected()
{

}

void measureset::on_speed_activated(const QString &arg1)
{

}

void measureset::on_range_activated(const QString &arg1)
{
    sta();
    write("ANA:RANGE "+arg1);
    sto();
}

void measureset::on_combi_activated(const QString &arg1)
{

}

void measureset::on_trace2_activated(const QString &arg1)
{
    sta();
    write("ANA:PROP2 "+arg1);
    sto();
}

void measureset::on_trace1_activated(const QString &arg1)
{
    sta();
    write("ANA:PROP1 "+arg1);
    sto();
}

void measureset::on_combi_activated(int index)
{
    sta();

    if(index==0)
    write("ANA:EQU-CCT SER");
    else
    write("ANA:EQU-CCT PAR");

    sto();
}

void measureset::on_speed_activated(int index)
{
    sta();

    if(index==0)
    write("ANA:SPEED MAX");
    else
    if(index==1)
    write("ANA:SPEED FAST");
    else
    if(index==2)
    write("ANA:SPEED MED");
    else
    if(index==3)
    write("ANA:SPEED SLOW");
    else
    {
          QString x=QInputDialog::getText(this,"Enter Speed","Enter Speed");

          write("ANA:SPEED "+x);
    }

    sto();
}





void measureset::on_doubleSpinBox_valueChanged(const QString &arg1)
{
    sta();
    write("ANA:LEVEL "+arg1+ui->comboBox->currentText());
    sto();
}

void measureset::on_comboBox_activated(const QString &arg1)
{
    sta();
    write("ANA:LEVEL "+ui->doubleSpinBox->text()+arg1);
    sto();
}

void measureset::on_comboBox_3_activated(int index)
{
    sta();



    if(index==0)
    {  write("ANA:BIAS-TYPE CUR"); ui->pushButton->setText("C");}
    else
    {   write("ANA:BIAS-TYPE VOL"); ui->pushButton->setText("V");}

    write("ANA:BIAS "+ui->doubleSpinBox_2->text());

    sto();
}

void measureset::on_doubleSpinBox_2_valueChanged(const QString &arg1)
{
    sta();
    write("ANA:BIAS "+arg1);
    sto();
}
