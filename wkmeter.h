#ifndef WKMETER_H
#define WKMETER_H

#include <QMainWindow>

namespace Ui {
class wkmeter;
}

class wkmeter : public QMainWindow
{
    Q_OBJECT

public:
    explicit wkmeter(QWidget *parent = 0);
    ~wkmeter();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::wkmeter *ui;
};

#endif // WKMETER_H
