#include "function2.h"
#include <QString>
#include <QDebug>

extern QString negative_number(QString input);
extern int operator_priority(char x);
extern int compare_priority(char a, char b);
extern double calculate(QString input);
extern QString double_to_string(double num);
extern QString function_convert(QString input);
extern QString shorten_function(QString str);

//function2::function2(QObject *parent)
    //: QAbstractItemModel(parent)
function2::function2(void)
{
    expression1 = "";
    expression2 = "";
    line_color = "";
    line_type = "";
}
/*
QVariant function2::headerData(int section, Qt::Orientation orientation, int role) const
{
    // FIXME: Implement me!
}

QModelIndex function2::index(int row, int column, const QModelIndex &parent) const
{
    // FIXME: Implement me!
}

QModelIndex function2::parent(const QModelIndex &index) const
{
    // FIXME: Implement me!
}

int function2::rowCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

int function2::columnCount(const QModelIndex &parent) const
{
    if (!parent.isValid())
        return 0;

    // FIXME: Implement me!
}

QVariant function2::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    // FIXME: Implement me!
    return QVariant();
}
*/
//输入
void function2::get_expression(QString str1, QString str2, QString color, QString type){
    expression1 = str1;
    expression2 = str2;
    line_color = color;
    line_type = type;
}
//读出expression1
QString function2::read_expression1(void){
    return expression1;
}
//读出expression2
QString function2::read_expression2(void){
    return expression2;
}
//读出line_color
QString function2::read_line_color(void){
    return line_color;
}
//读出line_type
QString function2::read_line_type(void){
    return line_type;
}
//检查输入合法性
bool function2::check_input(QString str1, QString str2){
    //处理t和tan
    for(int i=0;i<str1.length();i++){
        if(str1[i]=='X'){
            return false;
        }
        else if(str1[i]=='t'){
            if(str1[i+1]=='a'&&str1[i+2]=='n'&&str1[i+3]=='('){}
            else str1[i] = 'X';
        }
    }

    //检测特殊函数
        for(int i = 0;i<str1.length();i++){
            if(str1[i]=='s'){
                if(str1[i+1]=='i'&&str1[i+2]=='n'&&str1[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str1[i]=='c'){
                if(str1[i+1]=='o'&&str1[i+2]=='s'&&str1[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str1[i]=='t'){
                if(str1[i+1]=='a'&&str1[i+2]=='n'&&str1[i+3]=='('){
                    i += 3;
                    continue;
                }
                //else if(str1[i+1]=='+'||str1[i+1]=='-'||str1[i+1]=='*'||str1[i+1]=='/'||str1[i+1]=='^'||str1[i+1]==')'){}
                else return false;
            }
            else if(str1[i]=='a'){
                if(str1[i+1]=='r'&&str1[i+2]=='c'&&str1[i+3]=='t'&&str1[i+4]=='a'&&str1[i+5]=='n'&&str1[i+6]=='('){
                    i += 6;
                    continue;
                }
                else return false;
            }
            else if(str1[i]=='e'){
                if(str1[i+1]=='x'&&str1[i+2]=='p'&&str1[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str1[i]=='l'){
                if(str1[i+1]=='n'&&str1[i+2]=='('){
                    i += 2;
                    continue;
                }
                else return false;
            }
        }

        //缩短
        QString shortened_str = shorten_function(str1);
        if(shortened_str=="") return false;
        //字符过滤
        for(int i=0;i<shortened_str.length();i++){
            if(shortened_str[i]=='.'||shortened_str[i]=='X'||shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='l'||shortened_str[i]=='a'||shortened_str[i]=='e'||shortened_str[i]=='('||shortened_str[i]==')'||shortened_str[i]=='+'||shortened_str[i]=='-'||shortened_str[i]=='*'||shortened_str[i]=='/'||shortened_str[i]=='^'||(shortened_str[i]>='0'&&shortened_str[i]<='9')){}
            else return false;
        }
//        qDebug()<<"shorten succeeded "<<shortened_str<<endl;

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
                    qDebug()<<"before x"<<endl;
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
                if(shortened_str[i+1]=='s'||shortened_str[i+1]=='c'||shortened_str[i+1]=='t'||shortened_str[i+1]=='X'||shortened_str[i+1]=='a'||shortened_str[i+1]=='l'||shortened_str[i+1]=='e'||shortened_str[i+1]=='('||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
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
                //每个)前只能是数字或x
                if(shortened_str[i-1]=='X'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
                else{
                    qDebug()<<"before )"<<endl;
                    return false;
                }
                //每个)后只能是^或+-*/或)
                if(shortened_str[i+1]==')'||shortened_str[i+1]=='^'||shortened_str[i+1]=='+'||shortened_str[i+1]=='-'||shortened_str[i+1]=='*'||shortened_str[i+1]=='/'){}
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
                //每个^后只能是(或数字或x或-或sctlae
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






        //str2
        //处理t和tan
        for(int i=0;i<str2.length();i++){
            if(str2[i]=='X'){
                return false;
            }
            if(str2[i]=='t'){
                if(str2[i+1]=='a'&&str2[i+2]=='n'&&str2[i+3]=='('){}
                else str2[i] = 'X';
            }
        }
//检测特殊函数
        for(int i = 0;i<str2.length();i++){
            if(str2[i]=='s'){
                if(str2[i+1]=='i'&&str2[i+2]=='n'&&str2[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str2[i]=='c'){
                if(str2[i+1]=='o'&&str2[i+2]=='s'&&str2[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str2[i]=='t'){
                if(str2[i+1]=='a'&&str2[i+2]=='n'&&str2[i+3]=='('){
                    i += 3;
                    continue;
                }
                //else if(str1[i+1]=='+'||str1[i+1]=='-'||str1[i+1]=='*'||str1[i+1]=='/'||str1[i+1]=='^'||str1[i+1]==')'){}
                else return false;
            }
            else if(str2[i]=='a'){
                if(str2[i+1]=='r'&&str2[i+2]=='c'&&str2[i+3]=='t'&&str2[i+4]=='a'&&str2[i+5]=='n'&&str2[i+6]=='('){
                    i += 6;
                    continue;
                }
                else return false;
            }
            else if(str2[i]=='e'){
                if(str2[i+1]=='x'&&str2[i+2]=='p'&&str2[i+3]=='('){
                    i += 3;
                    continue;
                }
                else return false;
            }
            else if(str2[i]=='l'){
                if(str2[i+1]=='n'&&str2[i+2]=='('){
                    i += 2;
                    continue;
                }
                else return false;
            }
        }

            //缩短
            shortened_str = shorten_function(str2);
            if(shortened_str=="") return false;
            //字符过滤
            for(int i=0;i<shortened_str.length();i++){
                if(shortened_str[i]=='.'||shortened_str[i]=='X'||shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='l'||shortened_str[i]=='a'||shortened_str[i]=='e'||shortened_str[i]=='('||shortened_str[i]==')'||shortened_str[i]=='+'||shortened_str[i]=='-'||shortened_str[i]=='*'||shortened_str[i]=='/'||shortened_str[i]=='^'||(shortened_str[i]>='0'&&shortened_str[i]<='9')){}
                else return false;
            }
//            qDebug()<<"shorten succeeded "<<shortened_str<<endl;

            //第一个字符只能是x或数字或(或s或c或t或a或l或e
            if(shortened_str[0]=='X'||shortened_str[0]=='s'||shortened_str[0]=='c'||shortened_str[0]=='t'||shortened_str[0]=='a'||shortened_str[0]=='l'||shortened_str[0]=='e'||shortened_str[0]=='('||(shortened_str[0]>='0'&&shortened_str[0]<='9')){}
            else return false;
            if(shortened_str.length()>1&&shortened_str[0]=='X'){
                if((shortened_str[1]=='^'||shortened_str[1]=='+'||shortened_str[1]=='-'||shortened_str[1]=='*'||shortened_str[1]=='/')){}
                else return false;
            }

            //中间字符
            for(i=1;i<shortened_str.length()-1;i++){
                if(shortened_str[i]=='X'||shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='a'||shortened_str[i]=='l'||shortened_str[i]=='e'){
                    //每个x s c t a l e前只能是数字或+-或^或(或*
                    if(shortened_str[i-1]=='*'||shortened_str[i-1]=='+'||shortened_str[i-1]=='-'||shortened_str[i-1]=='('||shortened_str[i-1]=='^'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
                    else{
                        qDebug()<<"before x"<<endl;
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
                    //运算符号后只能是数字或x或(或cstlae
                    if(shortened_str[i+1]=='X'||shortened_str[i+1]=='s'||shortened_str[i+1]=='c'||shortened_str[i+1]=='t'||shortened_str[i+1]=='a'||shortened_str[i+1]=='l'||shortened_str[i+1]=='e'||shortened_str[i+1]=='('||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
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
                    //每个(后只能是数字或x或sctale或-
                    if(shortened_str[i+1]=='-'||shortened_str[i+1]=='('||shortened_str[i+1]=='X'||shortened_str[i-1]=='s'||shortened_str[i-1]=='c'||shortened_str[i-1]=='t'||shortened_str[i-1]=='a'||shortened_str[i-1]=='l'||shortened_str[i-1]=='e'||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
                    else{
                        qDebug()<<"after ("<<endl;
                        return false;
                    }
                }
                else if(shortened_str[i]==')'){
                    //每个)前只能是数字或x
                    if(shortened_str[i-1]=='X'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
                    else{
                        qDebug()<<"before )"<<endl;
                        return false;
                    }
                    //每个)后只能是^或+-*/
                    if(shortened_str[i+1]=='^'||shortened_str[i+1]=='+'||shortened_str[i+1]=='-'||shortened_str[i+1]=='*'||shortened_str[i+1]=='/'){}
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

//替换t为指定数字
QString function2::replace_t(QString str, double n){
    for(int i=0;i<str.length();i++){
        if(str[i]=='t'){
            if(str[i+1]=='a'&&str[i+2]=='n'&&str[i+3]=='('){}
            else str[i] = 'X';
        }
    }
    QString num;
    int i;
    //将double数转换为字符串
    num = double_to_string(n);
    //cout<<num;
    i = 0;
    while(i<str.length()){

        if(str[i]=='X'){

            QString str_left = str.mid(0,i);
            QString str_right = str.mid(i+1);
            if(i>=1&&str[i-1]>='0'&&str[i-1]<='9') str = str_left + "*(" + num + ')' + str_right;
            else str = str_left + '(' + num + ')' + str_right;
            i = 0;
        }
        else i++;
    }
    return str;
}

//最终计算
double function2::calculate_function(int n, double x){
    QString out1;
    if(n==1) out1 = function2::replace_t(expression1, x);
    else out1 = function2::replace_t(expression2, x);
//    qDebug()<<"out1: "<<out1<<endl;
//    QString out1 = function2::replace_t(input, x);
    QString out2 = shorten_function(out1);
//    qDebug()<<"out2: "<<out2<<endl;
//    if(out2==""){
//        qDebug()<QString("error")<<endl;
//        return 0;
//    }
    QString out3 = function_convert(out2);
//    qDebug()<<"out3: "<<out3<<endl;
    QString input2 = '(' + out3 + ")\0";
//    qDebug()<<"input2: "<<input2<<endl;
    QString input3 = negative_number(input2);
//    qDebug()<<input3<<endl;
    double result = calculate(input3);
//    qDebug()<<result<<endl;

    return result;

}

