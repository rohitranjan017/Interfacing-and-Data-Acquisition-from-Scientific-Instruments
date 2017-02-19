#include "ke2182a.h"
#include "ui_ke2182a.h"

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
