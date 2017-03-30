#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QTime>
#include "Scriptwrite.h"
#include <QPair>
#include <QtCharts>

//#define props prop
#define start_connection start_connection_VI
#define read_string read_string_VI
#define stop_connection stop_connection_VI
#define write_command write_command_VI
using namespace QtCharts;
#define vec vect
int point;
qreal min_value,max_value;
QString folder_name;
double cur,volt,power;
QVector< QString > vect;
QList<double> curtemp;
int datapoints;

bool MainWindow::checkset(int out)
{
    if((out==1 and curtemp.size()==datapoints) or (out==2 and curtemp.size()==datapoints) )
    {
        auto mm = std::minmax_element(curtemp.begin(), curtemp.end());
        curtemp.pop_front();
        QFile fit("bugy.txt");
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
            if(*mm.second-*mm.first<ui->accuracy2->value())
                return true;
            else
                return false;
        }
    }
    else
        return false;
}

void readfiles()
{
    QFile file("/home/phy/ControlVI/wk.txt");

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

                    vec.push_back(temp);
            }
    }
}

double calc(int points)
{
    double Avg_Volt,cur,sum=0;

    QList<double> voltages;

    for(int i=0;i<points;i++)
    {
        QString command="SENS:DATA:FRES?";
        start_connection(2);
        read_string(command);
        stop_connection();
        readfiles();
        cur=vec[0].toDouble();
        sum+=cur;
        voltages.push_back(cur);
    }


    Avg_Volt=sum/points;

    auto mm = std::minmax_element(voltages.begin(), voltages.end());

    while(((*mm.second)-(*mm.first))>std::abs(Avg_Volt/10))
    {
        QString command="SENS:DATA:FRES?";
        start_connection(2);
        read_string(command);
        stop_connection();
        readfiles();
        cur=vec[0].toDouble();
        sum=sum+cur-voltages.front();
        voltages.pop_front();
        voltages.push_back(cur);
        Avg_Volt=sum/points;



        mm = std::minmax_element(voltages.begin(), voltages.end());
    }

    return Avg_Volt;

}

void delay( int millisecondsToWait )
{

    millisecondsToWait*=1000;
    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}


//QVector <QPointF > points;

int noof_points;
int firstx;
char sensor_type1='R',sensor_type2='R',sensor_type3='R',sensor_type4='R';
bool output_status,output_mode1,output_mode2=0,output_mode3,output_mode4,input_mode1,input_mode2,input_mode3,input_mode4;// PUCHO ROHITH SE
QString sensor_range[11]={ "10ê", "30ê", "100ê", "300ê", "1kê", "3kê", "10kê", "30kê", "100kê","300kê","Auto" };
//QString prop[12]={"L","C","Q","D","R","X","Z","Y","Angle","B","G","L"};

QFile file("/home/phy/ControlVI/script.sh");

QTextStream out(&file);
//QList <double> curtemp;

