#ifndef SCRIPTWRITE2_H
#define SCRIPTWRITE2_H
#include <QFile>
#include <QTextStream>

QFile viscriptfile("/home/phy/ControlX/scriptwk.sh");
void start_connection()
{
    //conecting code starts
   viscriptfile.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream vi_out(&viscriptfile);
   vi_out<<"#!/usr/bin/expect\n";
   vi_out<<"spawn ibtest\n";
   vi_out<<"send ";
   vi_out<<"\"";
   vi_out<<"d";
   vi_out<<"\\n";
   vi_out<<"\"";
   vi_out<<"\n";
   vi_out<<"send ";
   vi_out<<"\"";
   vi_out<<"6";
   vi_out<<"\\n";
   vi_out<<"\"";
   vi_out<<"\n";

   //connecting code ends

}
void stop_connection()
{ QTextStream vi_out(&viscriptfile);
    vi_out<<"send ";
    vi_out<<"\"";
    vi_out<<"q";
    vi_out<<"\\n";
    vi_out<<"\"";
    vi_out<<"\n";
    vi_out<<"interact\n";

    viscriptfile.close();
    system("script -c /home/phy/ControlX/./scriptwk.sh /home/phy/ControlX/wk.txt");
}
void intialize_write()
{ QTextStream vi_out(&viscriptfile);
    vi_out<<"send ";
    vi_out<<"\"";
    vi_out<<"w";
    vi_out<<"\\n";
    vi_out<<"\"";
    vi_out<<"\n";

    vi_out<<"send ";
    vi_out<<"\"";
}
void send_enter()
{ QTextStream vi_out(&viscriptfile);
    vi_out<<"\\";
    vi_out<<"n";
    vi_out<<"\"";
    vi_out<<"\n";
}
void send_command(QString s)
{ QTextStream vi_out(&viscriptfile);

   intialize_write();
    vi_out<<s;

}
void read_string(QString s)
{QTextStream vi_out(&viscriptfile);
     send_command(s);
     send_enter();
     vi_out<<"send ";
     vi_out<<"\"";
     vi_out<<"r";
     vi_out<<"\\n";
     vi_out<<"\"";
     vi_out<<"\n";
     vi_out<<"send ";
     vi_out<<"\"";
     vi_out<<"200";
     vi_out<<"\\n";
     vi_out<<"\"";
     vi_out<<"\n";

}
void write_command(QString s)
{
    send_command(s);
    send_enter();
}
#endif // Scriptwritre_H
