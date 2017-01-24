#ifndef WK_H
#define WK_H

#include <QMainWindow>

namespace Ui {
class wk;
}

class wk : public QMainWindow
{
    Q_OBJECT

public:
    explicit wk(QWidget *parent = 0);
    ~wk();

private slots:

    void on_pushButton_2_clicked();

    void on_meas_setup_clicked();

    void on_trace_setup_clicked();

private:
    Ui::wk *ui;
};

#endif // WK_H
