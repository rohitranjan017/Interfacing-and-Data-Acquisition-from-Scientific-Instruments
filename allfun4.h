#ifndef ALLFUN4_H
#define ALLFUN4_H
#include <QFile>
#include <QTextStream>
QFile til("scriptwk.sh");
void sta4()
{
    //conecting code starts
   til.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream pout(&til);
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
void sto4()
{ QTextStream pout(&til);
    pout<<"send ";
    pout<<"\"";
    pout<<"q";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";
     pout<<"interact\n";

     til.close();
      system("script -c ./scriptwk.sh wk.txt");
}
void spre4()
{ QTextStream pout(&til);
    pout<<"send ";
    pout<<"\"";
    pout<<"w";
    pout<<"\\n";
    pout<<"\"";
    pout<<"\n";


    pout<<"send ";
    pout<<"\"";
}
void spost4()
{ QTextStream pout(&til);
    pout<<"\\";
    pout<<"n";
    pout<<"\"";
    pout<<"\n";
}
void pouts4(QString s)
{ QTextStream pout(&til);

   spre4();
    pout<<s;

}
void read4(QString s)
{QTextStream pout(&til);
     pouts4(s);
     spost4();
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

void write4(QString s)
{
    pouts4(s);
    spost4();
}

#endif // ALLFUN4_H
