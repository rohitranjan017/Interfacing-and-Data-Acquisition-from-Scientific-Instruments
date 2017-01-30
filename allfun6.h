#ifndef ALLFUN6_H
#define ALLFUN6_H
#include <QFile>
#include <QTextStream>
QFile hil("scriptwk.sh");
void sta6()
{
    //conecting code starts
   hil.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream pout(&hil);
   pout<<"#!/usr/bin/expect\n";
   pout<<"spawn ibtest\n";
   pout<<"send ";
   pout<<"\"";
   pout<<"d";
   pout<<"\\n";
   pout<<"\"";
   pout<<"\n";
   pout<<"send ";
   pout<<"\"";
   pout<<"6";
   pout<<"\\n";
   pout<<"\"";
   pout<<"\n";

   //connecting code ends

}
void sto6()
{ QTextStream pout(&hil);
    pout<<"send ";
    pout<<"\"";
    pout<<"q";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";
     pout<<"interact\n";

     hil.close();
      system("script -c ./scriptwk.sh wk.txt");
}
void spre6()
{ QTextStream pout(&hil);
    pout<<"send ";
    pout<<"\"";
    pout<<"w";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";


    pout<<"send ";
    pout<<"\"";
}
void spost6()
{ QTextStream pout(&hil);
    pout<<"\\";
    pout<<"n";
    pout<<"\"";
    pout<<"\n";
}
void pouts6(QString s)
{ QTextStream pout(&hil);

   spre6();
    pout<<s;

}
void read6(QString s)
{QTextStream pout(&hil);
     pouts6(s);
     spost6();
     pout<<"send ";
     pout<<"\"";
     pout<<"r";
     pout<<"\\n";
     pout<<"\"";
     pout<<"\n";
     pout<<"send ";
     pout<<"\"";
     pout<<"200";
     pout<<"\\n";
     pout<<"\"";
     pout<<"\n";

}

void write6(QString s)
{
    pouts6(s);
    spost6();
}
#endif // ALLFUN6_H
