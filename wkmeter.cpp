#include "wkmeter.h"
#include "ui_wkmeter.h"
#include "wk.h"
wkmeter::wkmeter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wkmeter)
{
    ui->setupUi(this);
}

wkmeter::~wkmeter()
{
    delete ui;
}

void wkmeter::on_pushButton_clicked()
{
    wk* ptr;
    ptr=new wk;
    ptr->show();
    hide();
}
