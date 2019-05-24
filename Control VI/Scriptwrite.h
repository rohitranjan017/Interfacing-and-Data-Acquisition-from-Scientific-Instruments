#ifndef SCRIPTWRITE_H
#define SCRIPTWRITE_H
#include <QFile>
#include <QTextStream>
QFile viscript("/home/phy/ControlVI/scriptwk.sh");
void start_connection_VI(int address=6)
{
    //conecting code starts
   viscript.open(QIODevice::WriteOnly| QIODevice::Text);
    QTextStream vi_out(&viscript);
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
   vi_out<<QString::number(address);
   vi_out<<"\\n";
   vi_out<<"\"";
   vi_out<<"\n";

   //connecting code ends

}
void stop_connection_VI()
{ QTextStream vi_out(&viscript);
    vi_out<<"send ";
    vi_out<<"\"";
    vi_out<<"q";
    vi_out<<"\\n";
    vi_out<<"\"";
    vi_out<<"\n";
    vi_out<<"interact\n";

    viscript.close();
    system("script -c /home/phy/ControlVI/./scriptwk.sh /home/phy/ControlVI/wk.txt");
}
void intialize_write_VI()
{ QTextStream vi_out(&viscript);
    vi_out<<"send ";
    vi_out<<"\"";
    vi_out<<"w";
    vi_out<<"\\n";
    vi_out<<"\"";
    vi_out<<"\n";

    vi_out<<"send ";
    vi_out<<"\"";
}
void send_enter_VI()
{ QTextStream vi_out(&viscript);
    vi_out<<"\\";
    vi_out<<"n";
    vi_out<<"\"";
    vi_out<<"\n";
}
void send_command_VI(QString s)
{ QTextStream vi_out(&viscript);

   intialize_write_VI();
    vi_out<<s;

}
void read_string_VI(QString s)
{QTextStream vi_out(&viscript);
     send_command_VI(s);
     send_enter_VI();
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
void write_command_VI(QString s)
{
    send_command_VI(s);
    send_enter_VI();
}
#endif // Scriptwritre_H
