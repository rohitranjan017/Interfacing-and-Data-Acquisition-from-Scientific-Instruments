#include "wk.h"
#include "ui_wk.h"
#include "measureset.h"
#include "traceset.h"
#include "wkmeter.h"
#include "QFile"
#include "QTextStream"
#include <QDebug>
#include "allfun4.h"
#include <QPixmap>
#define sta sta4
#define sto sto4
#define read read4
#define write write4
#define delay delay1
#include <QTime>
#include <wk.h>
QString props[12]={"L","C","Q","D","R","X","Z","Y","Angle","B","G","L"};
QString propy[11]={"Inductance","Capacitance","Q-factor","D-factor","Resistance","Reactance","Impedance","Admittance","Angle","Susceptance","Conductance"};
QVector< QString > vec;
int j; int pt; qreal mi,Ma;

QFile fi("/home/dell/build-CTC100-Desktop_Qt_5_8_0_GCC_64bit-Debug/check.txt");
QTextStream foo(&fi);


void delay1( int millisecondsToWait )
{
    millisecondsToWait*=1000;

    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
void readfile()
{
    QFile file("/home/dell/build-CTC100-Desktop_Qt_5_8_0_GCC_64bit-Debug/wk.txt");


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
                //qDebug()<<temp;
            }
    }
}

void wk::writelog()
{
    sta();
    read("ANA:POINTS?");
    sto();

       readfile();

     QFile file1("/home/dell/build-CTC100-Desktop_Qt_5_8_0_GCC_64bit-Debug/Graphs/"+props[j]+"~Freq"+".txt");
     QFile file2("/home/dell/build-CTC100-Desktop_Qt_5_8_0_GCC_64bit-Debug/Graphs/"+props[j+1]+"~Freq"+".txt");

     file1.open(QFile::WriteOnly |QFile::Text);
     file2.open(QFile::WriteOnly |QFile::Text);

     QTextStream out1(&file1);
     QTextStream out2(&file2);

    int tot=vec[0].toInt();
        //qDebug()<<vec[0];

    sta();

    for(int i=0;i<tot;i++)
    {
       read("ANA:POINT? "+QString::number(i));
    }

    sto();

    readfile();

    out1<<"Frquency(Hz)"<<"                "<<props[j]<<endl<<endl;
    out2<<"Frquency(Hz)"<<"                "<<props[j+1]<<endl<<endl;




    for(int i=0;i<tot;i++)
    {
        QStringList my = vec[i].split(',');
        out1<<my[0]<<"        "<<my[1]<<endl;
        out2<<my[0]<<"        "<<my[2]<<endl;

    }
    //delay(ui->spinBox_3->value());

    for(int i=0;i<11;i++)
    {int temp=250;
        sta();
        write("ANA:PROP1 "+props[i]);
        write("ANA:FIT 3");
        sto();

        QFile file1("/home/dell/build-CTC100-Desktop_Qt_5_8_0_GCC_64bit-Debug/Graphs/"+props[i]+"~Freq"+".txt");
        file1.open(QFile::ReadWrite);

        QTextStream out(&file1);

        out<<temp<<"             ";

        sta();

        for(int i=0;i<=tot;i++)
        {
           read("ANA:POINT? "+QString::number(i));
        }

        sto();

        readfile();

        for(int i=0;i<11;i++)
        {
            QStringList my = vec[i].split(',');
            out<<my[1]<<"       ";
        }


    }
}


bool biasm=0;
wk::wk(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wk)
{

    ui->setupUi(this);

fi.open(QIODevice::ReadOnly);
    this->setWindowTitle("Analysis Mode");

    sta();
    read("ANA:BIAS-STAT?");
    sto();

    readfile();

    if(vec[0][0]=="0")
    {
        QPixmap pixmap(":/on.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton->setIcon(ButtonIcon);
        ui->pushButton->setIconSize(QSize(61,31));
        biasm=1;
    }
    else
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton->setIcon(ButtonIcon);
        ui->pushButton->setIconSize(QSize(61,31));
        biasm=0;
    }


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

wk::~wk()
{
    delete ui;

}

void wk::on_pushButton_2_clicked()
{
    wkmeter* ptr=new wkmeter;
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

void wk::on_pushButton_clicked()
{
    if(biasm==1)
    {
        QPixmap pixmap(":/on-off.jpg");
        QIcon ButtonIcon(pixmap);
        ui->pushButton->setIcon(ButtonIcon);
        ui->pushButton->setIconSize(QSize(61,31));
        biasm=0;
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
        biasm=1;
        sta();
        write("ANA:BIAS-STAT ON");
        sto();

    }
}

void wk::on_trig_clicked()
{
    sta();
    write("ANA:TRIG");
    sto();

    delay(50);

    for( j=0;j<11;j+=2)
    {
        sta();
        write("ANA:PROP1 "+props[j]);
        write("ANA:PROP2 "+props[j+1]);
        write("ANA:FIT 3");
        sto();

        writelog();

    }
    //writelog();

}

/*void wk::on_add_clicked()
{
   // fi.open(QIODevice::ReadOnly);



    char a[1025];

        fi.readLine(a,sizeof(a));
        QString cur=a;
    double yt=cur.toDouble();
    fi.readLine(a,sizeof(a));
    cur=a;
    double xt=cur.toDouble();
    qreal y=qreal(yt);
    qreal x=qreal(xt);

    series[3]->append(x,y);

    if(pt==0)
    {
        if(y>0)
        {mi=y-y/50; Ma=y+y/50;}
        else
        {mi=y+y/50; Ma=y-y/50;}

        axisX[3]->setRange(x-5,x+5);
    }
    else
    {
        if(y<mi)
            mi=y-(mi-y);
        else
        if(y>Ma)
            Ma=y+(y-Ma);
        axisX[3]->setMax(x+5);

    }


    axisY[3]->setRange(mi,Ma); pt++;


foo<<y<<" "<<mi<<" "<<Ma<<endl;
    //series[0]->attachAxis(axisY[0]);

}*/
