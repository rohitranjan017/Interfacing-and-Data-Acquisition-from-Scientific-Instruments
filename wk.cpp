#include "wk.h"
#include "ui_wk.h"
#include "measureset.h"
#include "traceset.h"
#include "wkmeter.h"
#include "QFile"
#include "QTextStream"
#include <QDebug>
wk::wk(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wk)
{

    ui->setupUi(this);


}

wk::~wk()
{
    delete ui;

}

void wk::on_pushButton_2_clicked()
{
   wkmeter *ptr;
   ptr =new wkmeter;
    ptr->show();
    hide();
}

void wk::on_meas_setup_clicked()
{
    measureset* ptr;
    ptr= new measureset;
    ptr->show();
}

void wk::on_trace_setup_clicked()
{
    traceset* ptr;
    ptr=new traceset;
    ptr->show();
}
