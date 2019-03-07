#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAbstractItemView>
#include "function1.h";
#include "function2.h";
#include <vector>
#include <QMessageBox>
#include <QDebug>

//extern function1 expression1[5];
//extern function2 expression2[5];
//extern int function1_count;
//extern int function2_count;
extern std::vector<function1> expression1;
extern std::vector<function2> expression2;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    ui->pushButton->setText("Add");
    ui->pushButton_2->setText("Draw");
    ui->pushButton_3->setText("Delete");
    ui->label->setOpenExternalLinks(true);
    //函数列表
    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setRowCount(0);
//    ui->tableWidget->horizontalHeader()->setClickable(false);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setColumnWidth(0,400);
    ui->tableWidget->setColumnWidth(1,100);
    ui->tableWidget->horizontalHeader()->setFixedHeight(50);
    ui->tableWidget->setStyleSheet("selection-background-color:green;");
    ui->tableWidget->setStyleSheet("QHeaderView::section{background:skyblue;}");
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);

}

MainWindow::~MainWindow()
{
    delete ui;
}


//按下Add，创建窗口对象
void MainWindow::on_pushButton_clicked()
{
    dialog = new DialogAddFuntion(this);
    dialog->setModal(true);  //模态
    dialog->setWindowTitle("添加函数");
    dialog->show();
}
//按下draw
void MainWindow::on_pushButton_2_clicked()
{
    draw = new DialogDraw(this);
    draw->setModal(true);
    draw->setWindowTitle("绘图");
//    draw->refresh_graph();//产生图形
    draw->show();
}
//addfunction1完成后
void MainWindow::refresh_table1(void){
    int row_count = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row_count);//插入新行
    ui->tableWidget->setItem(row_count,0,new QTableWidgetItem("Y= "+ expression1.back().read_expression()));
    ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(expression1.back().read_line_color()));
    ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(expression1.back().read_line_type()));
     //     QTableWidgetItem *item = new QTableWidgetItem();
}

//addfunction2完成后
void MainWindow::refresh_table2(void){
    int row_count = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(row_count);
    ui->tableWidget->setItem(row_count,0,new QTableWidgetItem("X= "+ expression2.back().read_expression1() +"   Y= "+ expression2.back().read_expression2()));
    ui->tableWidget->setItem(row_count,1,new QTableWidgetItem(expression2.back().read_line_color()));
    ui->tableWidget->setItem(row_count,2,new QTableWidgetItem(expression2.back().read_line_type()));


}
//按下delete后删除选中行
void MainWindow::on_pushButton_3_clicked()
{
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    int rowIndex = ui->tableWidget->currentRow();
    //qDebug()<<rowIndex<<endl;
    if((rowIndex!=-1)&&(expression1.size()!=0)||(expression2.size()!=0)){
        QList<QTableWidgetItem*> items = ui->tableWidget->selectedItems();
        QTableWidgetItem *item = items.at(0);
        QString exp = item->text();//读取选中行的表达式
        qDebug()<<exp<<endl;
        //找到vector中对应对象并删除

        if(exp[0]=='Y'){
            QString str_x = exp.mid(3);
            int j;
            for(j=0;j<expression1.size();j++){
                if(str_x==expression1[j].read_expression()) break;
            }
            expression1.erase(expression1.begin()+j,expression1.begin()+j+1);
            qDebug()<<j<<"deleted"<<endl;
            qDebug()<<"expression1 count:"<<expression1.size()<<endl;
        }
        else{
            int j;
            for(j=3;j<exp.length();j++){
                if(exp[j]==' ') break;
            }
            QString str_x = exp.mid(3,j-3);
            //qDebug()<<str_x;
            int i;
            for(i=0;i<expression2.size();i++){
                if(str_x==expression2[i].read_expression1()) break;
            }
            expression2.erase(expression2.begin()+i,expression2.begin()+i+1);
            qDebug()<<i<<"deleted"<<endl;
            qDebug()<<"expression2 count:"<<expression2.size()<<endl;
        }
    }

    if(rowIndex != -1) ui->tableWidget->removeRow(rowIndex);
//    qDebug()<<rowIndex<<endl;


}
/*
//使用说明
void MainWindow::on_action_triggered()
{

}
*/
