#ifndef ADDFUNCTION_H
#define ADDFUNCTION_H

#include <QDialog>

namespace Ui {
class AddFunction;
}

class AddFunction : public QDialog
{
    Q_OBJECT

public:
    explicit AddFunction(QWidget *parent = 0);
    ~AddFunction();

private:
    Ui::AddFunction *ui;
};

#endif // ADDFUNCTION_H
