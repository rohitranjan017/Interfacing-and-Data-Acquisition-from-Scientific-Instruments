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
QVector< QString > vec;
int j;
void readfile()
{
    QFile file("/home/dell/build-CTC100-Desktop_Qt_5_7_0_GCC_64bit-Debug/o.txt");

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

void writelog()
{
    /*sta();
    read("ANA:POINTS?");
    sto();

       readfile();

     QFile file1("/home/dell/build-CTC100-Desktop_Qt_5_7_0_GCC_64bit-Debug/Graphs/"+props[j]+"~Freq"+".txt");
     QFile file2("/home/dell/build-CTC100-Desktop_Qt_5_7_0_GCC_64bit-Debug/Graphs/"+props[j+1]+"~Freq"+".txt");

     file1.open(QFile::WriteOnly |QFile::Text);
     file2.open(QFile::WriteOnly |QFile::Text);

     QTextStream out1(&file1);
     QTextStream out2(&file2);

    int tot=vec[0].toInt();
        qDebug()<<vec[0];

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
    delay(ui->spinBox_3->value());*/

    for(int i=0;i<1;i++)
    {int temp=250;
        /*sta();
        write("ANA:PROP1 "+props[i]);
        write("ANA:FIT 3");
        sto();*/

        QFile file1("/home/dell/build-CTC100-Desktop_Qt_5_7_0_GCC_64bit-Debug/Graphs/"+props[i]+"~Freq"+".txt");
        file1.open(QFile::ReadWrite);

        QTextStream out(&file1);

        out<<temp<<"             ";

        /*sta();

        for(int i=0;i<=tot;i++)
        {
           read("ANA:POINT? "+QString::number(i));
        }

        sto();*/

        readfile();

        for(int i=0;i<10;i++)
        {
            QStringList my = vec[i].split(',');
            out<<my[1]<<"       ";
        }


    }
}

void delay1( int millisecondsToWait )
{
    millisecondsToWait*=1000;

    QTime dieTime = QTime::currentTime().addMSecs( millisecondsToWait );
    while( QTime::currentTime() < dieTime )
    {
        QCoreApplication::processEvents( QEventLoop::AllEvents, 100 );
    }
}
bool biasm=0;
wk::wk(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::wk)
{

    ui->setupUi(this);

    this->setWindowTitle("Analysis Mode");

    /*sta();
    read("ANA:BIAS-STAT?");
    sto();

    readfile();*/

    /*if(vec[0]=="0")
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
    }*/


    //Graphs...1


    for(int i=0;i<11;i++)
    {
        axisX[i]=new QCategoryAxis();
        //axisY[i]=new QCategoryAxis();
        axisY[i]=new QLogValueAxis();
        // d, i, o, x, X, f, F, e, E, g, G, c.
        axisY[i]->setLabelFormat("%d");
        axisY[i]->setBase(10);
        axisY[i]->setLabelsVisible(true);
        //axisY[i]->QObject
        //axisY[i]->set
    }


    for(int i=0;i<11;i++){
    series[i] = new QLineSeries();
    chart[i] = new QChart();
    chart[i]->addSeries(series[i]);
     axisX[i]->setRange(0,500);
     //axisX[i]->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
     //axisY[i]->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
     axisY[i]->setRange(1, 10000000);
     chart[i]->setAxisX(axisX[i], series[i]);
     //chart[i]->setAxisY(axisY[i], series[i]);
     chart[i]->addAxis(axisY[i], Qt::AlignLeft);
     series[i]->attachAxis(axisY[i]);

    chartView[i] = new QChartView(chart[i]);
    }

     qreal num;
   //QString s[22]={"1n","10n","100n","1u","10u","100u","1m","10m","100m","1","10","100","1k","10k","100k","1M","10M","100M","1G","10G","100G","1T"};
    //int q=0;
    /*for(double j=1.0e-9;j<=1.0e+11;j*=10,q++)
    {
        for(int i=0;i<11;i++)
        {
            num=j;
            axisY[i]->append(s[q],num);
        }
    }*/
        /*
        //Graphs...2
        series2 = new QLineSeries();
        chart2 = new QChart();

        chart2->addSeries(series1);
        chart2->createDefaultAxes();
        QCategoryAxis *axisX = new QCategoryAxis();
        QCategoryAxis *axisY = new QCategoryAxis();

           axisX->append("low", 10);
            axisX->append("optimal", 20);
            axisX->append("high", 30);
            axisX->append("Very High",40);
            axisX->setRange(0, 40);
            axisX->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
            axisY->setLabelsPosition(QCategoryAxis::AxisLabelsPositionOnValue);
            axisY->append("slow", 10);
            axisY->append("med", 20);
            axisY->append("fast", 30);
            axisY->setRange(0, 40);

            chart1->setAxisX(axisX, series1);
            chart1->setAxisY(axisY, series1);
            chartView1 = new QChartView(chart1);

            ui->gridLayout_4->addWidget(chartView1);
            */
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

            //QLineSeries *serie = new QLineSeries();
            //*serie << QPointF(1, 1) << QPointF(2, 73) << QPointF(3, 268) << QPointF(4, 17) << QPointF(5, 4325) << QPointF(6, 723);

            //chart[0]->addSeries(serie);

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
   /* sta();
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

    }*/
    writelog();

}
