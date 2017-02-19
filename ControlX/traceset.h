#ifndef TRACESET_H
#define TRACESET_H

#include <QDialog>
namespace Ui {
class traceset;
}

class traceset : public QDialog
{
    Q_OBJECT

public:
    explicit traceset(QWidget *parent = 0);
    ~traceset();

private slots:
    void on_buttonBox_accepted();

    void on_spinBox_valueChanged(const QString &arg1);

    void on_spinBox_2_valueChanged(const QString &arg1);

    void on_checkBox_clicked();

    void on_comboBox_4_activated(const QString &arg1);

    void on_spinBox_3_valueChanged(const QString &arg1);

private:
    Ui::traceset *ui;
};

#endif // TRACESET_H
