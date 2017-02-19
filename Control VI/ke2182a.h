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
    ~ke2182a();

private:
    Ui::ke2182a *ui;
};

#endif // KE2182A_H
