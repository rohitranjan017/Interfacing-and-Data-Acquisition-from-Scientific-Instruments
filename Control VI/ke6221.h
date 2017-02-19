#ifndef KE6221_H
#define KE6221_H

#include <QDialog>

namespace Ui {
class ke6221;
}

class ke6221 : public QDialog
{
    Q_OBJECT

public:
    explicit ke6221(QWidget *parent = 0);
    ~ke6221();

private slots:
    void on_Output_clicked();

    void on_SetFilter_2_clicked();

    void on_RangeType_currentIndexChanged(const QString &arg1);

private:
    Ui::ke6221 *ui;
};

#endif // KE6221_H
