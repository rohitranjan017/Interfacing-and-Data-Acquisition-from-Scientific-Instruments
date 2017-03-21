#ifndef KE2182A_H
#define KE2182A_H

#include <QDialog>

namespace Ui {
class ke2182a;
}

class ke2182a : public QDialog
{
    Q_OBJECT

public:
    explicit ke2182a(QWidget *parent = 0);
    int total_points;
    ~ke2182a();

private slots:

    void on_NoofPoints_valueChanged(double arg1);

    void on_ok_clicked();

private:
    Ui::ke2182a *ui;
};

#endif // KE2182A_H
