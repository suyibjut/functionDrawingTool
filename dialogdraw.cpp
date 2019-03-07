#include "dialogdraw.h"
#include "ui_dialogdraw.h"
#include "qcustomplot.h"
#include <QColor>
#include <QDebug>
#include <QVector>
#include <vector>
#include "function1.h"
#include "function2.h"
//extern int function1_count;
//extern int function2_count;
extern std::vector<function1> expression1;
extern std::vector<function2> expression2;

DialogDraw::DialogDraw(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogDraw)
{
    ui->setupUi(this);
    setFixedSize(this->width(),this->height());
    //隐藏网格线
    ui->widget->xAxis->grid()->setVisible(false);
    ui->widget->yAxis->grid()->setVisible(false);
    //坐标轴箭头
    ui->widget->xAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    ui->widget->yAxis->setUpperEnding(QCPLineEnding::esSpikeArrow);
    //坐标轴名
    ui->widget->xAxis->setLabel(QString('X'));
    ui->widget->yAxis->setLabel(QString('Y'));
    //拖拽 缩放
    ui->widget->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    //背景色
    ui->widget->setBackground(QBrush(Qt::darkGray));

    qDebug()<<"start drawing"<<endl;
//    qDebug()<<expression1.size()<<" "<<expression2.size()<<endl;
    //function1图像
    QVector<QVector<double>> y(expression1.size());
    for (int m = 0; m < y.size(); m++)
        y[m].resize(2001);
    for(int m = 0; m < y.size(); m++)
    {
        for (int n = 0; n < y[0].size(); n++)
        {
            y[m][n] = (m+1)*(n+1);
        }
    }
    QVector<QVector<double>> x(expression1.size());
    for (int m = 0; m < x.size(); m++)
        x[m].resize(2001);
    for(int m = 0; m < x.size(); m++)
    {
        for (int n = 0; n < x[0].size(); n++)
        {
            x[m][n] = (m+1)*(n+1);
        }
    }
    //QVector<double> x(2001);

    int i = 0;
//    qDebug()<<"function1_count: "<<function1_count<<endl;
    for(i=0;i<expression1.size();i++){

        ui->widget->addGraph();
//        qDebug()<<"graph added"<<endl;
        //设置颜色
        QPen pen;
        if(expression1[i].read_line_color()==QString("red"))
            pen.setColor(QColor(Qt::red));
        else if(expression1[i].read_line_color()==QString("yellow"))
            pen.setColor(QColor(Qt::yellow));
        else if(expression1[i].read_line_color()==QString("blue"))
            pen.setColor(QColor(Qt::blue));
        else if(expression1[i].read_line_color()==QString("green"))
            pen.setColor(QColor(Qt::green));
        else if(expression1[i].read_line_color()==QString("black"))
            pen.setColor(QColor(Qt::black));

        //设置线型
        if(expression1[i].read_line_type()=="type1")
            pen.setStyle(Qt::SolidLine);
        else if(expression1[i].read_line_type()=="type2")
            pen.setStyle(Qt::DashLine);
        else if(expression1[i].read_line_type()=="type3")
            pen.setStyle(Qt::DotLine);
        else if(expression1[i].read_line_type()=="type4")
            pen.setStyle(Qt::DashDotLine);

        ui->widget->graph(i)->setPen(pen);

        //计算点坐标
        for(int j=0;j<2001;++j){
            bool flag = 0;
            //含有ln
            for(int k=0;k<expression1[i].read_expression().length();k++){
                if(expression1[i].read_expression()[k]=='l'){
                    flag = 1;
                    //qDebug()<<"含有ln"<<endl;
                    break;
                }
                /*
                else if(expression1[i].read_expression()[k]=='^'){
                    flag = 1;
                    break;
                }
                */
            }
            if(flag==0){
                x[i][j] = j/50.0 - 20;
            }
            else{
                x[i][j] = j/50.0 + 0.0001;
            }
//            qDebug()<<expression1[0].calculate_function(1)<<endl;
            y[i][j] = expression1[i].calculate_function(x[i][j]);
            //qDebug()<<'('<<x[i][j]<<','<<y[i][j]<<')'<<endl;
        }
    }
//    qDebug()<<"add graph finished"<<endl;
    //设置数据
    for(i=0;i<expression1.size();i++){
        ui->widget->graph(i)->setData(x[i],y[i]);
        //
//        ui->widget->graph(i)->rescaleAxes(true);
//        qDebug()<<"set data "<<i;
    }
//    qDebug()<<"set data finished"<<endl;





    //function2图像
    QVector<QVector<double>> y1(expression2.size());
    for (int m = 0; m < y1.size(); m++)
        y1[m].resize(251);
    for(int m = 0; m < y1.size(); m++)
    {
        for (int n = 0; n < y1[0].size(); n++)
        {
            y1[m][n] = (m+1)*(n+1);
        }
    }
    QVector<QVector<double>> x1(expression2.size());
    for (int m = 0; m < x1.size(); m++)
        x1[m].resize(251);
    for(int m = 0; m < x1.size(); m++)
    {
        for (int n = 0; n < x1[0].size(); n++)
        {
            x1[m][n] = (m+1)*(n+1);
        }
    }

//    qDebug()<<"space prepared"<<endl;

/*
        for(int j=0;j<251;++j){

            x1[i][j] = expression2[i].calculate_function(1,j/79.58-1.57);
    //            qDebug()<<expression1[0].calculate_function(1)<<endl;
            y1[i][j] = expression2[i].calculate_function(2,j/79.58-1.57);
//            qDebug()<<'('<<x1[j]<<','<<y1[i][j]<<')'<<endl;
        }
    }
*/
    for(i=0;i<expression2.size();i++){
        bool flag = 0;
        for(int j=0;j<expression2[i].read_expression1().length();j++){
            if(expression2[i].read_expression1()[j]=='s'||expression2[i].read_expression1()[j]=='c'||(expression2[i].read_expression1()[j]=='a'&&expression2[i].read_expression1()[j+1]=='r')||(expression2[i].read_expression1()[j]=='t'&&expression2[i].read_expression1()[j+1]=='a')){
                flag = 1;
                break;
            }
        }
        for(int j=0;j<expression2[i].read_expression2().length();j++){
            if(expression2[i].read_expression2()[j]=='s'||expression2[i].read_expression2()[j]=='c'||(expression2[i].read_expression2()[j]=='a'&&expression2[i].read_expression1()[j+1]=='r')||(expression2[i].read_expression2()[j]=='t'&&expression2[i].read_expression2()[j+1]=='a')){
                flag = 1;
                break;
            }
        }
        //三角函数
        if(flag==1){
            qDebug()<<"三角函数"<<endl;
            int j;
            for(j=0;j<251;j++){
                x1[i][j] = expression2[i].calculate_function(1,j/19.875-6.283);
        //        qDebug()<<expression1[0].calculate_function(1)<<endl;
                y1[i][j] = expression2[i].calculate_function(2,j/19.875-6.283);
                //qDebug()<<'('<<x2[i][j]<<','<<y2[i][j]<<')'<<endl;
            }
        }
        else{
            int j;
            bool flag2 = 0;
            for(j=0;j<expression2[i].read_expression1().length();j++){
                if(expression2[i].read_expression1()[j]=='l'){
                    flag2 = 1;
                    break;
                }
            }
            for(j=0;j<expression2[i].read_expression2().length();j++){
                if(expression2[i].read_expression2()[j]=='l'){
                    flag2 = 1;
                    break;
                }
            }
            //含ln
            if(flag2==1){
                int j;
                for(j=0;j<251;j++){
                    x1[i][j] = expression2[i].calculate_function(1,j/12.50+0.002);
            //        qDebug()<<expression1[0].calculate_function(1)<<endl;
                    y1[i][j] = expression2[i].calculate_function(2,x1[i][j]);
                    //qDebug()<<'('<<x[i][j]<<','<<y[i][j]<<')'<<endl;
                }
            }
            //不含ln
            else{
                //int j;
                for(j=0;j<251;j++){
                    x1[i][j] = expression2[i].calculate_function(1,j/12.50-10);
            //        qDebug()<<expression1[0].calculate_function(1)<<endl;
                    y1[i][j] = expression2[i].calculate_function(2,x1[i][j]);
                    //qDebug()<<'('<<x[i][j]<<','<<y[i][j]<<')'<<endl;
                }
            }
        }
    }

    //设置数据等
    for(i=0;i<expression2.size();i++){

        QCPCurve *newCurve = new QCPCurve(ui->widget->xAxis,ui->widget->yAxis);
//       qDebug()<<"graph2 added"<<endl;
    //设置颜色
        QPen pen;
        if(expression2[i].read_line_color()==QString("red"))
            pen.setColor(QColor(Qt::red));
        else if(expression2[i].read_line_color()==QString("yellow"))
            pen.setColor(QColor(Qt::yellow));
        else if(expression2[i].read_line_color()==QString("blue"))
            pen.setColor(QColor(Qt::blue));
        else if(expression2[i].read_line_color()==QString("green"))
            pen.setColor(QColor(Qt::green));
        else if(expression2[i].read_line_color()==QString("black"))
            pen.setColor(QColor(Qt::black));

        //设置线型
        if(expression2[i].read_line_type()=="type1")
            pen.setStyle(Qt::SolidLine);
        else if(expression2[i].read_line_type()=="type2")
            pen.setStyle(Qt::DashLine);
        else if(expression2[i].read_line_type()=="type3")
            pen.setStyle(Qt::DotLine);
        else if(expression2[i].read_line_type()=="type4")
            pen.setStyle(Qt::DashDotLine);

        newCurve->setPen(pen);
        //ui->widget->graph(i+expression1.size())->setPen(pen);
        newCurve->setData(x1[i],y1[i]);
    }
}

