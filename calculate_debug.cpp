#include "function1.h"
#include "function2.h"
#include <QDebug>

void debug(void){

    //实体化
    function1 test;
    //设定
    test.get_expression(QString("sin(exp(X))"),QString("red"),QString("type1"));
    //计算
    qDebug()<<test.calculate_function(0.00);


}
