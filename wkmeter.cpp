#include "wkmeter.h"
#include "ui_wkmeter.h"
#include "wk.h"
#include "allfun5.h"
#define sta sta5
#define sto sto5
#define read read5
#define write write5
bool bias=0;
wkmeter::wkmeter(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wkmeter)
{
    ui->setupUi(this);
    this->setWindowTitle("Meter Mode");

    sta();
    read("ANA:BIAS-STAT?");
    sto();

    QFile file("/home/dell/build-CTC100-Desktop_Qt_5_8_0_GCC_64bit-Debug/wk.txt");

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
                //qDebug()<<temp;
            }
    }

    if(v[0][0]=="0")
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton->setIcon(ButtonIcon);
        ui->pushButton->setIconSize(QSize(61,31));
        bias=1;
    }
    else
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton->setIcon(ButtonIcon);
        ui->pushButton->setIconSize(QSize(61,31));
        bias=0;
    }
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

void wkmeter::on_pushButton_2_clicked()
{
    if(bias==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton->setIcon(ButtonIcon);
        ui->pushButton->setIconSize(QSize(61,31));
        bias=0;
        sta();
        write("ANA:BIAS-STAT OFF");
        sto();

    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton->setIcon(ButtonIcon);
        ui->pushButton->setIconSize(QSize(61,31));
        bias=1;
        sta();
        write("ANA:BIAS-STAT ON");
        sto();

    }
}
