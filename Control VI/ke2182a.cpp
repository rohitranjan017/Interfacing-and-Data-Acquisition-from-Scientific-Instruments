#include "ke2182a.h"
#include "ui_ke2182a.h"
QString unit[3]={"e-3","e-6","e-9"};
ke2182a::ke2182a(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ke2182a)
{
    ui->setupUi(this);

}

ke2182a::~ke2182a()
{
    delete ui;
}

void ke2182a::on_NoofPoints_valueChanged(double arg1)
{
    total_points= (int)arg1;
}

void ke2182a::on_ok_clicked()
{
  //  ui->hide();
}

void ke2182a::on_NoofPoints_2_valueChanged(double arg1)
{
    sample_points=(int)arg1;
}

void ke2182a::on_SetAmplitude_valueChanged(const QString &arg1)
{
    arg1+=unit[ui->RangeType_2->currentIndex()];
    lo_lmt=arg1.toDouble();
}

void ke2182a::on_RangeType_2_currentIndexChanged(int index)
{
    QString temp=QString::number(ui->SetAmplitude->value)+unit[index];
    lo_lmt=temp.toDouble();

}

void ke2182a::on_SetAmplitude_2_valueChanged(const QString &arg1)
{
    arg1+=unit[ui->RangeType_3->currentIndex()];
    hi_lmt=arg1.toDouble();
}

void ke2182a::on_RangeType_3_currentIndexChanged(int index)
{
    QString temp=QString::number(ui->SetAmplitude_2->value)+unit[index];
    hi_lmt=temp.toDouble();
}

void ke2182a::on_NoofPoints_3_valueChanged(double arg1)
{
    total_points2=(int)arg1;
}

void ke2182a::on_radioButton_clicked()
{
    mode=0;
}

void ke2182a::on_radioButton_2_clicked()
{
    mode=1;
}
