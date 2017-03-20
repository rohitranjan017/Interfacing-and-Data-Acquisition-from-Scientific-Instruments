#include "ke6221.h"
#include "ui_ke6221.h"
#include "Scriptwrite.h"
ke6221::ke6221(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ke6221)
{
    ui->setupUi(this);
}
bool OutputStatus,filter;
ke6221::~ke6221()
{
    delete ui;
}

void ke6221::on_Output_clicked()
{
    if(OutputStatus==0)
    {
        OutputStatus=!OutputStatus;
        ui->Output->setStyleSheet("background-color:red");
    }
    else
    {
         OutputStatus=!OutputStatus;
         ui->Output->setStyleSheet("background-color:black");
    }
}

void ke6221::on_SetFilter_2_clicked()
{

    if(filter==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->SetFilter_2->setIcon(ButtonIcon);
        ui->SetFilter_2->setIconSize(QSize(61,31));
        filter=!filter;
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->SetFilter_2->setIcon(ButtonIcon);
        ui->SetFilter_2->setIconSize(QSize(61,31));
        filter=!filter;
    }


}

void ke6221::on_RangeType_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Select")
    {
        ui->groupBox->setVisible(false);
    }
    else if(arg1=="manual")
    {
        ui->groupBox->setVisible(true);
        ui->groupBox->setEnabled(true);
    }
    else
    {
        ui->groupBox->setVisible(false);
        ui->groupBox->setEnabled(false);
    }
}
