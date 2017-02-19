#ifndef CUSTOM_H
#define CUSTOM_H

#include <QDialog>

namespace Ui {
class custom;
}

class custom : public QDialog
{
    Q_OBJECT

public:

    explicit custom(QWidget *parent = 0);
    ~custom();


private slots:
    void on_buttonBox_accepted();

private:
    Ui::custom *ui;
};
#endif // CUSTOM_H
