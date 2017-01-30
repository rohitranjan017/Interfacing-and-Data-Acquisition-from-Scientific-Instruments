#ifndef ALLFUN3_H
#define ALLFUN3_H
#include <QFile>
#include <QTextStream>
QFile gil("scriptwk.sh");
void sta3()
{
    //conecting code starts
   gil.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream pout(&gil);
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
void sto3()
{ QTextStream pout(&gil);
    pout<<"send ";
    pout<<"\"";
    pout<<"q";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";
     pout<<"interact\n";

     gil.close();
      system("script -c ./scriptwk.sh wk.txt");
}
void spre3()
{ QTextStream pout(&gil);
    pout<<"send ";
    pout<<"\"";
    pout<<"w";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";


    pout<<"send ";
    pout<<"\"";
}
void spost3()
{ QTextStream pout(&gil);
    pout<<"\\";
    pout<<"n";
    pout<<"\"";
    pout<<"\n";
}
void pouts3(QString s)
{ QTextStream pout(&gil);

   spre3();
    pout<<s;

}
void read3(QString s)
{QTextStream pout(&gil);
     pouts3(s);
     spost3();
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

void write3(QString s)
{
    pouts3(s);
    spost3();
}

#endif // ALLFUN3_H