void con()
{
    //conecting code starts

   file.open(QIODevice::WriteOnly| QIODevice::Text);

   out<<"#!/usr/bin/expect\n";
   out<<"spawn telnet 100.10.19.37\n";
   /*if(sig==true)
       out<<"sleep 0.55\n";
   else
   out<<"sleep 0.2\n";*/
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

    //if(sig==true)
      //  out<<"sleep 0.55\n";
    //else
    //out<<"sleep 0.2\n";
   /* out<<"send ";
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
    out<<"\n";*/
    out<<"send ";
    out<<"\"system.other.reset Ports";
    out<<"\\n";
    out<<"\"";
    out<<"\n";

   // out<<"system.other.reset Ports\n";
     out<<"interact\n";
    //connection terminating code ends//
    file.close();
   system("script -c /home/phy/ControlVI/./script.sh /home/phy/ControlVI/ctc.txt");
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

    start_connection();
    write_command("SOUR:CURR:RANG:AUTO 1");
    stop_connection();


    for(int i=0;i<11;i++)
    {
           ui->comboBox_8->addItem(sensor_range[i]);
           ui->comboBox_16->addItem(sensor_range[i]);
           ui->comboBox_24->addItem(sensor_range[i]);
           ui->comboBox_22->addItem(sensor_range[i]);
    }

    timer=new QTimer();
    connect(timer, SIGNAL(timeout()),this,SLOT(showtime()));

    series = new QLineSeries();
    chart = new QChart();
    axisX = new QValueAxis();
    axisY = new QValueAxis();
    series->setName("R~T");
    series->setPointsVisible(true);
    chart->addSeries(series);
    chart->addAxis(axisY, Qt::AlignLeft);
    chart->setAxisX(axisX, series);
    series->attachAxis(axisY);
   axisX->setTitleText("Temperature (K)");
   axisY->setTitleText("Resistance (Ω)");
    axisY->setLabelFormat("%0.4E");
    series->setPointsVisible(true);

    chartView = new QChartView(chart);

    ui->gridLayout->addWidget(chartView);

}
void MainWindow::conduct(int temp,int impdel)
{


    //qdebug()<<noof_points;
    con();
    outs("In1.selected?"); //
    outs("In"+QString::number(temp)+".value?");
    clo();

    /*if(impdel==1)
        ui->pushButton_3->setStyleSheet("background-color:green");
    else
        ui->pushButton_5->setStyleSheet("background-color:green");*/

    QFile file("/home/phy/ControlVI/ctc.txt");


  QString s[40];
  int j=0;
    file.open(QIODevice::ReadOnly);
      while (!file.atEnd())
      {

               char a[1025];

                   file.readLine(a,sizeof(a));

                   QString temp;

                   for(int i=0;i<int(qstrlen(a))-2;i++)
                    temp=temp+a[i];

                   if(temp=="On" || temp=="Off")
                   {
                       int k=0; s[0]=temp; j++;

                      while(k<2)
                      {
                             file.readLine(a,sizeof(a));
                              for(int i=0;i<int(qstrlen(a))-2;i++)
                              s[j]=s[j]+a[i];

                            j++;


                            qDebug()<<s[j]<<endl;

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


      double Avg_Rst,Avg_Volt;double current;

      if(ke2->mode==0)
      {

       noof_points=ke2->total_points; double vfin=0;
//write code for 5 points
        start_connection();
        read_string("SOUR:CURR?");
        stop_connection();
        readfiles();
        current=vec[0].toDouble();

        Avg_Volt=calc(noof_points);
        vfin+=Avg_Volt;
        Avg_Rst=Avg_Volt/current;

        current*=-1; Avg_Volt=0;

        start_connection();
        write_command("SOUR:CURR "+QString::number(current));
        stop_connection();

        Avg_Volt=calc(noof_points);

        vfin-=Avg_Volt;
        vfin/=2;
        Avg_Rst+=Avg_Volt/current;
        Avg_Rst/=2;

        current*=-1;
        start_connection();
        write_command("SOUR:CURR "+QString::number(current));
        stop_connection();

        QFile file1("/home/phy/Desktop/ControlVI_Data/"+folder_name+"/R~T.txt");
        file1.open(QIODevice::Append);

        QTextStream out(&file1);

   out<<qSetFieldWidth(20)<<s[1]<<qSetFieldWidth(20)<<vfin<<qSetFieldWidth(20)<<current<<qSetFieldWidth(20)<<Avg_Rst<<endl;    // (done)write code for file write of resistance
       }
      else if(ke2->mode==1)
          {

          QFile file1("/home/phy/Desktop/ControlVI_Data/"+folder_name+"/R~T.txt");
          file1.open(QIODevice::Append);

          QTextStream out(&file1);

            double interval=((ke2->hi_lmt-ke2->lo_lmt)/(ke2->sample_points-1));

            for(int i=0;i<ke2->sample_points;i++)
            {
                Avg_Volt=0;
                current=ke2->lo_lmt+i*interval; double vfin=0;

                start_connection();
                write_command("SOUR:CURR "+QString::number(current));
                stop_connection();

                delay(1000);


                double Avg_Rstin=0;

                qApp->processEvents();

                Avg_Volt=calc(ke2->total_points2);

                vfin+=Avg_Volt;
                Avg_Rstin=Avg_Volt/current;
                Avg_Rst+=Avg_Rstin;

                current*=-1;

                start_connection();
                write_command("SOUR:CURR "+QString::number(current));
                stop_connection();


                 Avg_Rstin=0;
                 Avg_Volt=0;

                qApp->processEvents();

                Avg_Volt=calc(ke2->total_points2);

                vfin-=Avg_Volt;
                vfin/=2;
                Avg_Rstin=Avg_Volt/current;
                Avg_Rst+=Avg_Rstin;


                current*=-1;

 out<<qSetFieldWidth(20)<<s[1]<<qSetFieldWidth(20)<<vfin<<qSetFieldWidth(20)<<current<<qSetFieldWidth(20)<<Avg_Rstin<<endl;


            }Avg_Rst/=2*ke2->sample_points;

          }
      else
      {
           cur=power/volt; double fin=0;

           start_connection();
           write_command("SOUR:CURR "+QString::number(cur));
           stop_connection();

           Avg_Volt=calc(ke2->total_points3);

           fin+=Avg_Volt;
           Avg_Rst=Avg_Volt/cur;

           cur*=-1;

           start_connection();
           write_command("SOUR:CURR "+QString::number(cur));
           stop_connection();

           Avg_Volt=calc(ke2->total_points3);

           Avg_Rst+=Avg_Volt/cur;
           Avg_Rst/=2;
           fin-=Avg_Volt;
           fin/=2;

           QFile file1("/home/phy/Desktop/ControlVI_Data/"+folder_name+"/R~T.txt");
           file1.open(QIODevice::Append);

           QTextStream out(&file1);



      out<<qSetFieldWidth(20)<<s[1]<<qSetFieldWidth(20)<<fin<<qSetFieldWidth(20)<<-cur<<qSetFieldWidth(20)<<Avg_Rst<<endl;

      volt=fin;

      }





                      double yt=Avg_Rst;
                      double xt=s[1].toDouble();
                      qreal y=qreal(yt);
                      qreal x=qreal(xt);

            if(point==0)
            {
                if(y>0)
                {min_value=y-y/5000; max_value=y+y/5000;}
                else
                {min_value=y+y/5000; max_value=y-y/5000;}
                firstx=x-2;


            }
            else
            {
                if(y<min_value)
                    min_value=y;
                else
                if(y>max_value)
                    max_value=y;


            }

            series->append(x,y);
            axisY->setRange(min_value-(max_value-min_value)/10,max_value+(max_value-min_value)/10); point++;
            axisX->setRange(firstx,x+2);




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
    QFile file("/home/phy/ControlVI/ctc.txt");
    QString s[40];
    int j=0;
    file.open(QIODevice::ReadOnly);

      while(!file.atEnd())
      {

               char a[1025];

                   file.readLine(a,sizeof(a));

                   QString temp;

                   for(int i=0;i<int(qstrlen(a))-2;i++)
                    temp=temp+a[i];
                   //qDebug()<<temp;

                   if(temp=="On" || temp=="Off")
                   {
                       int k=0; s[0]=temp; j++;

                      while(k<8)
                      {
                             file.readLine(a,sizeof(a));
                              for(int i=0;i<int(qstrlen(a))-2;i++)
                              s[j]=s[j]+a[i];

                            j++;

                           // qDebug()<<s[j-1];


                          k++;
                      }

                      break;
                   }

      }



      if(s[0]=="On")        //Output1 on or off
      {
          powtab->setpoint=ui->doubleSpinBox_6->value();
          double out1_tol=ui->doubleSpinBox_25->value();
          double max=powtab->setpoint+out1_tol;
          double min=powtab->setpoint-out1_tol;
          double final=ui->doubleSpinBox_8->value();
          double interval=ui->doubleSpinBox_7->value();
          if(s[2]=="In 1")
          {

              ui->lcdNumber->display(s[4]);
              double comp=s[4].toDouble();


              if(comp>min and comp<max )
              {
                  //PAUSE CODE by bikash**


                  ui->pushButton_3->setStyleSheet("background-color:green");

                  delay(ui->spinBox->value());

                  conduct(1,1);

                  if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0) )
                  {
                      timer->stop();
                      ui->pushButton_2->setStyleSheet("background-color:black");
                      con();
                      outs("OutputEnable = Off");
                      clo();
                      output_status=!output_status;
                  }
                  else
                  {
                      ui->doubleSpinBox_6->setValue(powtab->setpoint+interval);
                  }

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


               if(comp>min and comp<max )
               {

             //PAUSE CODE
                   ui->pushButton_3->setStyleSheet("background-color:green");
                  delay(ui->spinBox->value());

                 conduct(2,1);

                   if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0)  )
                   {
                       timer->stop();

                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                        output_status=!output_status;
                   }
                   else
                       ui->doubleSpinBox_6->setValue(powtab->setpoint+interval);

                   ui->pushButton_3->setStyleSheet("background-color:red");


                   con();
                   outs("Out1.PID.Mode = On");
                   clo();
               }

          }
          else if(s[2]=="In 3")
          {
               ui->lcdNumber_3->display(s[6]);
               double comp=s[6].toDouble();


               if(comp>min and comp<max )
               {

                   ui->pushButton_3->setStyleSheet("background-color:green");
                  delay(ui->spinBox->value());

                  conduct(3,1);

                   if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0)  )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                    else
                       ui->doubleSpinBox_6->setValue(powtab->setpoint+interval);

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


               if(comp>min and comp<max )
               {

             //PAUSE CODE
                   ui->pushButton_3->setStyleSheet("background-color:green");
                   delay(ui->spinBox->value());

                   conduct(4,1);

                   if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0) )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                        output_status=!output_status;
                   }
                   else
                       ui->doubleSpinBox_6->setValue(powtab->setpoint+interval);
                   ui->pushButton_3->setStyleSheet("background-color:red");


                   con();
                   outs("Out1.PID.Mode = On");
                   clo();
               }

          }
      }
      if(s[1]=="On")        //Output2 on or off
      {
           powtab->setpoint=ui->doubleSpinBox_17->value();
          double out2_tol=ui->doubleSpinBox_38->value();
          double max=powtab->setpoint+out2_tol;
          double min=powtab->setpoint-out2_tol;
          double final=ui->doubleSpinBox_19->value();
          double interval=ui->doubleSpinBox_18->value();
          if(s[3]=="In 1")
          {

              ui->lcdNumber->display(s[4]);
              double comp=s[4].toDouble();


                curtemp.push_back(comp);
              if(checkset(2) and comp>min and comp<max )
              {

            //PAUSE CODE
             // check(1,2);
                  ui->pushButton_5->setStyleSheet("background-color:green");
                  //delay(ui->spinBox_2->value());

                  conduct(1,2);


                  if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0)  )
                  {
                      timer->stop();
                       ui->pushButton_2->setStyleSheet("background-color:black");
                      con();
                      outs("OutputEnable = Off");
                      clo();
                       output_status=!output_status;
                  }
                  else
                      datapoints=ui->spinBox_2->value(),ui->doubleSpinBox_17->setValue(powtab->setpoint+interval),curtemp.clear();

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
               if(comp>min and comp<max )
               {
             //PAUSE CODE
                   ui->pushButton_5->setStyleSheet("background-color:green");
                   delay(ui->spinBox_2->value());

                   conduct(2,2);

                   if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0))
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                   }
                    else
                       ui->doubleSpinBox_17->setValue(powtab->setpoint+interval);
                   ui->pushButton_5->setStyleSheet("background-color:red");

                   con();
                   outs("Out2.PID.Mode = On");
                   clo();

               }

          }
          else if(s[2]=="In 3")
          {
               ui->lcdNumber_3->display(s[6]);
               double comp=s[6].toDouble();


              if(comp>min and comp<max )
               {
             //PAUSE CODE
                  ui->pushButton_5->setStyleSheet("background-color:green");
                   delay(ui->spinBox_2->value());

                   conduct(3,2);

                   if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0) )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                        output_status=!output_status;
                   }
                   else
                       ui->doubleSpinBox_17->setValue(powtab->setpoint+interval);

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


               if(comp>min and comp<max )
               {
             //PAUSE CODE
                   ui->pushButton_5->setStyleSheet("background-color:green");
                   delay(ui->spinBox_2->value());

                   conduct(4,2);

                   if((final<powtab->setpoint+interval&&interval>0)||(final>powtab->setpoint+interval&&interval<0) )
                   {
                       timer->stop();
                        ui->pushButton_2->setStyleSheet("background-color:black");
                       con();
                       outs("OutputEnable = Off");
                       clo();
                        output_status=!output_status;
                   }
                   else
                        ui->doubleSpinBox_17->setValue(powtab->setpoint+interval);

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


    if(output_status==0)
    {
        QString temp;

        while(1)
        {
            bool ok=false;
            folder_name=QInputDialog::getText(this,"Folder","Enter folder name to save files",QLineEdit::Normal,"PHY ",&ok);
            if(ok==false)
                return;
            QFile file("/home/phy/ControlVI/fault.sh");
            file.open(QIODevice::WriteOnly);
            QTextStream out(&file);
            out<<"#!/bin/sh\n";
            out<<"mkdir "+folder_name<<"\n";
            file.close();
            system("script -c /home/phy/ControlVI/./fault.sh /home/phy/ControlVI/bat.txt");
            QFile file1("/home/phy/ControlVI/bat.txt");
            file1.open(QIODevice::ReadOnly);
            int i=0;
            while(!file1.atEnd())
            {
                char a[1024];

                file1.readLine(a,sizeof(a));
                i++;
        }
            if(i==4)
            {
              QMessageBox::StandardButton reply;
              reply=QMessageBox::question(this,"CONFIRM","Folder already exists. Do you wish to overwrite?",QMessageBox::Yes|QMessageBox::No);\
              if(reply==QMessageBox::Yes)
                 break;

            }
           else
            if(i==5)
            {
                QMessageBox::StandardButton reply;
                reply=QMessageBox::warning(this,"WARNING!!!","Folder name can not be empty",QMessageBox::Ok);
                if(reply==QMessageBox::Ok)
                    return;

            }
            else
            {
              break;
            }
        }

     //Write code??


            QFile file1("/home/phy/Desktop/ControlVI_Data/"+folder_name+"/"+"R~T"+".txt");
            file1.open(QIODevice::WriteOnly);

            QTextStream out(&file1);

out<<qSetFieldWidth(20)<<"Temperature(K)"<<qSetFieldWidth(20)<<"Voltage(V)"<<qSetFieldWidth(20)<<"Current(A)"<<qSetFieldWidth(20)<<"Resistance(Ω)"<<endl;
            ui->pushButton_2->setStyleSheet("background-color:red");
            con();
            outs("outputEnable = on");
            clo();
        QMessageBox::information(this,"OUTPUT","Ouput Enabled");

        ui->pushButton_3->setStyleSheet("background-color:red");
        ui->pushButton_5->setStyleSheet("background-color:red");


        start_connection();
        write_command("SOUR:CURR:RANG:AUTO 1");
        stop_connection();

        QString command="SENS:DATA:FRES?";
        start_connection(2);
        read_string(command);
        stop_connection();
        readfiles();
        volt=vec[0].toDouble();

        start_connection();
        read_string("SOUR:CURR?");
        stop_connection();
        readfiles();
        cur=vec[0].toDouble();
        power=cur*volt;


        start_connection();
        write_command("OUTP 1");
        stop_connection();
        point=0;
        series->clear();
        datapoints=ui->spinBox_2->value();

        if(powtab->setpoint < 150)
        {
            con();

            outs("Out2.HiLmt "+QString::number(powtab->pow150));
            outs("Out1.HiLmt "+arg1);

            clo();
        }

        timer->start(100);
    }
    else
    {
            ui->pushButton_2->setStyleSheet("background-color:black");
            con();
            outs("outputEnable = off");
            clo();
            timer->stop();
            QMessageBox::information(this,"OUTPUT","Ouput Disabled");
    }
    output_status=!output_status;
}

