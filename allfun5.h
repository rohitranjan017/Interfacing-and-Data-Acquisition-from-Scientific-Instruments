#ifndef ALLFUN5_H
#define ALLFUN5_H
#include <QFile>
#include <QTextStream>
QFile ril("script.sh");
void sta5()
{
    //conecting code starts
   ril.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream pout(&ril);
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
void sto5()
{ QTextStream pout(&ril);
    pout<<"send ";
    pout<<"\"";
    pout<<"q";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";
     pout<<"interact\n";

     ril.close();
      system("script -c ./script.sh o.txt");
}
void spre5()
{ QTextStream pout(&ril);
    pout<<"send ";
    pout<<"\"";
    pout<<"w";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";


    pout<<"send ";
    pout<<"\"";
}
void spost5()
{ QTextStream pout(&ril);
    pout<<"\\";
    pout<<"n";
    pout<<"\"";
    pout<<"\n";
}
void pouts5(QString s)
{ QTextStream pout(&ril);

   spre5();
    pout<<s;

}
void read5(QString s)
{QTextStream pout(&ril);
     pouts5(s);
     spost5();
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

void write5(QString s)
{
    pouts5(s);
    spost5();
}
#endif // ALLFUN5_H
