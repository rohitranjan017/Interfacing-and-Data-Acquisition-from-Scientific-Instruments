#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
char c1='R',c2='R',c3='R',c4='R';
bool z;
bool mode1;
bool mode2;
bool inmode1,inmode2,inmode3,inmode4;
QString v[11]={ "10ê", "30ê", "100ê", "300ê", "1kê", "3kê", "10kê", "30kê", "100kê",
                "300kê","Auto" };
QFile file("script.sh");
QTextStream out(&file);
void con()
{
    //conecting code starts

   file.open(QIODevice::WriteOnly| QIODevice::Text);

   out<<"#!/usr/bin/expect\n";
   out<<"spawn telnet 100.10.19.37\n";
   out<<"sleep 1\n";
   out<<"send ";
   out<<"\"";
   out<<"\\n";
   out<<"\"";
   out<<"\n";
   out<<"send ";
   out<<"\"";
   out<<"\\n";
   out<<"\"";
   out<<"\n";
   //connecting code ends
}
void clo()
{

    //connection terminating code starts//
    out<<"sleep 1\n";
    out<<"send ";
    out<<"\"";
    out<<"\\";
    out<<"x1D";
    out<<"\\n";
    out<<"\"";
    out<<"\n";

    out<<"send ";
    out<<"\"quit";
    out<<"\\n";
    out<<"\"";
    out<<"\n";
    out<<"send ";
    out<<"\"";
    out<<"\\";
    out<<"x1D";
    out<<"\\n";
    out<<"\"";
    out<<"\n";
    out<<"expect ";
    out<<"\"";
    out<<"telnet> ";
    out<<"\"";
    out<<"\n";
    out<<"send ";
    out<<"\"quit";
    out<<"\\n";
    out<<"\"";
    out<<"\n";

    out<<"interact\n";
    //connection terminating code ends//
    file.close();
    system("script -c ./script.sh o.txt");

}
void pre()
{
    out<<"send ";
    out<<"\"";
}
void post()
{
    out<<"\\n";
    out<<"\"";
    out<<"\n";
}
void outs(QString s)
{
    pre();
    out<<s;
    post();
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0;i<11;i++)
    {
           ui->comboBox_8->addItem(v[i]);
           ui->comboBox_16->addItem(v[i]);
           ui->comboBox_24->addItem(v[i]);
           ui->comboBox_22->addItem(v[i]);
    }
   
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    if(z==0)
    {
        ui->pushButton_2->setStyleSheet("background-color:red");

            con();


           outs("outputEnable = on");


           clo();

        QMessageBox::information(this,"OUTPUT","Ouput Enabled");

    }
    else
    {
            ui->pushButton_2->setStyleSheet("background-color:black");

            con();

           outs("outputEnable = off");



           clo();

            QMessageBox::information(this,"OUTPUT","Ouput Disabled");
    }

    z=!z;
}

