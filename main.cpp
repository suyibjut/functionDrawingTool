#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include "function1.h"
#include "function2.h"
#include <QDebug>
#include <vector>

std::vector<function1> expression1;
std::vector<function2> expression2;
int function1_count = 0;
int function2_count = 0;
//function1 expression1[5];
//function2 expression2[5];
extern void debug(void);//调试用

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("函数绘制工具");
    //调试
    debug();
    qDebug()<<"debug succeeded!"<<endl;

    w.show();
/*
    QApplication app(argc,argv);
    QWidget w1;

    QPushButton button;
    button.show();

    w1.show();
*/
    return a.exec();
}
