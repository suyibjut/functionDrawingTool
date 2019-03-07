#include "addfunction.h"
#include "ui_addfunction.h"

AddFunction::AddFunction(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddFunction)
{
    ui->setupUi(this);
}

AddFunction::~AddFunction()
{
    delete ui;
}
