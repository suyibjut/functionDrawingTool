#ifndef DIALOGADDFUNTION_H
#define DIALOGADDFUNTION_H

#include <QDialog>

namespace Ui {
class DialogAddFuntion;
}

class DialogAddFuntion : public QDialog
{
    Q_OBJECT

public:
    explicit DialogAddFuntion(QWidget *parent = 0);
    ~DialogAddFuntion();

private slots:
    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_buttonBox_accepted();

private:
    Ui::DialogAddFuntion *ui;
};

#endif // DIALOGADDFUNTION_H
