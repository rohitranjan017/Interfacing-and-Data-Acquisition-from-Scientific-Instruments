#ifndef WK_H
#define WK_H

#include <QMainWindow>
#include <QtSql>
#include <QFileInfo>
namespace Ui {
class wk;
}

class wk : public QMainWindow
{
    Q_OBJECT

public:
    explicit wk(QWidget *parent = 0);
    ~wk();
     //Ui::wk *ptr;
private slots:

    void on_pushButton_2_clicked();

    void on_meas_setup_clicked();

    void on_trace_setup_clicked();

    void on_pushButton_clicked();

    void on_trig_clicked();

private:
    Ui::wk *ui;
};

#endif // WK_H
