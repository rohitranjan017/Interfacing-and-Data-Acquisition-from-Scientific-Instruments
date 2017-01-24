#include "traceset.h"
#include "ui_traceset.h"
#include "allfun3.h"
#include <QDebug>
#define sta sta3
#define sto sto3
#define read read3
#define write write3
traceset::traceset(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::traceset)
{
    ui->setupUi(this);

    sta();

    read("ANA:START?");
    read("ANA:STOP?");
    read("ANA:LOG-X?");
    read("ANA:POINTS?");
    read("ANA:AVERAGES?");

    sto();

    QFile file("/home/dell/build-CTC100-Desktop_Qt_5_7_0_GCC_64bit-Debug/o.txt");

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
            }
    }

    QString temp,exp; int i;

    for( i=0;v[0][i]!='e';i++)
        temp=temp+v[0][i];

    for(i=i+2;i<v[0].size();i++)
        exp=exp+v[0][i];

    int p=exp.toInt();
   // qDebug()<<temp;
    float f=temp.toFloat();
    while(p--)
    {
        f*=10;
    }

     ui->spinBox->setValue(f);

    QString tem,ex;

    for( i=0;v[1][i]!='e';i++)
        tem=tem+v[1][i];

    for(i=i+2;i<v[1].size();i++)
        ex=ex+v[1][i];

     p=ex.toInt();
   // qDebug()<<temp;
     f=temp.toFloat();
    while(p--)
    {
        f*=10;
    }



   ui->spinBox_2->setValue(f);

    if(v[2]=="1")
        ui->checkBox->setChecked(true);

    ui->comboBox_4->setCurrentText(v[3]);
   ui->spinBox_3->setValue(v[4].toInt());

}

traceset::~traceset()
{
    delete ui;
}

void traceset::on_buttonBox_accepted()
{

}

void traceset::on_spinBox_valueChanged(const QString &arg1)
{
    sta();
    write("ANA:START "+arg1);
    sto();

}

void traceset::on_spinBox_2_valueChanged(const QString &arg1)
{
    sta();
    write("ANA:STOP "+arg1);
    sto();
}

void traceset::on_checkBox_clicked()
{
    sta();
    if(ui->checkBox->isChecked())
    write("ANA:LOG-X ON");
    else
    write("ANA:LOG-X OFF");
    sto();
}

void traceset::on_comboBox_4_activated(const QString &arg1)
{
    sta();
    write("ANA:POINTS "+arg1);
    sto();
}

void traceset::on_spinBox_3_valueChanged(const QString &arg1)
{
    sta();
    write("ANA:AVERAGES "+arg1);
    sto();
}
