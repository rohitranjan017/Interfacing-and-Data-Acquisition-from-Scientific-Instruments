#ifndef ALLFUN_H
#define ALLFUN_H
#include <QFile>
#include <QTextStream>
QFile fil("scriptwk.sh");
void sta()
{
    //conecting code starts
   fil.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream pout(&fil);
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
void sto()
{ QTextStream pout(&fil);
    pout<<"send ";
    pout<<"\"";
    pout<<"q";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";
     pout<<"interact\n";

     fil.close();
      system("script -c ./scriptwk.sh wk.txt");
}
void spre()
{ QTextStream pout(&fil);
    pout<<"send ";
    pout<<"\"";
    pout<<"w";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";


    pout<<"send ";
    pout<<"\"";
}
void spost()
{ QTextStream pout(&fil);
    pout<<"\\";
    pout<<"n";
    pout<<"\"";
    pout<<"\n";
}
void pouts(QString s)
{ QTextStream pout(&fil);

   spre();
    pout<<s;

}
void read(QString s)
{QTextStream pout(&fil);
     pouts(s);
     spost();
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

void write(QString s)
{
    pouts(s);
    spost();
}

#endif // ALLFUN_H
