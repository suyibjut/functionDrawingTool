#include "function1.h"
#include <QString>
#include <QDebug>

extern QString negative_number(QString input);
extern int operator_priority(char x);
extern int compare_priority(char a, char b);
extern double calculate(QString input);
extern QString double_to_string(double num);
extern QString function_convert(QString input);
extern QString shorten_function(QString str);

//function1::function1(QObject *parent)
 //   : QAbstractItemModel(parent)
function1::function1(void)
{
    expression = "";
    line_color = "";
    line_type = "";
}
/*
QVariant function1::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex function1::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex function1::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int function1::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int function1::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant function1::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
*/
//输入
void function1::get_expression(QString str,QString color, QString type){
    expression = str;
    line_color = color;
    line_type = type;
}
//读出expression
QString function1::read_expression(void){
    return expression;
}
QString function1::read_line_color(void){
    return line_color;
}
QString function1::read_line_type(void){
    return line_type;
}
//检查合法输入
bool function1::check_input(QString str){

    //检测特殊函数
        for(int i = 0;i<str.length();i++){
            if(str[i]=='s'){
                if(str[i+1]=='i'&&str[i+2]=='n'&&str[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str[i]=='c'){
                if(str[i+1]=='o'&&str[i+2]=='s'&&str[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str[i]=='t'){
                if(str[i+1]=='a'&&str[i+2]=='n'&&str[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str[i]=='a'){
                if(str[i+1]=='r'&&str[i+2]=='c'&&str[i+3]=='t'&&str[i+4]=='a'&&str[i+5]=='n'&&str[i+6]=='('){
                    i += 6;
                    continue;
                }
                else return false;
            }
            else if(str[i]=='e'){
                if(str[i+1]=='x'&&str[i+2]=='p'&&str[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str[i]=='l'){
                if(str[i+1]=='n'&&str[i+2]=='('){
                    i += 2;
                    continue;
                }
                else return false;
            }
        }


        //缩短
        QString shortened_str = shorten_function(str);
        if(shortened_str==""){
            return false;
            qDebug()<<"shorten error"<<endl;
        }

        //字符过滤
        for(int i=0;i<shortened_str.length();i++){
            if(shortened_str[i]=='X'||shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='l'||shortened_str[i]=='a'||shortened_str[i]=='e'||shortened_str[i]=='('||shortened_str[i]==')'||shortened_str[i]=='+'||shortened_str[i]=='-'||shortened_str[i]=='*'||shortened_str[i]=='/'||shortened_str[i]=='^'||shortened_str[i]=='.'||(shortened_str[i]>='0'&&shortened_str[i]<='9')){}
            else return false;
        }
//        qDebug()<<"shorten succeeded"<<endl;
//        qDebug()<<shortened_str<<endl;
        int count,i;
        //第一个字符只能是x或数字或(或s或c或t或a或l或e或-
        if(shortened_str[0]=='-'||shortened_str[0]=='X'||shortened_str[0]=='s'||shortened_str[0]=='c'||shortened_str[0]=='t'||shortened_str[0]=='a'||shortened_str[0]=='l'||shortened_str[0]=='e'||shortened_str[0]=='('||(shortened_str[0]>='0'&&shortened_str[0]<='9')){}
        else return false;
        if(shortened_str.length()>1&&shortened_str[0]=='X'){
            if((shortened_str[1]=='^'||shortened_str[1]=='+'||shortened_str[1]=='-'||shortened_str[1]=='*'||shortened_str[1]=='/')){}
            else return false;
        }

        //中间字符
        for(i=1;i<shortened_str.length()-1;i++){
            if(shortened_str[i]=='X'||shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='a'||shortened_str[i]=='l'||shortened_str[i]=='e'){
                //每个x s c t a l e前只能是数字或+-或^或(或/或*
                if(shortened_str[i-1]=='*'||shortened_str[i-1]=='/'||shortened_str[i-1]=='+'||shortened_str[i-1]=='-'||shortened_str[i-1]=='('||shortened_str[i-1]=='^'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
                else{
                    qDebug()<<"before xsctale"<<endl;
                    return false;
                }
                //每个x后只能是^或+-*/或)
                if(shortened_str[i]=='X'&&(shortened_str[i+1]=='^'||shortened_str[i+1]=='+'||shortened_str[i+1]=='-'||shortened_str[i+1]==')'||shortened_str[i+1]=='*'||shortened_str[i+1]=='/')){}
                //sctlae在shorten_function中已经检测过，确保后面是(
                else if(shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='l'||shortened_str[i]=='a'||shortened_str[i]=='e'){}
                else{
                    qDebug()<<"after x"<<endl;
                    return false;
                }
            }
            else if(shortened_str[i]=='+'||shortened_str[i]=='-'||shortened_str[i]=='*'||shortened_str[i]=='/'){
                //运算符号前只能是数字或x或)
                if(shortened_str[i-1]=='X'||shortened_str[i-1]==')'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
                else if(shortened_str[i]=='-'&&shortened_str[i-1]=='^'||shortened_str[i-1]=='('){}  //特殊 x^-2 x^(-2)
                else{
                    qDebug()<<"before sign"<<endl;
                    return false;
                }
                //运算符号后只能是数字或x或(或sctale
                if(shortened_str[i+1]=='X'||shortened_str[i+1]=='('||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')||shortened_str[i+1]=='s'||shortened_str[i+1]=='c'||shortened_str[i+1]=='t'||shortened_str[i+1]=='a'||shortened_str[i+1]=='l'||shortened_str[i+1]=='e'){}
                else{
                    qDebug()<<"after sign"<<endl;
                    return false;
                }
            }
            else if(shortened_str[i]=='('){
                //每个(前只能是^或+-*/或sctale或(
                if(shortened_str[i-1]=='('||shortened_str[i-1]=='^'||shortened_str[i-1]=='+'||shortened_str[i-1]=='-'||shortened_str[i-1]=='*'||shortened_str[i-1]=='/'||shortened_str[i-1]=='s'||shortened_str[i-1]=='c'||shortened_str[i-1]=='t'||shortened_str[i-1]=='a'||shortened_str[i-1]=='l'||shortened_str[i-1]=='e'){}
                else{
                    qDebug()<<"before ("<<endl;
                    return false;
                }
                //每个(后只能是数字或x或sctale或(或-
                if(shortened_str[i+1]=='-'||shortened_str[i+1]=='('||shortened_str[i+1]=='X'||shortened_str[i+1]=='s'||shortened_str[i+1]=='c'||shortened_str[i+1]=='t'||shortened_str[i+1]=='a'||shortened_str[i+1]=='l'||shortened_str[i+1]=='e'||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
                else{
                    qDebug()<<"after ("<<endl;
                    return false;
                }
            }
            else if(shortened_str[i]==')'){
                //每个)前只能是数字或x或)
                if(shortened_str[i-1]==')'||shortened_str[i-1]=='X'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
                else{
                    qDebug()<<"before )"<<endl;
                    return false;
                }
                //每个)后只能是^或+-*/或)
                if(shortened_str[i+1]=='^'||shortened_str[i+1]=='+'||shortened_str[i+1]=='-'||shortened_str[i+1]=='*'||shortened_str[i+1]=='/'||shortened_str[i+1]==')'){}
                else{
                    qDebug()<<"after )"<<endl;
                    return false;
                }
            }
            else if(shortened_str[i]=='^'){
                //每个^前只能是)或数字或x
                if(shortened_str[i-1]==')'||shortened_str[i-1]=='X'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
                else{
                    qDebug()<<"before ^"<<endl;
                    return false;
                }
                //每个^后只能是(或数字或x或sctlae
                if(shortened_str[i+1]=='('||shortened_str[i+1]=='X'||shortened_str[i+1]=='s'||shortened_str[i+1]=='c'||shortened_str[i+1]=='t'||shortened_str[i+1]=='a'||shortened_str[i+1]=='l'||shortened_str[i+1]=='e'||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
                else{
                    qDebug()<<"after ^"<<endl;
                    return false;
                }
            }
            else if(shortened_str[i]=='.'){
                //每个.前后只能是数字
                if(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9'&&shortened_str[i+1]>='0'&&shortened_str[i+1]<='9'){}
                else{
                    qDebug()<<"near ."<<endl;
                    return false;
                }
            }
        }

        //结尾字符只能是)或数字或x
        if(shortened_str[shortened_str.length()-1]==')'||shortened_str[shortened_str.length()-1]=='X'||(shortened_str[shortened_str.length()-1]>='0'&&shortened_str[shortened_str.length()-1]<='9')){}
        else return false;

        //括号闭合问题
        i = 0;
        count = 0;
        while(i<shortened_str.length()){
            if(shortened_str[i]=='(') count++;
            else if(shortened_str[i]==')') count--;

            if(count<0) return false;
            i++;
        }
        if(count!=0){
            qDebug()<<"buckets error"<<endl;
            return false;
        }

        return true;


}

//替换x为指定数字
QString function1::replace_x(QString str,double n){
    QString num;
    int i;
    //将double数转换为字符串
    num = double_to_string(n);
    //cout<<num;
    i = 0;
    while(i<str.length()){

        if(str[i]=='X'){

            QString str_left = str.mid(0,i);
//            qDebug()<<"str_left:"<<str_left<<endl;
            QString str_right = str.mid(i+1);
//            qDebug()<<"str_right:"<<str_right<<endl;
            if(i>=1&&str[i-1]>='0'&&str[i-1]<='9') str = str_left + "*(" + num + ')' + str_right;
            else str = str_left + '(' + num + ')' + str_right;
//            qDebug()<<"str:"<<str<<endl;
            i = 0;
        }
        else i++;
    }
    return str;
}
//计算结果
double function1::calculate_function(double x){
    QString input = expression;
//    qDebug()<<"input= "<<input<<endl;
    QString out1 = function1::replace_x(input,x);
//    qDebug()<<"out1= "<<out1<<endl;
    QString out2 = shorten_function(out1);    
//    if(out2==""){
//        qDebug()<QString("error")<<endl;
//        return 0;
//    }
    out2 = negative_number(out2);
//    qDebug()<<"out2= "<<out2;
    QString out3 = function_convert(out2);
//    qDebug()<<"out3= "<<out3;
    QString input2 = '(' + out3 + ")\0";
    QString input3 = negative_number(input2);
//    qDebug()<<"input3="<<input3<<endl;
    double result = calculate(input3);
//    qDebug()<<x<<" ->result= ";
//    qDebug()<<"result="<<result<<endl;

    return result;
}