DialogDraw::~DialogDraw()
{
    delete ui;
}

void DialogDraw::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        ui->widget->xAxis->grid()->setVisible(true);
        ui->widget->yAxis->grid()->setVisible(true);
    }
    else{
        ui->widget->xAxis->grid()->setVisible(false);
        ui->widget->yAxis->grid()->setVisible(false);
    }

    ui->widget->replot();

}





/*
void DialogDraw::mouseMoved(QMouseEvent *event){

    QVector<double> vx,vy;

    double x = ui->widget->xAxis->pixelToCoord(event->pos().x());

    double y = ui->widget->yAxis->pixelToCoord(event->pos().y());

    vx<<0<<x<<ui->widget->xAxis->range().maxRange;

    vy<<y<<y<<y;

    ui->widget->graph(1)->setData(vx,vy);

    ui->widget->graph(1)->setPen(QPen(Qt::red));

    vx.clear();

    vy.clear();

    vx<<x<<x<<x;

    vy<<0<<y<<ui->widget->yAxis->range().maxRange;

    ui->widget->graph(2)->setData(vx,vy);

    ui->widget->graph(2)->setPen(QPen(Qt::red));

    ui->widget->replot();

}
*/
/*
void DialogDraw::refresh_graph(void){
    //添加function1图线

//    QVector<double> x(251), y(10)(251);

    QVector<QVector<double>> y(5);
    for (int m = 0; m < y.size(); m++)
        y[m].resize(251);
    for(int m = 0; m < y.size(); m++)
    {
        for (int n = 0; n < y[0].size(); n++)
        {
            y[m][n] = (m+1)*(n+1);
        }
    }
    QVector<double> x(251);

    int i = 0;
    for(i=0;i<function1_count;i++){
        ui->widget->addGraph();
        //设置颜色
        ui->widget->graph(i)->setPen(QPen(QColor(Qt::red)));

        for(int j=0;j<251;++j){
            x[j] = j;
            y[i][j] = expression1[i].calculate_function(j);
        }
    }
    //设置数据
    for(i=0;i<function1_count;i++){
        ui->widget->graph(i)->setData(x,y[i]);
    }
}
*/
