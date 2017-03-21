#include "ke6221.h"
#include "ui_ke6221.h"
#include "scriptwrite2.h"
#include <QString>
ke6221::ke6221(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ke6221)
{
    ui->setupUi(this);
}
bool OutputStatus,filter;
QString command;
ke6221::~ke6221()
{
    delete ui;
}

void ke6221::on_Output_clicked()
{
    if(OutputStatus==0)
    {
        command="";     //
        start_connection();
        write_command(command);
        stop_connection();

        ui->Output->setStyleSheet("background-color:red");
    }
    else
    {
        command="";     //
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
        command="";     //
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
        command="";     //
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
    if(arg1=="Select")              //Default
    {
        ui->groupBox->setVisible(false);
    }
    else if(arg1=="manual")             //Manual
    {
        command="";     //Command Auto off
        start_connection();
        write_command(command);
        stop_connection();


        ui->groupBox->setVisible(true);
        ui->groupBox->setEnabled(true);
    }
    else            //Auto
    {
        command="";     //Command for auto
        start_connection();
        write_command(command);
        stop_connection();


        ui->groupBox->setVisible(false);
        ui->groupBox->setEnabled(false);
    }
}

void ke6221::on_SetAmplitude_valueChanged(QString arg1)
{
    command="";     // Command to set amplitude
    start_connection();
    write_command(command);
    stop_connection();
}

void ke6221::on_SetRange_currentIndexChanged(const QString &arg1)
{
    command="";     //  Command to set range
    start_connection();
    write_command(command);
    stop_connection();

}

void ke6221::on_SetAmplitude_valueChanged(double arg1)
{
    current = arg1;
}
