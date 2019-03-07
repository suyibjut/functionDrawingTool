#include "dialogaddfuntion.h"
#include "ui_dialogaddfuntion.h"
#include "mainwindow.h"
#include "function1.h"
#include "function2.h"
#include <QDebug>
#include <QColor>
#include <QMessageBox>
#include <vector>

extern int function1_count;
extern int function2_count;
extern std::vector<function1> expression1;
extern std::vector<function2> expression2;
//extern function1 expression1[5];
//extern function2 expression2[5];

DialogAddFuntion::DialogAddFuntion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAddFuntion)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    ui->radioButton->setChecked(true);

    ui->label_3->setVisible(true);//f(x)=
    ui->lineEdit->setVisible(true);//f(x)输入框

    ui->label_4->setVisible(false);//x(t)=
    ui->label_5->setVisible(false);//y(t)=
    ui->lineEdit_2->setVisible(false);//x(t)输入框
    ui->lineEdit_3->setVisible(false);//y(t)输入框

    QStringList combo_color;
    combo_color << QString("red") << QString("yellow") << QString("green") << QString("blue") << QString("black");
    ui->comboBox->addItems(combo_color);
    ui->comboBox->setItemData(0, QColor(Qt::red), Qt::BackgroundColorRole);
    ui->comboBox->setItemData(1, QColor(Qt::yellow), Qt::BackgroundColorRole);
    ui->comboBox->setItemData(2, QColor(Qt::green), Qt::BackgroundColorRole);
    ui->comboBox->setItemData(3, QColor(Qt::blue), Qt::BackgroundColorRole);
    ui->comboBox->setItemData(4, QColor(Qt::black), Qt::BackgroundColorRole);
    ui->comboBox->setItemData(4, QColor(Qt::white), Qt::TextColorRole);

    QStringList combo_type;
    combo_type << QString("type1") << QString("type2") << QString("type3") << QString("type4");
    ui->comboBox_2->addItems(combo_type);

    ui->lineEdit->setFont(QFont("微软雅黑",20,QFont::Bold));
    ui->lineEdit_2->setFont(QFont("微软雅黑",20,QFont::Bold));
    ui->lineEdit_3->setFont(QFont("微软雅黑",20,QFont::Bold));
    ui->label_3->setFont(QFont("微软雅黑",12,QFont::Bold));
    ui->label_4->setFont(QFont("微软雅黑",12,QFont::Bold));
    ui->label_5->setFont(QFont("微软雅黑",12,QFont::Bold));
}

DialogAddFuntion::~DialogAddFuntion()
{
    delete ui;
}
//点击radiobutton1时显示输入框1
void DialogAddFuntion::on_radioButton_clicked()
{
    ui->label_3->setVisible(true);
    ui->lineEdit->setVisible(true);

    ui->label_4->setVisible(false); //x(t)=
    ui->label_5->setVisible(false);//y(t)=
    ui->lineEdit_2->setVisible(false);//x(t)输入框
    ui->lineEdit_3->setVisible(false);//y(t)输入框
}
//点击radiobutton1时显示输入框2，3
void DialogAddFuntion::on_radioButton_2_clicked()
{
    ui->label_3->setVisible(false);
    ui->lineEdit->setVisible(false);

    ui->label_4->setVisible(true); //x(t)=
    ui->label_5->setVisible(true);//y(t)=
    ui->lineEdit_2->setVisible(true);//x(t)输入框
    ui->lineEdit_3->setVisible(true);//y(t)输入框
}
//点击ok时
void DialogAddFuntion::on_buttonBox_accepted()
{
    //f(x)时 函数表达式
    if(ui->radioButton->isChecked()){
        QString function1_expression= ui->lineEdit->text();
        QString line_color = ui->comboBox->currentText();
        QString line_type = ui->comboBox_2->currentText();

//        qDebug()<<line_type<<endl;
//        qDebug()<<line_color<<endl;
        qDebug()<<function1_expression<<endl;
        //生成临时对象 获得信息
        function1 *function_test = new function1;
        if(function_test->check_input(function1_expression)){
            qDebug()<<"checked"<<endl;
            function1 exp;
            exp.get_expression(function1_expression,line_color,line_type);
            expression1.push_back(exp);
            //expression1.back().get_expression(function1_expression,line_color,line_type);
            //expression1[function1_count].get_expression(function1_expression, line_color, line_type);
//            qDebug()<<expression1[function1_count].calculate_function(2)<<endl;
            //            qDebug()<<expression1[function1_count].calculate_function(2.00)<<endl;
//            w.refresh_table();
            MainWindow *ptr = (MainWindow*) parentWidget();
            ptr->refresh_table1();
            parentWidget()->show();
            delete this;
//
            //function1_count++;
            qDebug()<<"function1 count:"<<expression1.size()<<endl;
            qDebug()<<"function2 count:"<<expression2.size()<<endl;
            delete function_test;
        }
        else{
            delete function_test;
            QMessageBox::about(NULL, "error", "input error");
        }
    }
    //x(t) y(t)时 函数表达式
    else if(ui->radioButton_2->isChecked()){
        QString  function2_expression1,function2_expression2;
        function2_expression1 = ui->lineEdit_2->text();
        function2_expression2 = ui->lineEdit_3->text();
        QString line_color = ui->comboBox->currentText();
        QString line_type = ui->comboBox_2->currentText();

//        qDebug()<<line_type<<endl;
//        qDebug()<<line_color<<endl;
        qDebug()<<function2_expression1<<endl;
        qDebug()<<function2_expression2<<endl;
        //生成临时对象 获得信息
        function2 *function_test = new function2;
        if(function_test->check_input(function2_expression1, function2_expression2)){
            qDebug()<<"checked"<<endl;
            function2 exp;
            exp.get_expression(function2_expression1,function2_expression2,line_color,line_type);
            expression2.push_back(exp);
            //expression2.back().get_expression(function2_expression1,function2_expression2,line_color,line_type);
            //expression2[function2_count].get_expression(function2_expression1, function2_expression2, line_color, line_type);
//            qDebug()<<expression2[function2_count].calculate_function(1, 3.14)<<endl;
//            qDebug()<<expression2[function2_count].calculate_function(2, 3.14)<<endl;
            MainWindow *ptr = (MainWindow*) parentWidget();
            ptr->refresh_table2();
            parentWidget()->show();
            delete this;
//
            //function2_count++;
            qDebug()<<"function1 count:"<<expression1.size()<<endl;
            qDebug()<<"function2 count:"<<expression2.size()<<endl;
            delete function_test;
        }
        else{
            delete function_test;
            QMessageBox::about(NULL, "error", "input error");
        }
    }


}