void MainWindow::on_connect_clicked()
{
    con();
   //Output1
       outs("Out1.PID.mode?");
       outs("Out1.Range?");
       outs("Out1.LowLmt?");
       outs("Out1.HiLmt?");
       outs("Out1.PID.Input?");
       outs("Out1.PID.Setpoint?");
       outs("Out1.PID.ramp?");
       outs("Out1.PID.P?");
       outs("Out1.PID.I?");
       outs("Out1.PID.D?");
   //Output2
       outs("Out2.PID.mode?");
       outs("Out2.Range?");
       outs("Out2.LowLmt?");
       outs("Out2.HiLmt?");
       outs("Out2.PID.Input?");
       outs("Out2.PID.Setpoint?");
       outs("Out2.PID.ramp?");
       outs("Out2.PID.P?");
       outs("Out2.PID.I?");
       outs("Out2.PID.D?");
   //Input1
       outs("In1.selected?");
       outs("In1.Sensor?");
       outs("In1.Range?");
   //Input2
       outs("In2.selected?");
       outs("In2.Sensor?");
       outs("In2.Range?");
   //Input3
       outs("In3.selected?");
       outs("In3.Sensor?");
       outs("In3.Range?");
   //Input4
       outs("In4.selected?");
       outs("In4.Sensor?");
       outs("In4.Range?");

       ui->connect->setStyleSheet("background-color:green");

       outs("popup CONNECTED!!!");

       clo();

       QFile file("/home/build-CTC100-Desktop_Qt_5_7_1_GCC_64bit-Debug/o.txt");

     QString s[40];
     int j=0;
       file.open(QIODevice::ReadOnly);

         while (!file.atEnd())
         {

                  char a[1025];

                      file.readLine(a,sizeof(a));

                      QString temp;

                      for(uint i=0;i<qstrlen(a)-3;i++)
                       temp=temp+a[i];
                     // qDebug()<<temp;

                      if(temp=="Error: \"Ã»Ã»\" is not a valid instruction")
                      {
                          int k=0;

                         while(k<32)
                         {
                                file.readLine(a,sizeof(a));





                                 for(uint i=0;i<qstrlen(a)-3;i++)
                                 s[j]=s[j]+a[i];

                               j++;

                               qDebug()<<s[j-1];


                             k++;
                         }

                         break;
                      }

         }
   //Output1

         if(s[0]=="On")
         {
             mode1=1;

             on_out1mode_clicked();
         }

         ui->comboBox->setCurrentText(s[1]);

         ui->doubleSpinBox->setValue(s[2].toDouble());

         ui->doubleSpinBox_2->setValue(s[3].toDouble());

         ui->comboBox_2->setCurrentText(s[4]);

         ui->doubleSpinBox_6->setValue(s[5].toDouble());

         ui->doubleSpinBox_9->setValue(s[6].toDouble());

         ui->doubleSpinBox_11->setValue(s[7].toDouble());

         ui->doubleSpinBox_12->setValue(s[8].toDouble());

         ui->doubleSpinBox_13->setValue(s[9].toDouble());

   //Output2

         if(s[10]=="On")
         {
             mode2=1;

             on_out2mode_clicked();
         }

         ui->comboBox_5->setCurrentText(s[11]);

         ui->doubleSpinBox_14->setValue(s[12].toDouble());

         ui->doubleSpinBox_15->setValue(s[13].toDouble());

         ui->comboBox_6->setCurrentText(s[14]);

         ui->doubleSpinBox_17->setValue(s[15].toDouble());

         ui->doubleSpinBox_20->setValue(s[16].toDouble());

         ui->doubleSpinBox_22->setValue(s[17].toDouble());

         ui->doubleSpinBox_23->setValue(s[18].toDouble());

         ui->doubleSpinBox_24->setValue(s[19].toDouble());

   //Input1
         if(s[20]=="On")
         {
             inmode1=1;
             on_out2mode_2_clicked();
         }
         ui->comboBox_7->setCurrentText(s[21]);

         ui->comboBox_8->setCurrentText(s[22]);

   //Input2
         if(s[23]=="On")
         {
             inmode2=1;
             on_out2mode_6_clicked();
         }
         ui->comboBox_15->setCurrentText(s[24]);

         ui->comboBox_16->setCurrentText(s[25]);
   //Input3
         if(s[26]=="On")
         {
             inmode3=1;
             on_out2mode_10_clicked();
         }
         ui->comboBox_23->setCurrentText(s[27]);

         ui->comboBox_24->setCurrentText(s[28]);
   //Input4
         if(s[29]=="On")
         {
             inmode4=1;
             on_out2mode_9_clicked();
         }
         ui->comboBox_21->setCurrentText(s[30]);

         ui->comboBox_22->setCurrentText(s[31]);

    QMessageBox::StandardButton reply;

     reply = QMessageBox::information(this, "Status", "CONNECTED!!!",
                                   QMessageBox::Ok);
     if (reply == QMessageBox::Ok) {




         con();

         outs("popup.close");

         clo();


     }




}

