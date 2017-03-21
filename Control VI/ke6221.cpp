#include "ke6221.h"
#include "ui_ke6221.h"
#include "scriptwrite2.h"
#include <QString>
#include <QVector>
QVector< QString > vectke;
QString ranges[9]={"2E-9","20E-9","200E-9","2E-6","20E-6","200E-6","2E-3","20E-3","100E-3"};
QString units[3]={"e-3","e-6","e-9"};
void readfileke()
{
    QFile file("/home/phy/ControlVI/wk.txt");

    vectke.clear();

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

                    vectke.push_back(temp);
            }
    }
}
bool OutputStatus,filter;
QString command;
ke6221::ke6221(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ke6221)
{
    ui->setupUi(this);
    start_connection();
    read_string("OUTP?");
    read_string("SOUR:CURR:FILT?");
    read_string("SOUR:CURR?");
    read_string("SOUR:CURR:RANG?");
    read_string("SOUR:CURR:RANG:AUTO?");
    stop_connection();

    readfileke();

    if(vectke[0]=="1")
        ui->Output->setStyleSheet("background-color:red"),OutputStatus=true;
    if(vectke[1]=="1")
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->SetFilter->setIcon(ButtonIcon);
        ui->SetFilter->setIconSize(QSize(61,31));
        filter=true;
    }
    if(vectke[4]=="1")
    {
        ui->groupBox->setVisible(false);
        ui->groupBox->setEnabled(false);
    }
    else
    {
        ui->groupBox->setVisible(true);
        ui->groupBox->setEnabled(true);
    }

}

ke6221::~ke6221()
{
    delete ui;
}

void ke6221::on_Output_clicked()
{
    if(OutputStatus==0)
    {
        command="OUTP ON";     //
        start_connection();
        write_command(command);
        stop_connection();

        ui->Output->setStyleSheet("background-color:red");
    }
    else
    {
        command="OUTP OFF";     //
        start_connection();
        write_command(command);
        stop_connection();

         ui->Output->setStyleSheet("background-color:black");
    }
    OutputStatus=!OutputStatus;
}

void ke6221::on_SetFilter_clicked()
{

    if(filter==1)
    {
        command="SOUR:CURR:FILT 0";     //
        start_connection();
        write_command(command);
        stop_connection();

        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->SetFilter->setIcon(ButtonIcon);
        ui->SetFilter->setIconSize(QSize(61,31));
    }
    else
    {
        command="SOUR:CURR:FILT 1";     //
        start_connection();
        write_command(command);
        stop_connection();

        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->SetFilter->setIcon(ButtonIcon);
        ui->SetFilter->setIconSize(QSize(61,31));
    }

            filter=!filter;

}

void ke6221::on_RangeType_currentIndexChanged(const QString &arg1)
{

    if(arg1=="Manual")             //Manual
    {
        command="SOUR:CURR:RANG:AUTO 0";     //Command Auto off
        start_connection();
        write_command(command);
        stop_connection();


        ui->groupBox->setVisible(true);
        ui->groupBox->setEnabled(true);
    }
    else            //Auto
    {
        command="SOUR:CURR:RANG:AUTO 1";     //Command for auto
        start_connection();
        write_command(command);
        stop_connection();

        ui->groupBox->setVisible(false);
        ui->groupBox->setEnabled(false);
    }
}

void ke6221::on_SetAmplitude_valueChanged(QString arg1)
{
    command="SOUR:CURR "+arg1+units[ui->RangeType_2->currentIndex()];     // Command to set amplitude
    start_connection();
    write_command(command);
    stop_connection();
}



void ke6221::on_SetAmplitude_valueChanged(double arg1)
{
    current = arg1;
}

void ke6221::on_SetRange_currentIndexChanged(int index)
{
    command="SOUR:CURR:RANG "+ranges[index];     // Command to set amplitude
    start_connection();
    write_command(command);
    stop_connection();
}

void ke6221::on_RangeType_2_currentIndexChanged(int index)
{
    double val=ui->SetAmplitude->value();

    command="SOUR:CURR "+QString::number(val)+units[index];     // Command to set amplitude
    start_connection();
    write_command(command);
    stop_connection();
}

void ke6221::on_ok_clicked()
{
    //ui->hide();
}
