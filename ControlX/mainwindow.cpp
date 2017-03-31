#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTime>
#include "allfun6.h"
#include <QPixmap>
#include <QSplineSeries>
#include <QPair>
#include <QProgressDialog>
#define sta sta6
#define sto sto6
#define read read6
#define write write6
#define props prop
#define vec vect
#define readfile readfiles
qreal m [11],M[11]; int pts[11];
QString folder;
QFile fit("/home/phy/ControlX/check.txt");
QString propy[11]={"Inductance","Capacitance","Q-factor","D-factor","Resistance","Reactance","Impedance","Admittance","Angle","Susceptance","Conductance"};
void delay( int millisecondsToWait )
{
    millisecondsToWait*=1000;

    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
QVector< QString > vect;
QVector <QPointF > points[11];
int tot; int startx;
char c1='R',c2='R',c3='R',c4='R';
bool z; bool flag;
bool mode1;
bool mode2;
bool mode3;
bool mode4;
bool inmode1,inmode2,inmode3,inmode4;
QString v[11]={ "10ê", "30ê", "100ê", "300ê", "1kê", "3kê", "10kê", "30kê", "100kê",
                "300kê","Auto" };
QString prop[12]={"L","C","Q","D","R","X","Z","Y","Angle","B","G","L"};
QFile file("/home/phy/ControlX/script.sh");
QTextStream out(&file);
QList <double> setpoints;
bool MainWindow::checkset(int out)
{
    if(setpoints.size()==5)
    {
        auto mm = std::minmax_element(setpoints.begin(), setpoints.end());

        fit.open(QIODevice::Append);
        QTextStream foo(&fit);

        foo<<*mm.second-*mm.first<<endl;

        if(out==1)
        {
            if(*mm.second-*mm.first<=ui->doubleSpinBox_25->value())
                return true;
            else
                return false;

        }
        else
        {
            if(*mm.second-*mm.first<=ui->doubleSpinBox_38->value())
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

void con(bool sig=false)
{
    //conecting code starts

   file.open(QIODevice::WriteOnly| QIODevice::Text);

   out<<"#!/usr/bin/expect\n";
   out<<"spawn telnet 100.10.19.37\n";
   if(sig==true)
       out<<"sleep 0.55\n";
   else
   out<<"sleep 0.4\n";
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
void clo(bool sig=false)
{

    //connection terminating code starts//

    if(sig==true)
        out<<"sleep 0.55\n";
    else
    out<<"sleep 0.4\n";
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
    system("script -c /home/phy/ControlX/./script.sh /home/phy/ControlX/ctc.txt");

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

void readfiles()
{
    QFile file("/home/phy/ControlX/wk.txt");

    vec.clear();

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

                    if(temp=="'" or temp=="No data")
                        vec.push_back("NA,NA             ");
                    else
                    vec.push_back(temp);
                //qDebug()<<temp;
            }
    }
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

    timer=new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(showtime()));

    /*QString daf="-4.17010701e+007";
    double asfa=daf.toDouble();
    qreal adfsd=qreal(asfa);
*/



   /* ptr->series[5]->append(40,adfsd);
    ptr->chart[5]->axisY()->setRange(adfsd+adfsd/2,adfsd-adfsd/2);*/

    //Graphs...1




    for(int i=0;i<11;i++){
    series[i] = new QLineSeries();
    chart[i] = new QChart();
    axisX[i] = new QValueAxis();
    axisY[i] = new QValueAxis();
    series[i]->setName(propy[i]+" Vs Temperature");
    series[i]->setPointsVisible(true);

    chart[i]->addSeries(series[i]);


    chart[i]->addAxis(axisY[i], Qt::AlignLeft);
    chart[i]->setAxisX(axisX[i], series[i]);
    series[i]->attachAxis(axisY[i]);
    //series[i]->attachAxis(axisX[i]);


   axisX[i]->setTitleText("Temperature");
   axisY[i]->setTitleText(propy[i]);
    axisY[i]->setLabelFormat("%0.4E");
    series[i]->setPointsVisible(true);
   // axisY[i]->setTickCount(10);
    //axisX[i]->setRange();
    //axisY[i]->setRange(0,250);


    chartView[i] = new QChartView(chart[i]);
    }

            ui->gridLayout_4->addWidget(chartView[0]);
            ui->gridLayout_5->addWidget(chartView[1]);
            ui->gridLayout_6->addWidget(chartView[2]);
            ui->gridLayout_7->addWidget(chartView[3]);
            ui->gridLayout_8->addWidget(chartView[4]);
            ui->gridLayout_9->addWidget(chartView[5]);
            ui->gridLayout_10->addWidget(chartView[6]);
            ui->gridLayout_11->addWidget(chartView[7]);
            ui->gridLayout_12->addWidget(chartView[8]);
            ui->gridLayout_13->addWidget(chartView[9]);
            ui->gridLayout_14->addWidget(chartView[10]);

}
void MainWindow::conduct(int temp,int impdel)
{

    do
    {
        sta();
        read("ANA:POINTS?");
        sto();

        readfile();

    }while(vec[0]=="'");

    tot=vec[0].toInt();
    //Process.....1
    //QProgressDialog progress(this);
    //progress.setLabelText("Plotting");
    //progress.setRange(0,11);
   // progress.setModal(true);

    con();
    outs("In1.selected?");
    outs("In"+QString::number(temp)+".value?");
    clo();

    sta();
    write("ANA:TRIG");
    sto();

    if(impdel==1)
        ui->pushButton_3->setStyleSheet("background-color:green");
    else
        ui->pushButton_5->setStyleSheet("background-color:green");

    QFile file("/home/phy/ControlX/ctc.txt");


  QString s[40];
  int j=0;
    file.open(QIODevice::ReadOnly);
       //fi.open(QIODevice::Append);
       //QTextStream foo(&fi);



      while (!file.atEnd())
      {

               char a[1025];

                   file.readLine(a,sizeof(a));

                   QString temp;

                   for(uint i=0;i<qstrlen(a)-3;i++)
                    temp=temp+a[i];
                   //qDebug()<<temp;

                   if(temp=="On" || temp=="Off")
                   {
                       int k=0; s[0]=temp; j++;

                      while(k<2)
                      {
                             file.readLine(a,sizeof(a));
                              for(uint i=0;i<qstrlen(a)-3;i++)
                              s[j]=s[j]+a[i];

                            j++;

                          //  qDebug()<<s[j-1];


                          k++;
                      }

                      break;
                   }

      }

      if(temp==1)
          ui->lcdNumber->display(s[1]);
      else if(temp==2)
          ui->lcdNumber_2->display(s[1]);
      else if(temp==3)
          ui->lcdNumber_3->display(s[1]);
      else
          ui->lcdNumber_4->display(s[1]);

    if(impdel==1)
    delay(ui->spinBox_3->value());
    else
    delay(ui->spinBox_4->value());






    for(int i=0;i<11;i++)
    {
        //Progress.....
        //progress.setValue(i);
       // qApp->processEvents();

        sta();
        write("ANA:PROP1 "+props[i]);
        write("ANA:FIT 3");
        sto();

        QFile file1("/home/phy/Desktop/"+folder+"/"+props[i]+"~T"+".txt");
        file1.open(QIODevice::Append);

        QTextStream out(&file1);

        do
        {
            sta();
            read("ANA:POINT? 0");
            sto();
            readfile();

        }while(vec[0]=="'" or vec[0]=="No data");

        sta();
        //ui->label_2->setText("");
        for(int j=0;j<=tot;j++)
        {
           read("ANA:POINT? "+QString::number(j));
        }

        sto();
        //ui->label_2->setText("Plotting...");
        readfile();

        if(flag==0 and i==0)
        { flag=1; i--; continue;}
        else
        {
            flag=0;
        }

         out<<qSetFieldWidth(20)<<s[1];


        for(int j=0;j<vec.size();j++)
        {//qDebug()<<vec[j];
            QStringList my = vec[j].split(',');
            //ui->label_2->setText("");
            if(my.size()>=2)
            out<<qSetFieldWidth(20)<<my[1];
            else
            out<<qSetFieldWidth(20)<<"NA";

             qApp->processEvents();
           // ui->label_2->setText("");
            if(j!=25)
                continue;

            if(my[0]=="NA")
                continue;
            else
            {
                  QString cur=my[1];
                  double yt=cur.toDouble();
                  cur=s[1];
                  double xt=cur.toDouble();
                  qreal y=qreal(yt);
                  qreal x=qreal(xt);
                  //ui->label_2->setText("Plotting...");
            //qDebug()<<x<<" "<<y;
                  /*  if(y>0)
             {
                  if(pts==0)
                      ptr->axisY[i]->setRange(y-y/100,y+y/100);
                   else
                      if(y>=ptr->axisY[i]->max())
                      { foo<<y<<"    1"<<ptr->axisY[i]->max()<<endl; ptr->axisY[i]->setMax(y+(y-ptr->axisY[i]->max()));}
                        else
                          if(y<ptr->axisY[i]->min())
                            { foo<<y<<"    2"<<ptr->axisY[i]->min()<<endl; ptr->axisY[i]->setMin(y-(ptr->axisY[i]->min()-y));}

                    ptr->series[i]->append(x,y);
                  pts++;
                  ptr->axisX[i]->setRange(ptr->axisX[i]->min(),x+10);}

                    else
                    {
                        if(pts==0)
                            ptr->axisY[i]->setRange(y+y/100,y-y/100);
                         else
                            if(y>=ptr->axisY[i]->max())
                              { foo<<y<<"    1"<<ptr->axisY[i]->max()<<endl; ptr->axisY[i]->setMax(y+(y-ptr->axisY[i]->max()));}
                              else
                                if(y<ptr->axisY[i]->min())
                                   {foo<<y<<"    2"<<ptr->axisY[i]->min()<<endl; ptr->axisY[i]->setMin(y-(ptr->axisY[i]->min()-y));}

                          ptr->series[i]->append(x,y);
                        pts++;
                        ptr->axisX[i]->setRange(ptr->axisX[i]->min(),x+10);
                    }*/

            //char a[1025];

           /*     fi.readLine(a,sizeof(a));
                QString cur=a;
            double yt=cur.toDouble();
            fi.readLine(a,sizeof(a));
            cur=a;
            double xt=cur.toDouble();
            qreal y=qreal(yt);
            qreal x=qreal(xt);*/



            if(pts[i]==0)
            {
                if(y>0)
                {m[i]=y-y/5000; M[i]=y+y/5000;}
                else
                {m[i]=y+y/5000; M[i]=y-y/5000;}
                startx=x-2;


            }
            else
            {
                if(y<m[i])
                    m[i]=y;
                else
                if(y>M[i])
                    M[i]=y;
                //ptr->axisX[i]->setMax(x+5);


            }

            series[i]->append(x,y);
            axisY[i]->setRange(m[i]-(M[i]-m[i])/10,M[i]+(M[i]-m[i])/10); pts[i]++;
            axisX[i]->setRange(startx,x+2);
           // ui->label_2->setText("");

             //foo<<i<<" "<<pts[i]<<endl;
               // foo<<y<<" "<<m[i]<<" "<<M[i]<<endl<<endl;
            }
        }
        out<<endl;

            //Process...
        //qApp->processEvents();

    }

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showtime()
{




    con();
    outs("Out1.selected?");
    outs("Out2.selected?");
    outs("Out1.PID.Input?");
    outs("Out2.PID.Input?");
    outs("In1.value?");
    outs("In2.value?");
    outs("In3.value?");
    outs("In4.value?");
    clo();
    QFile file("/home/phy/ControlX/ctc.txt");

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
                   //qDebug()<<temp;

                   if(temp=="On" || temp=="Off")
                   {
                       int k=0; s[0]=temp; j++;

                      while(k<8)
                      {
                             file.readLine(a,sizeof(a));
                              for(uint i=0;i<qstrlen(a)-3;i++)
                              s[j]=s[j]+a[i];

                            j++;

                           // qDebug()<<s[j-1];


                          k++;
                      }

                      break;
                   }

      }
      if(s[0]=="On")        //Output1 on or off
      {//qDebug()<<s[2];
          double out1_setpoint=ui->doubleSpinBox_6->value();
          double out1_tol=ui->doubleSpinBox_25->value();
          double max=out1_setpoint+out1_tol;
          double min=out1_setpoint-out1_tol;
          double final=ui->doubleSpinBox_8->value();
          double interval=ui->doubleSpinBox_7->value();
          if(s[2]=="In 1")
          {

              ui->lcdNumber->display(s[4]);
              double comp=s[4].toDouble();

              /*if(setpoints.size()>=5)
                  setpoints.pop_back();
              setpoints.push_back(comp);*/

              if(comp>min and comp<max )
              {
                 // ui->pushButton_3->setStyleSheet("background-color:green");
               //   setpoints.clear();

                  //PAUSE CODE
                  delay(ui->spinBox->value());

                  conduct(1,1);

                  if(final==out1_setpoint )
                  {
                      timer->stop();

                       ui->pushButton_2->setStyleSheet("background-color:black");
                      con();
                      outs("OutputEnable = Off");

                      clo();

                  }
                  else
                      ui->doubleSpinBox_6->setValue(out1_setpoint+interval);

                  ui->pushButton_3->setStyleSheet("background-color:red");

                  con();
                  outs("Out1.PID.Mode = On");
                  clo();

              }

          }
          else if(s[2]=="In 2")
          {
               ui->lcdNumber_2->display(s[5]);
               double comp=s[5].toDouble();

               /*if(setpoints.size()>=5)
                   setpoints.pop_back();
               setpoints.push_back(comp);*/

               if(comp>min and comp<max )
               {
                   //ui->pushButton_3->setStyleSheet("background-color:green");
                  // setpoints.clear();
             //PAUSE CODE
                  delay(ui->spinBox->value());

                 conduct(2,1);

                   if(final==out1_setpoint )
                   {
                       timer->stop();

                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                   else
                       ui->doubleSpinBox_6->setValue(out1_setpoint+interval);

                   ui->pushButton_3->setStyleSheet("background-color:red");


                   con();
                   outs("Out1.PID.Mode = On");
                   clo();
               }

          }
          else if(s[2]=="In 3")
          {
               ui->lcdNumber_3->display(s[6]);  //qDebug()<<s[6]<<endl;
               double comp=s[6].toDouble();

               /*if(setpoints.size()>=5)
                   setpoints.pop_back();
               setpoints.push_back(comp);*/

               if(comp>min and comp<max )
               {
                  // ui->pushButton_3->setStyleSheet("background-color:green");
                   //setpoints.clear();
             //PAUSE CODE
                  delay(ui->spinBox->value());

                  conduct(3,1);

                   if(final==out1_setpoint )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                    else
                       ui->doubleSpinBox_6->setValue(out1_setpoint+interval);

                   ui->pushButton_3->setStyleSheet("background-color:red");


                   con();
                   outs("Out1.PID.Mode = On");
                   clo();
               }

          }
          else if(s[2]=="In 4")
          {
               ui->lcdNumber_4->display(s[7]);
               double comp=s[7].toDouble();

               /*if(setpoints.size()>=5)
                   setpoints.pop_back();
               setpoints.push_back(comp);*/

               if(comp>min and comp<max )
               {
                   //ui->pushButton_3->setStyleSheet("background-color:green");
                   //setpoints.clear();
             //PAUSE CODE
                   delay(ui->spinBox->value());

                   conduct(4,1);

                   if(final==out1_setpoint )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                   else
                       ui->doubleSpinBox_6->setValue(out1_setpoint+interval);
                   ui->pushButton_3->setStyleSheet("background-color:red");


                   con();
                   outs("Out1.PID.Mode = On");
                   clo();
               }

          }
      }
      if(s[1]=="On")        //Output2 on or off
      {
          double out2_setpoint=ui->doubleSpinBox_17->value();
          double out2_tol=ui->doubleSpinBox_38->value();
          double max=out2_setpoint+out2_tol;
          double min=out2_setpoint-out2_tol;
          double final=ui->doubleSpinBox_19->value();
          double interval=ui->doubleSpinBox_18->value();
          if(s[3]=="In 1")
          {
                //qDebug()<<s[4];
              ui->lcdNumber->display(s[4]);
              double comp=s[4].toDouble();

              /*if(setpoints.size()>=5)
                  setpoints.pop_back();
              setpoints.push_back(comp);*/

              if(comp>min and comp<max )
              {
                  //ui->pushButton_5->setStyleSheet("background-color:green");
                  //setpoints.clear();
            //PAUSE CODE
                  delay(ui->spinBox_2->value());

                  conduct(1,2);

                  if(final==out2_setpoint )
                  {
                      timer->stop();
                       ui->pushButton_2->setStyleSheet("background-color:black");
                      con();
                      outs("OutputEnable = Off");
                      clo();
                  }
                  else
                       ui->doubleSpinBox_17->setValue(out2_setpoint+interval);

                  ui->pushButton_5->setStyleSheet("background-color:red");


                  con();
                  outs("Out2.PID.Mode = On");
                  clo();
              }

          }
          else if(s[2]=="In 2")
          {
               ui->lcdNumber_2->display(s[5]);
               double comp=s[5].toDouble();

              /* if(setpoints.size()>=5)
                   setpoints.pop_back();
               setpoints.push_back(comp);*/

               if(comp>min and comp<max )
               {
                  // ui->pushButton_5->setStyleSheet("background-color:green");
                   //setpoints.clear();

             //PAUSE CODE
                   delay(final==out2_setpoint);

                   conduct(2,2);

                   if(comp > final-out2_tol && comp<final+out2_tol )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                    else
                       ui->doubleSpinBox_17->setValue(out2_setpoint+interval);
                   ui->pushButton_5->setStyleSheet("background-color:red");

                   con();
                   outs("Out2.PID.Mode = On");
                   clo();

               }

          }
          else if(s[2]=="In 3")
          {
               ui->lcdNumber_3->display(s[6]); //qDebug()<<s[6]<<endl;
               double comp=s[6].toDouble();

               if(setpoints.size()>=5)
                   setpoints.pop_back();
               setpoints.push_back(comp);

              if(comp>min and comp<max )
               {
                   //ui->pushButton_5->setStyleSheet("background-color:green");
                   //setpoints.clear();
             //PAUSE CODE
                   delay(ui->spinBox_2->value());

                   conduct(3,2);

                   if(final==out2_setpoint )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                   else
                       ui->doubleSpinBox_17->setValue(out2_setpoint+interval);

                   ui->pushButton_5->setStyleSheet("background-color:red");


                   con();
                   outs("Out2.PID.Mode = On");
                   clo();
               }

          }
          else if(s[2]=="In 4")
          {
               ui->lcdNumber_4->display(s[7]);
               double comp=s[7].toDouble();

               /*if(setpoints.size()>=5)
                   setpoints.pop_back();
               setpoints.push_back(comp);*/

               if(comp>min and comp<max )
               {
                   //ui->pushButton_5->setStyleSheet("background-color:green");
                   //setpoints.clear();
             //PAUSE CODE
                   delay(ui->spinBox_2->value());

                   conduct(4,2);

                   if(final==out2_setpoint )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                   else
                        ui->doubleSpinBox_17->setValue(out2_setpoint+interval);

                   ui->pushButton_5->setStyleSheet("background-color:red");


                   con();
                   outs("Out2.PID.Mode = On");
                   clo();
               }

          }
      }

}

void MainWindow::on_pushButton_2_clicked()
{


    if(z==0)
    {
        QString temp;

        while(1){

            folder=QInputDialog::getText(this,"Folder","Enter Folder name");
            if(folder=="")
                return;
            QFile file("/home/phy/ControlX/fault.sh");
            file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out<<"#!/bin/sh\n";
            out<<"mkdir "+folder<<"\n";
            file.close();
            system("script -c /home/phy/ControlX/./fault.sh /home/phy/ControlX/bat.txt");
            QFile file1("/home/phy/ControlX/bat.txt");
            file1.open(QIODevice::ReadOnly);
            int i=0;
            while(!file1.atEnd())
            {
                char a[1024];

                file1.readLine(a,sizeof(a));
                i++;


             //QFile file("/home/phy/ControlX/bat.txt");

             //file.open(QIODevice::ReadOnly);

             /*if(!file.size()<=2)
                 break;
             else*/

        }

            if(i==4)
            {
               QMessageBox::StandardButton reply;
              reply=QMessageBox::question(this,"CONFIRM","Folder already exists. Do you wish to overwrite?",QMessageBox::Yes|QMessageBox::No);\

              if(reply==QMessageBox::Yes)
                 break;

            }
            else
                break;



}
        do
        {
            sta();
            read("ANA:POINTS?");
            sto();

            readfile();

        }while(vec[0]=="'" or vec[0]=="No data");

        tot=vec[0].toInt();

        sta();

        for(int j=0;j<=tot;j++)
        {
           read("ANA:POINT? "+QString::number(j));
        }

        sto();

        readfile();



        for(int i=0;i<11;i++)
        {
            QFile file1("/home/phy/Desktop/"+folder+"/"+props[i]+"~T"+".txt");
            file1.open(QIODevice::WriteOnly);

            QTextStream out(&file1);

            out<<qSetFieldWidth(20)<<"T(K)\\F(Hz)";

            for(int j=0;j<vec.size();j++)
            {   //qDebug()<<vec[j];
                QStringList my = vec[j].split(',');
                if(my.size()>0)
                out<<qSetFieldWidth(20)<<my[0];
                else
                out<<qSetFieldWidth(20)<<"NA";
            }

            out<<endl<<endl;


        }
    //6 8 17 19



        ui->pushButton_2->setStyleSheet("background-color:red");

            con();


           outs("outputEnable = on");


           clo();

        QMessageBox::information(this,"OUTPUT","Ouput Enabled");

        ui->pushButton_3->setStyleSheet("background-color:red");
        ui->pushButton_5->setStyleSheet("background-color:red");

        timer->start(1000);


    }
    else
    {
            ui->pushButton_2->setStyleSheet("background-color:black");

            con();

           outs("outputEnable = off");

            clo();

             ui->pushButton_2->setStyleSheet("background-color:black");

            timer->stop();



            QMessageBox::information(this,"OUTPUT","Ouput Disabled");
    }

    z=!z;


}

void MainWindow::on_connect_clicked()
{
    /*QLabel *lbl = new QLabel;
    QMovie *movie = new QMovie(":/gears.gif");
    lbl->setMovie(movie);
    lbl->setScaledContents(true);
    //lbl->show();
    movie->start();*/

    /*con();
    outs("Connected!!!");
    clo();
*/

    /*QMessageBox::StandardButton reply;

     reply = QMessageBox::information(this, "Status", "CONNECTED!!!",QMessageBox::Ok);

     if (reply == QMessageBox::Ok)
     {
         con();
         outs("popup.close");
         clo();
     }*/



   con(true);
   //Output1

       outs("Out1.selected?");
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
       outs("Out2.selected?");
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
   //OutputEnable
       outs("OutputEnable?");
   //Output Pid mode
       outs("Out1.PID.Mode?");
       outs("Out2.PID.Mode?");
   //Value of Inputs
       outs("In1.value?");
       outs("In2.value?");
       outs("In3.value?");
       outs("In4.value?");

       clo(true);

       QFile file("/home/phy/ControlX/ctc.txt");


     QString s[100];
     int j=0;
       file.open(QIODevice::ReadOnly);


         while (!file.atEnd())
         {

                  char a[1025];

                      file.readLine(a,sizeof(a));

                      QString temp;

                      for(uint i=0;i<qstrlen(a)-3;i++)
                       temp=temp+a[i];
                      //qDebug()<<temp;

                      if(temp=="On" or temp=="Off")
                      {
                          int k=0; s[0]=temp; j++;

                         while(k<39)
                         {
                                file.readLine(a,sizeof(a));





                                 for(uint i=0;i<qstrlen(a)-3;i++)
                                 s[j]=s[j]+a[i];

                               j++;

                              //qDebug()<<s[j-1];


                             k++;
                         }

                         break;
                      }

         }
   //Output1

         if(s[0]=="On")
         {
             mode1=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out1mode->setIcon(ButtonIcon);
             ui->out1mode->setIconSize(QSize(61,31));
             //on_out1mode_clicked();
         }
         else
         {
              mode1=0;

              //on_out1mode_clicked();
         }

         if(s[33]=="On")
         {
             mode3=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_5->setIcon(ButtonIcon);
             ui->out2mode_5->setIconSize(QSize(61,31));
             //on_out2mode_5_clicked();
         }
         else
         {
              mode3=0;

              //on_out2mode_5_clicked();
         }
         ui->comboBox->setCurrentText(s[1]);

         ui->doubleSpinBox->setValue(s[2].toDouble());

         ui->doubleSpinBox_2->setValue(s[3].toDouble());

         if(s[4]=="unselected")
             s[4]="Select";

         ui->comboBox_2->setCurrentText(s[4]);

         ui->doubleSpinBox_6->setValue(s[5].toDouble());

         ui->doubleSpinBox_9->setValue(s[6].toDouble());

         ui->doubleSpinBox_11->setValue(s[7].toDouble());

         ui->doubleSpinBox_12->setValue(s[8].toDouble());

         ui->doubleSpinBox_13->setValue(s[9].toDouble());

         qApp->processEvents();
         //qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
   //Output2

         if(s[10]=="On")
         {
             mode2=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode->setIcon(ButtonIcon);
             ui->out2mode->setIconSize(QSize(61,31));
             //on_out2mode_clicked();
         }
         else
         {
             mode2=0;

             //on_out2mode_clicked();
         }
         if(s[34]=="On")
         {
             mode4=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_4->setIcon(ButtonIcon);
             ui->out2mode_4->setIconSize(QSize(61,31));
             //on_out2mode_4_clicked();
         }
         else
         {
              mode4=0;

              //on_out2mode_4_clicked();
         }
         ui->comboBox_5->setCurrentText(s[11]);

         ui->doubleSpinBox_14->setValue(s[12].toDouble());

         ui->doubleSpinBox_15->setValue(s[13].toDouble());

         if(s[14]=="unselected")
             s[14]="Select";

         ui->comboBox_6->setCurrentText(s[14]);

         ui->doubleSpinBox_17->setValue(s[15].toDouble());

         ui->doubleSpinBox_20->setValue(s[16].toDouble());

         ui->doubleSpinBox_22->setValue(s[17].toDouble());

         ui->doubleSpinBox_23->setValue(s[18].toDouble());

         ui->doubleSpinBox_24->setValue(s[19].toDouble());

         qApp->processEvents();
        // qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
   //Input1
         if(s[20]=="On")
         {
             inmode1=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_2->setIcon(ButtonIcon);
             ui->out2mode_2->setIconSize(QSize(61,31));
             //on_out2mode_2_clicked();
         }
         else
         {
             inmode1=0;
             //on_out2mode_2_clicked();
         }
         ui->comboBox_7->setCurrentText(s[21]);

         if(s[22]!="Auto" and s[22]!="2.5V")
         {
             int x=s[22].size();

             QString temp;

             for(int i=x-3;i>=0;i--)
                 temp=s[22][i]+temp;

             temp+="ê";

             s[22]=temp;
         }

         ui->comboBox_8->setCurrentText(s[22]);
        // qDebug()<<s[22];

         qApp->processEvents();
        // qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
   //Input2
         if(s[23]=="On")
         {
             inmode2=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_6->setIcon(ButtonIcon);
             ui->out2mode_6->setIconSize(QSize(61,31));
            // on_out2mode_6_clicked();
         }
         else
         {
             inmode2=0;
            // on_out2mode_6_clicked();
         }
         ui->comboBox_15->setCurrentText(s[24]);

         if(s[25]!="Auto" and s[25]!="2.5V")
         {
             int x=s[25].size();

             QString temp;

             for(int i=x-3;i>=0;i--)
                 temp=s[16][i]+temp;

             temp+="ê";

             s[25]=temp;
         }

         ui->comboBox_16->setCurrentText(s[25]);


         qApp->processEvents();
        // qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
   //Input3
         if(s[26]=="On")
         {
             inmode3=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_10->setIcon(ButtonIcon);
             ui->out2mode_10->setIconSize(QSize(61,31));
             //on_out2mode_10_clicked();
         }
         else
         {
             inmode3=0;
             //on_out2mode_10_clicked();
         }
         ui->comboBox_23->setCurrentText(s[27]);

         if(s[28]!="Auto" and s[28]!="2.5V")
         {
             int x=s[28].size();

             QString temp;

             for(int i=x-3;i>=0;i--)
                 temp=s[28][i]+temp;

             temp+="ê";

             s[28]=temp;
         }

         ui->comboBox_24->setCurrentText(s[28]);

         qApp->processEvents();
        // qApp->processEvents(QEventLoop::ExcludeUserInputEvents);
   //Input4
         if(s[29]=="On")
         {
             inmode4=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_9->setIcon(ButtonIcon);
             ui->out2mode_9->setIconSize(QSize(61,31));
             //on_out2mode_9_clicked();
         }
         else
         {
             inmode4=0;
             //on_out2mode_9_clicked();
         }
         ui->comboBox_21->setCurrentText(s[30]);

         if(s[31]!="Auto" and s[31]!="2.5V")
         {
             int x=s[31].size();

             QString temp;

             for(int i=x-3;i>=0;i--)
                 temp=s[31][i]+temp;

             temp+="ê";

             s[31]=temp;
         }

         ui->comboBox_22->setCurrentText(s[31]);

         ui->lcdNumber->display(s[35]);
         ui->lcdNumber_2->display(s[36]);
         ui->lcdNumber_3->display(s[37]);
         ui->lcdNumber_4->display(s[38]);

        //movie->stop();
        //lbl->close();
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
       outs("Out1.selected = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out1mode->setIcon(ButtonIcon);
        ui->out1mode->setIconSize(QSize(61,31));

        con();
        outs("Out1.selected = on");
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
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode->setIcon(ButtonIcon);
        ui->out2mode->setIconSize(QSize(61,31));

       con();
       outs("Out2.selected = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode->setIcon(ButtonIcon);
        ui->out2mode->setIconSize(QSize(61,31));

        con();
        outs("Out2.selected = on");
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
    if(inmode1==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_2->setIcon(ButtonIcon);
        ui->out2mode_2->setIconSize(QSize(61,31));

       con();
       outs("In1.selected = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_2->setIcon(ButtonIcon);
        ui->out2mode_2->setIconSize(QSize(61,31));

        con();
        outs("In1.selected = on");
        clo();
    }

    inmode1=!inmode1;
}

void MainWindow::on_out2mode_6_clicked()
{
    if(inmode2==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_6->setIcon(ButtonIcon);
        ui->out2mode_6->setIconSize(QSize(61,31));

       con();
       outs("In2.selected = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_6->setIcon(ButtonIcon);
        ui->out2mode_6->setIconSize(QSize(61,31));

        con();
        outs("In2.selected = on");
        clo();
    }

    inmode2=!inmode2;
}

void MainWindow::on_out2mode_10_clicked()
{
    if(inmode3==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_10->setIcon(ButtonIcon);
        ui->out2mode_10->setIconSize(QSize(61,31));

       con();
       outs("In3.selected = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_10->setIcon(ButtonIcon);
        ui->out2mode_10->setIconSize(QSize(61,31));

        con();
        outs("In3.selected = on");
        clo();
    }

    inmode3=!inmode3;
}

void MainWindow::on_out2mode_9_clicked()
{
    if(inmode4==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_9->setIcon(ButtonIcon);
        ui->out2mode_9->setIconSize(QSize(61,31));

       con();
       outs("In4.selected = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_9->setIcon(ButtonIcon);
        ui->out2mode_9->setIconSize(QSize(61,31));

        con();
        outs("In4.selected = on");
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

    QString temp="Auto";

    outs("In1.Range = "+temp);

    if(arg1!="Auto")
    {
        int i;

        for( i=0;i<11;i++)
        if(v[i]==arg1)
            break;
        i++;

        char c='0'+i;

        QString h;h+=c;

    outs("In1.Range += "+h);
    //qDebug()<<c;
    }
    clo();
}

void MainWindow::on_comboBox_24_activated(const QString &arg1)
{
    con();

    QString temp="Auto";

    outs("In2.Range = "+temp);

    if(arg1!="Auto")
    {
        int i;

        for( i=0;i<11;i++)
        if(v[i]==arg1)
            break;

        i++;

        char c='0'+i;

        QString h;h+=c;

    outs("In2.Range += "+h);
    }

    clo();
}

void MainWindow::on_comboBox_16_activated(const QString &arg1)
{
    con();

    QString temp="Auto";

    outs("In3.Range = "+temp);

    if(arg1!="Auto")
    {
        int i;

        for( i=0;i<11;i++)
        if(v[i]==arg1)
            break;

        i++;

        char c='0'+i;

        QString h;h+=c;

    outs("In3.Range += "+h);
    }

    clo();
}

void MainWindow::on_comboBox_22_activated(const QString &arg1)
{
    con();
QString temp="Auto";

    outs("In4.Range = "+temp);

    if(arg1!="Auto")
    {
        int i;

        for( i=0;i<11;i++)
        if(v[i]==arg1)
            break;
        i++;

        char c='0'+i;

        QString h;h+=c;

    outs("In4.Range += "+h);
    }

    clo();
}

void MainWindow::on_out2mode_5_clicked()
{
    if(mode3==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_5->setIcon(ButtonIcon);
        ui->out2mode_5->setIconSize(QSize(61,31));

       con();
       outs("Out1.PID.Mode = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_5->setIcon(ButtonIcon);
        ui->out2mode_5->setIconSize(QSize(61,31));

        con();
        outs("Out1.PID.Mode = on");
        clo();
    }

    mode3=!mode3;
}

void MainWindow::on_out2mode_4_clicked()
{
    if(mode4==1)
        {
            QPixmap pixmap(":/on-off.jpg");
            QIcon ButtonIcon(pixmap);
            ui->out2mode_4->setIcon(ButtonIcon);
            ui->out2mode_4->setIconSize(QSize(61,31));

           con();
           outs("Out1.PID.Mode = off");
           clo();
        }
        else
        {
            QPixmap pixmap(":/on.jpg");
            QIcon ButtonIcon(pixmap);
            ui->out2mode_4->setIcon(ButtonIcon);
            ui->out2mode_4->setIconSize(QSize(61,31));

            con();
            outs("Out1.PID.Mode = on");
            clo();
        }

        mode4=!mode4;
}

/*void MainWindow::on_pushButton_6_clicked()
{
    //ptr = new wk(this);
    ptr->show();

}*/

void MainWindow::on_meas_setup_clicked()
{
   meas->show();
}

void MainWindow::on_trace_setup_clicked()
{
    trace->show();
}

/*void MainWindow::on_doubleSpinBox_6_editingFinished()
{
    con();
    double temp=ui->doubleSpinBox_6->value();
    QString s=QString:
    outs("Out1.PID.setpoint "+arg1);

    clo();
}*/