void MainWindow::on_out1mode_clicked()
{
    if(mode1==0)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out1mode->setIcon(ButtonIcon);
        ui->out1mode->setIconSize(QSize(61,31));

       con();
       outs("Out1.PID.mode = on");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out1mode->setIcon(ButtonIcon);
        ui->out1mode->setIconSize(QSize(61,31));

        con();
        outs("Out1.PID.mode = off");
        clo();
    }

    mode1=!mode1;
}

void MainWindow::on_comboBox_currentIndexChanged(const QString &arg1)
{
    con();

    QString s="\\";
    s+= "\"" + arg1+"\\"+"\"";

    outs("Out1.Range = "+s);



    clo();
}

void MainWindow::on_doubleSpinBox_valueChanged(const QString &arg1)
{
    con();

    outs("Out1.LowLmt "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_2_valueChanged(const QString &arg1)
{
    con();

    outs("Out1.HiLmt "+arg1);

    clo();
}


void MainWindow::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    con();

    QString s="\\";
    s+= "\"" + arg1+"\\"+"\"";

    outs("Out1.PID.Input = "+s);


    clo();
}

void MainWindow::on_doubleSpinBox_6_valueChanged(const QString &arg1)
{
    con();

    outs("Out1.PID.setpoint "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_9_valueChanged(const QString &arg1)
{
    con();

    outs("Out1.PID.ramp "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_11_valueChanged(const QString &arg1)
{
    con();

    outs("Out1.PID.P "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_12_valueChanged(const QString &arg1)
{
    con();

    outs("Out1.PID.I "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_13_valueChanged(const QString &arg1)
{
    con();

    outs("Out1.PID.D "+arg1);

    clo();
}

void MainWindow::on_out2mode_clicked()
{
    if(mode2==0)
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode->setIcon(ButtonIcon);
        ui->out2mode->setIconSize(QSize(61,31));

       con();
       outs("Out2.PID.mode = on");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode->setIcon(ButtonIcon);
        ui->out2mode->setIconSize(QSize(61,31));

        con();
        outs("Out2.PID.mode = off");
        clo();
    }

    mode2=!mode2;
}

void MainWindow::on_comboBox_5_currentIndexChanged(const QString &arg1)
{
    con();

    QString s="\\";
    s+= "\"" + arg1+"\\"+"\"";

    outs("Out2.Range = "+s);

    clo();
}

void MainWindow::on_doubleSpinBox_14_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.LowLmt "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_15_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.HiLmt "+arg1);

    clo();
}

void MainWindow::on_comboBox_6_currentIndexChanged(const QString &arg1)
{
    con();

    QString s="\\";
    s+= "\"" + arg1+"\\"+"\"";

    outs("Out2.PID.Input = "+s);


    clo();
}


void MainWindow::on_doubleSpinBox_17_valueChanged(const QString &arg1)
{
        con();

    outs("Out2.PID.setpoint "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_20_valueChanged(const QString &arg1)
{

    con();

    outs("Out1.PID.ramp "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_22_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.PID.P "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_23_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.PID.I "+arg1);

    clo();
}

void MainWindow::on_doubleSpinBox_24_valueChanged(const QString &arg1)
{
    con();

    outs("Out2.PID.D "+arg1);

    clo();
}

void MainWindow::on_out2mode_2_clicked()
{
    if(inmode1==0)
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_2->setIcon(ButtonIcon);
        ui->out2mode_2->setIconSize(QSize(61,31));

       con();
       outs("In1.selected(on)");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_2->setIcon(ButtonIcon);
        ui->out2mode_2->setIconSize(QSize(61,31));

        con();
        outs("In1.selected = off");
        clo();
    }

    inmode1=!inmode1;
}

void MainWindow::on_out2mode_6_clicked()
{
    if(inmode2==0)
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_6->setIcon(ButtonIcon);
        ui->out2mode_6->setIconSize(QSize(61,31));

       con();
       outs("In2.selected(on)");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_6->setIcon(ButtonIcon);
        ui->out2mode_6->setIconSize(QSize(61,31));

        con();
        outs("In2.selected = off");
        clo();
    }

    inmode2=!inmode2;
}

void MainWindow::on_out2mode_10_clicked()
{
    if(inmode3==0)
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_10->setIcon(ButtonIcon);
        ui->out2mode_10->setIconSize(QSize(61,31));

       con();
       outs("In3.selected(on)");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_10->setIcon(ButtonIcon);
        ui->out2mode_10->setIconSize(QSize(61,31));

        con();
        outs("In3.selected = off");
        clo();
    }

    inmode3=!inmode3;
}

void MainWindow::on_out2mode_9_clicked()
{
    if(inmode4==0)
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_9->setIcon(ButtonIcon);
        ui->out2mode_9->setIconSize(QSize(61,31));

       con();
       outs("In4.selected(on)");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_9->setIcon(ButtonIcon);
        ui->out2mode_9->setIconSize(QSize(61,31));

        con();
        outs("In4.selected = off");
        clo();
    }

    inmode4=!inmode4;
}

void MainWindow::on_comboBox_7_currentIndexChanged(const QString &arg1)
{
       if(arg1=="Diode")
       {
            for(int i=0;i<11;i++)
                ui->comboBox_8->removeItem(0);

                ui->comboBox_8->addItem("2.5V");
            c1='D';
       }
       else if(c1=='D')
       {
           ui->comboBox_8->removeItem(0);

           for(int i=0;i<11;i++)
           {
                  ui->comboBox_8->addItem(v[i]);
           }


           c1='R';
       }

       con();

       outs("In1.Sensor = "+arg1);

       clo();
}

void MainWindow::on_comboBox_15_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Diode")
    {
         for(int i=0;i<11;i++)
             ui->comboBox_16->removeItem(0);

             ui->comboBox_16->addItem("2.5V");
         c2='D';
    }
    else if(c2=='D')
    {
        ui->comboBox_16->removeItem(0);

        for(int i=0;i<11;i++)
        {
               ui->comboBox_16->addItem(v[i]);
        }


        c2='R';
    }

    con();

    outs("In2.Sensor = "+arg1);

    clo();
}


void MainWindow::on_comboBox_23_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Diode")
    {
         for(int i=0;i<11;i++)
             ui->comboBox_24->removeItem(0);

             ui->comboBox_24->addItem("2.5V");
         c3='D';
    }
    else if(c3=='D')
    {
        ui->comboBox_24->removeItem(0);

        for(int i=0;i<11;i++)
        {
               ui->comboBox_24->addItem(v[i]);
        }


        c3='R';
    }

    con();

    outs("In3.Sensor = "+arg1);

    clo();
}



void MainWindow::on_comboBox_21_currentIndexChanged(const QString &arg1)
{
    if(arg1=="Diode")
    {
         for(int i=0;i<11;i++)
             ui->comboBox_22->removeItem(0);

             ui->comboBox_22->addItem("2.5V");
         c4='D';
    }
    else if(c4=='D')
    {
        ui->comboBox_22->removeItem(0);

        for(int i=0;i<11;i++)
        {
               ui->comboBox_22->addItem(v[i]);
        }


        c4='R';
    }

    con();

    outs("In4.Sensor = "+arg1);

    clo();
}


void MainWindow::on_comboBox_8_activated(const QString &arg1)
{
    con();

    outs("In1.Range = "+arg1);

    clo();
}

void MainWindow::on_comboBox_24_activated(const QString &arg1)
{
    con();

    outs("In2.Range = "+arg1);

    clo();
}

void MainWindow::on_comboBox_16_activated(const QString &arg1)
{
    con();

    outs("In3.Range = "+arg1);

    clo();
}

void MainWindow::on_comboBox_22_activated(const QString &arg1)
{
    con();

    outs("In4.Range = "+arg1);

    clo();
}