void MainWindow::on_connect_clicked()
{



   con();
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

       clo();

       QFile file("/home/phy/ControlVI/ctc.txt");
//qDebug()<<"^^^^^^^^^";

     QString s[100];
     int j=0;
       file.open(QIODevice::ReadOnly);


         while (!file.atEnd())
         {//qDebug()<<"%%%%%%%%%%%%%%%%%%%";

                  char a[1025];

                      file.readLine(a,sizeof(a));

                      //qDebug()<<a<<strlen(a);

                      QString temp;



                      for(int i=0;i<int(strlen(a))-2;i++)
                       temp=temp+a[i];


                      if(temp=="On" or temp=="Off")
                      {

                          int k=0; s[0]=temp; j++;

                         while(k<39)
                         {
                                file.readLine(a,sizeof(a));





                                 for(int i=0;i<int(qstrlen(a))-2;i++)
                                 s[j]=s[j]+a[i];

                               j++;

                              qDebug()<<s[j-1];


                             k++;
                         }

                         break;
                      }

                      qDebug()<<temp;

         }
   //Output1


         if(s[0]=="On")
         {
             output_mode1=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out1mode->setIcon(ButtonIcon);
             ui->out1mode->setIconSize(QSize(61,31));
             //on_out1mode_clicked();
         }
         else
         {
              output_mode1=0;

              //on_out1mode_clicked();
         }

         if(s[33]=="On")
         {
             output_mode3=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_5->setIcon(ButtonIcon);
             ui->out2mode_5->setIconSize(QSize(51,21));
             //on_out2mode_5_clicked();
         }
         else
         {
              output_mode3=0;

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
             output_mode2=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode->setIcon(ButtonIcon);
             ui->out2mode->setIconSize(QSize(61,31));
             //on_out2mode_clicked();
         }
         else
         {
             output_mode2=0;

             //on_out2mode_clicked();
         }
         if(s[34]=="On")
         {
             output_mode4=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_4->setIcon(ButtonIcon);
             ui->out2mode_4->setIconSize(QSize(51,21));
             //on_out2mode_4_clicked();
         }
         else
         {
              output_mode4=0;

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
             input_mode1=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_2->setIcon(ButtonIcon);
             ui->out2mode_2->setIconSize(QSize(61,31));
             //on_out2mode_2_clicked();
         }
         else
         {
             input_mode1=0;
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
             input_mode2=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_6->setIcon(ButtonIcon);
             ui->out2mode_6->setIconSize(QSize(61,31));
            // on_out2mode_6_clicked();
         }
         else
         {
             input_mode2=0;
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
             input_mode3=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_10->setIcon(ButtonIcon);
             ui->out2mode_10->setIconSize(QSize(61,31));
             //on_out2mode_10_clicked();
         }
         else
         {
             input_mode3=0;
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
             input_mode4=1;
             QPixmap pixmap(":/on.jpg");
             QIcon ButtonIcon(pixmap);
             ui->out2mode_9->setIcon(ButtonIcon);
             ui->out2mode_9->setIconSize(QSize(61,31));
             //on_out2mode_9_clicked();
         }
         else
         {
             input_mode4=0;
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

    qDebug()<<"CHINDI PELU"<<endl;
    if(output_mode1==1)
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

    output_mode1=!output_mode1;
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
    pidtab->setpt=arg1.toDouble();
    powtab->setpoint=arg1.toDouble();

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
    QFile decr("bggy.txt");

    decr.open(QIODevice::Append);
    QTextStream obj(&decr);
    obj<<output_mode2<<" ";
    qDebug()<<output_mode2<<" ";
    if(output_mode2==1)
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

    output_mode2=!output_mode2;
qDebug()<<output_mode2<<endl;
    obj<<output_mode2<<" "<<endl;
    decr.close();
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
    pidtab->setpt=arg1.toDouble();
    powtab->setpoint=arg1.toDouble();

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
    if(input_mode1==1)
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

    input_mode1=!input_mode1;
}

void MainWindow::on_out2mode_6_clicked()
{
    if(input_mode2==1)
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

    input_mode2=!input_mode2;
}

void MainWindow::on_out2mode_10_clicked()
{
    if(input_mode3==1)
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

    input_mode3=!input_mode3;
}

void MainWindow::on_out2mode_9_clicked()
{
    if(input_mode4==1)
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

    input_mode4=!input_mode4;
}

void MainWindow::on_comboBox_7_currentIndexChanged(const QString &arg1)
{
       if(arg1=="Diode")
       {
            for(int i=0;i<11;i++)
                ui->comboBox_8->removeItem(0);

                ui->comboBox_8->addItem("2.5V");
            sensor_type1='D';
       }
       else if(sensor_type1=='D')
       {
           ui->comboBox_8->removeItem(0);

           for(int i=0;i<11;i++)
           {
                  ui->comboBox_8->addItem(sensor_range[i]);
           }


           sensor_type1='R';
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
         sensor_type2='D';
    }
    else if(sensor_type2=='D')
    {
        ui->comboBox_16->removeItem(0);

        for(int i=0;i<11;i++)
        {
               ui->comboBox_16->addItem(sensor_range[i]);
        }


        sensor_type2='R';
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
         sensor_type3='D';
    }
    else if(sensor_type3=='D')
    {
        ui->comboBox_24->removeItem(0);

        for(int i=0;i<11;i++)
        {
               ui->comboBox_24->addItem(sensor_range[i]);
        }


        sensor_type3='R';
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
         sensor_type4='D';
    }
    else if(sensor_type4=='D')
    {
        ui->comboBox_22->removeItem(0);

        for(int i=0;i<11;i++)
        {
               ui->comboBox_22->addItem(sensor_range[i]);
        }


        sensor_type4='R';
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
        if(sensor_range[i]==arg1)
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
        if(sensor_range[i]==arg1)
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
        if(sensor_range[i]==arg1)
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
        if(sensor_range[i]==arg1)
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
    if(output_mode3==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_5->setIcon(ButtonIcon);
        ui->out2mode_5->setIconSize(QSize(51,21));

       con();
       outs("Out1.PID.Mode = off");
       clo();
    }
    else
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->out2mode_5->setIcon(ButtonIcon);
        ui->out2mode_5->setIconSize(QSize(51,21));

        con();
        outs("Out1.PID.Mode = on");
        clo();
    }

    output_mode3=!output_mode3;
}

void MainWindow::on_out2mode_4_clicked()
{

    qDebug()<<"CHINDI PELU";

    if(output_mode4==1)
        {
            QPixmap pixmap(":/on-off.jpg");
            QIcon ButtonIcon(pixmap);
            ui->out2mode_4->setIcon(ButtonIcon);
            ui->out2mode_4->setIconSize(QSize(51,21));

           con();
           outs("Out1.PID.Mode = off");
           clo();
        }
        else
        {
            QPixmap pixmap(":/on.jpg");
            QIcon ButtonIcon(pixmap);
            ui->out2mode_4->setIcon(ButtonIcon);
            ui->out2mode_4->setIconSize(QSize(51,21));

            con();
            outs("Out1.PID.Mode = on");
            clo();
        }

        output_mode4=!output_mode4;
}


void MainWindow::on_keithley_clicked()
{
    ke2->show();
}

void MainWindow::on_keithley6_clicked()
{
    ke6->show();
}


void MainWindow::on_powlmt2_clicked()
{
    powtab->show();
}

void MainWindow::on_powlmt1_clicked()
{
    powtab->show();
}
