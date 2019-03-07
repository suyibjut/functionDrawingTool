using namespace std;
#include <iostream>
#include <cstring>
#include <QStack>
#include <cmath>
#include <QString>
#include <QTextStream>
//#include <QDebug>

//解决负号问题  (-1  解决2(1
QString negative_number(QString input){
    int i = 0;
    while(i<input.length()){
        if(input[i]=='('&&input[i+1]=='-'){
            QString input_left = input.mid(0,i+1);
            QString input_right = input.mid(i+1);
//			cout<<input_left<<endl;
//			cout<<input_right<<endl;
            input = input_left + '0' +input_right;
//			cout<<input;
            i = 0;
            continue;
        }
        if(i>0&&input[i]=='('&&input[i-1]>='0'&&input[i-1]<='9'){
            QString input_left = input.mid(0,i);
            QString input_right = input.mid(i);
            input = input_left + '*' + input_right;
            i = 0;
            continue;
        }
        i++;
    }
//    qDebug()<<"nega dealt with:"<<input;
    return input;
}

int operator_priority(QChar x){

    if(x=='+'||x=='-') return 1;
    else if(x=='*'||x=='/') return 2;
    else if(x=='^') return 3;
    else if(x=='(') return 0;
    return -1;
}

int compare_priority(QChar a, QChar b){
    if(operator_priority(a) <= operator_priority(b)) return 1;
    else return 0;
}

double calculate(QString input){

    QStack<QChar> ope;
    QStack<double> number;
    QChar tmp[20];
    double tmp_num;
    int i,j;

    input = negative_number(input);
    for(i=0;i<input.length();i++){

        //数字
        if(input[i]>='0'&&input[i]<='9'){
            j = 0;
            while((input[i+j]>='0'&&input[i+j]<='9')||input[i+j]=='.'){
                tmp[j] = input[i+j];
                j++;
            }
            tmp[j] = 0;
            tmp_num = QString(tmp).toDouble();//sscanf(tmp, "%lf", &tmp_num);
            number.push(tmp_num);
            i = i + j -1;
        }
        //符号
        else{
            if(input[i]=='('){
                ope.push(input[i]);
                continue;
            }
            bool flag = false;
            while(!ope.empty()&&compare_priority(input[i], ope.top())){
                QChar ch = ope.top();
                if(input[i]==')'){
                    if(flag) break;
                    if(ch=='(') flag = true;
                }
                ope.pop();
                if(ch == '*'){
                    double x = number.top();
                    number.pop();
                    double y = number.top();
                    number.pop();
                    number.push(x*y);
                }
                if (ch == '/'){
                    double x = number.top();
                    number.pop();
                    double y = number.top();
                    number.pop();
                    number.push(y / x);
                }
                if (ch == '+'){
                    double x = number.top();
                    number.pop();
                    double y = number.top();
                    number.pop();
                    number.push(x + y);
                }
                if (ch == '-'){
                    double x = number.top();
                    number.pop();
                    double y = number.top();
                    number.pop();
                    number.push(y - x);
                }
                if (ch == '^'){
                    double exp = number.top();
                    number.pop();
                    double base = number.top();
                    number.pop();
                    if(exp<0){
                        number.push(1/pow(base,-exp));
                    }
                    else{
                        number.push(pow(base, exp));
                    }

                }
            }
            if(input[i] != ')') ope.push(input[i]);
        }

    }
    double result = number.top();
    number.pop();
    return result;
}

//将double数转换为字符串
QString double_to_string(double num){
    //QChar str[256];
    //sprintf(str, "%lf", num);
    //QString result = QString(str);
    QString result = QString::number(num,'f',4);
    return result;
}


//sin -> s
//cos -> c
//tan -> t
//ln -> l
//arctan -> a
//exp -> e
QString shorten_function(QString str){

    int i;//,length;
    QString str_left,str_right;
    //length = str.length();
    i = 0;
    while(i<str.length()){
        //sin()
        if(str[i] == 's'){
            if(str[i+1]=='i'&&str[i+2]=='n'&&str[i+3]=='('){
                str_left = str.mid(0,i);
                str_right = str.mid(i+3);
                str = str_left + 's' +str_right;
                i = 0;
                continue;
            }
        }
        //cos()
        else if(str[i] == 'c'){
            if(str[i+1]=='o'&&str[i+2]=='s'&&str[i+3]=='('){
                str_left = str.mid(0,i);
                str_right = str.mid(i+3);
                str = str_left + 'c' +str_right;
                i = 0;
                continue;
            }
        }
        //tan()
        else if(str[i] == 't'){
            if(str[i+1]=='a'&&str[i+2]=='n'&&str[i+3]=='('){
                str_left = str.mid(0,i);
                str_right = str.mid(i+3);
                str = str_left + 't' +str_right;
                i = 0;
                continue;
            }
        }
        //ln()
        else if(str[i] == 'l'){
            if(str[i+1]=='n'&&str[i+2]=='('){
                str_left = str.mid(0,i);
                str_right = str.mid(i+2);
                str = str_left + 'l' +str_right;
                i = 0;
                continue;
            }
        }
        //arctan()
        else if(str[i] == 'a'){
            if(str[i+1]=='r'&&str[i+2]=='c'&&str[i+3]=='t'&&str[i+4]=='a'&&str[i+5]=='n'&&str[i+6]=='('){
                str_left = str.mid(0,i);
                str_right = str.mid(i+6);
                str = str_left + 'a' +str_right;
                i = 0;
                continue;
            }
        }
        //exp()
        else if(str[i] == 'e'){
            if(str[i+1]=='x'&&str[i+2]=='p'&&str[i+3]=='('){
                str_left = str.mid(0,i);
                str_right = str.mid(i+3);
                str = str_left + 'e' +str_right;
                i = 0;
                continue;
            }
        }
        i++;
    }
    return str;
}

//s(1+s(x+(1+1)))
//s(s())
//sin() cos() tan() arctan() ln() exp()
QString function_convert(QString input){

    double tmp_result;
    QString tmp_str;
//	input = shorten_function(input);
    int i = input.length() - 4;
    QString tmp;
    QChar tmp1[50];
    while(i >= 0){
        //sin()
        if(input[i]=='s'){
            int j = 2;
            int count=1;
//			tmp.append(a,1);
            tmp1[0] = '(';

            while(count!=0){
                if(input[i+j]=='(') count++;
                else if(input[i+j]==')') count--;

//				tmp.append(input,i+j,1);
                tmp1[j-1] = input[i+j];
                j++;
            }
            tmp1[j-1] = '\0';
//			cout<<tmp1<<endl;

            tmp = QString(tmp1);

            tmp_result = calculate(tmp);
            tmp_result = sin(tmp_result);
            tmp_str = double_to_string(tmp_result);

            QString input_left = input.mid(0,i);
            QString input_right = input.mid(i+j);

//			cout<<input_left<<endl;
//			cout<<input_right<<endl;
//			cout<<tmp_str<<endl;

            input = input_left + '(' + tmp_str + ')' + input_right;
            i = input.length()-4;
            continue;
        }
        //cos()
        else if(input[i]=='c'){
            int j = 2;
            int count=1;
//			tmp.append(a,1);
            tmp1[0] = '(';

            while(count!=0){
                if(input[i+j]=='(') count++;
                else if(input[i+j]==')') count--;

//				tmp.append(input,i+j,1);
                tmp1[j-1] = input[i+j];
                j++;
            }
            tmp1[j-1] = '\0';
//			cout<<tmp1<<endl;

            tmp = QString(tmp1);

            tmp_result = calculate(tmp);
            tmp_result = cos(tmp_result);
            tmp_str = double_to_string(tmp_result);

            QString input_left = input.mid(0,i);
            QString input_right = input.mid(i+j);

//			cout<<input_left<<endl;
//			cout<<input_right<<endl;
//			cout<<tmp_str<<endl;

            input = input_left + '(' + tmp_str + ')' + input_right;
            i = input.length()-4;
            continue;
        }
        //tan()
        else if(input[i]=='t'){
            int j = 2;
            int count=1;
//			tmp.append(a,1);
            tmp1[0] = '(';

            while(count!=0){
                if(input[i+j]=='(') count++;
                else if(input[i+j]==')') count--;

//				tmp.append(input,i+j,1);
                tmp1[j-1] = input[i+j];
                j++;
            }
            tmp1[j-1] = '\0';
//			cout<<tmp1<<endl;

            tmp = QString(tmp1);

            tmp_result = calculate(tmp);
            tmp_result = tan(tmp_result);
            tmp_str = double_to_string(tmp_result);

            QString input_left = input.mid(0,i);
            QString input_right = input.mid(i+j);

//			cout<<input_left<<endl;
//			cout<<input_right<<endl;
//			cout<<tmp_str<<endl;

            input = input_left + '(' + tmp_str + ')' + input_right;
            i = input.length()-4;
            continue;
        }
        //arctan()
        if(input[i]=='a'){
            int j = 2;
            int count=1;
//			tmp.append(a,1);
            tmp1[0] = '(';

            while(count!=0){
                if(input[i+j]=='(') count++;
                else if(input[i+j]==')') count--;

//				tmp.append(input,i+j,1);
                tmp1[j-1] = input[i+j];
                j++;
            }
            tmp1[j-1] = '\0';
//			cout<<tmp1<<endl;

            tmp = QString(tmp1);

            tmp_result = calculate(tmp);
            tmp_result = atan(tmp_result);
            tmp_str = double_to_string(tmp_result);

            QString input_left = input.mid(0,i);
            QString input_right = input.mid(i+j);

//			cout<<input_left<<endl;
//			cout<<input_right<<endl;
//			cout<<tmp_str<<endl;

            input = input_left + '(' + tmp_str + ')' + input_right;
            i = input.length()-4;
            continue;
        }
        //exp()
        else if(input[i]=='e'){
            int j = 2;
            int count=1;
//			tmp.append(a,1);
            tmp1[0] = '(';

            while(count!=0){
                if(input[i+j]=='(') count++;
                else if(input[i+j]==')') count--;

//				tmp.append(input,i+j,1);
                tmp1[j-1] = input[i+j];
                j++;
            }
            tmp1[j-1] = '\0';
            //cout<<tmp1<<endl;

            tmp = QString(tmp1);

            tmp_result = calculate(tmp);
            tmp_result = exp(tmp_result);
            tmp_str = double_to_string(tmp_result);

            QString input_left = input.mid(0,i);
            QString input_right = input.mid(i+j);

//			cout<<input_left<<endl;
//			cout<<input_right<<endl;
//			cout<<tmp_str<<endl;

            input = input_left + '(' + tmp_str + ')' + input_right;
            i = input.length()-4;
            continue;
        }
        //ln()
        else if(input[i]=='l'){
            int j = 2;
            int count=1;
//			tmp.append(a,1);
            tmp1[0] = '(';

            while(count!=0){
                if(input[i+j]=='(') count++;
                else if(input[i+j]==')') count--;

//				tmp.append(input,i+j,1);
                tmp1[j-1] = input[i+j];
                j++;
            }
            tmp1[j-1] = '\0';
//			cout<<tmp1<<endl;

            tmp = QString(tmp1);

            tmp_result = calculate(tmp);
            if(tmp_result>0)
                tmp_result = log(tmp_result);
            else
                tmp_result = +100.00;
            tmp_str = double_to_string(tmp_result);

            QString input_left = input.mid(0,i);
            QString input_right = input.mid(i+j);

//			cout<<input_left<<endl;
//			cout<<input_right<<endl;
//			cout<<tmp_str<<endl;

            input = input_left + '(' + tmp_str + ')' + input_right;
            i = input.length()-4;
            continue;
        }
        else{
            i--;
        }

    }
    return input;
}
/*
//检查输入合法性
bool check(QString str){
    //检测特殊函数
    for(int i = 0;i<str.length();i++){
        if(str[i]=='s'){
            if(str[i+1]=='i'&&str[i+2]=='n'&&str[i+3]=='('){}
            else return false;
        }
        else if(str[i]=='c'){
            if(str[i+1]=='o'&&str[i+2]=='s'&&str[i+3]=='('){}
            else return false;
        }
        else if(str[i]=='t'){
            if(str[i+1]=='a'&&str[i+2]=='n'&&str[i+3]=='('){}
            else return false;
        }
        else if(str[i]=='a'){
            if(str[i+1]=='r'&&str[i+2]=='c'&&str[i+3]=='t'&&str[i+4]=='a'&&str[i+5]=='n'&&str[i+6]=='('){}
            else return false;
        }
        else if(str[i]=='e'){
            if(str[i+1]=='x'&&str[i+2]=='p'&&str[i+3]=='('){}
            else return false;
        }
        else if(str[i]=='l'){
            if(str[i+1]=='n'&&str[i+2]=='('){}
            else return false;
        }
    }

    //缩短
    QString shortened_str = shorten_function(str);
    if(shortened_str=="") return false;

    cout<<"shorten succeeded"<<endl;

    int count,i;
    //第一个字符只能是x或数字或(或s或c或t或a或l或e
    if(shortened_str[0]=='X'||shortened_str[0]=='s'||shortened_str[0]=='c'||shortened_str[0]=='t'||shortened_str[0]=='a'||shortened_str[0]=='l'||shortened_str[0]=='e'||shortened_str[0]=='('||(shortened_str[0]>='0'&&shortened_str[0]<='9')){}
    else return false;

    //中间字符
    for(i=1;i<shortened_str.length()-1;i++){
        if(shortened_str[i]=='X'||shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='a'||shortened_str[i]=='l'||shortened_str[i]=='e'){
            //每个x s c t a l e前只能是数字或+-或^或(
            if(shortened_str[i-1]=='+'||shortened_str[i-1]=='-'||shortened_str[i-1]=='('||shortened_str[i-1]=='^'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
            else{
                cout<<"before x"<<endl;
                return false;
            }
            //每个x后只能是^或+-/*或)
            if(shortened_str[i]=='X'&&(shortened_str[i+1]=='^'||shortened_str[i+1]=='+'||shortened_str[i+1]=='-'||shortened_str[i+1]==')'||shortened_str[i+1]=='*'||shortened_str[i+1]=='/')){}
            //sctlae在shorten_function中已经检测过，确保后面是(
            else if(shortened_str[i]=='s'||shortened_str[i]=='c'||shortened_str[i]=='t'||shortened_str[i]=='l'||shortened_str[i]=='a'||shortened_str[i]=='e'){}
            else{
                cout<<"after x"<<endl;
                return false;
            }
        }
        else if(shortened_str[i]=='+'||shortened_str[i]=='-'||shortened_str[i]=='*'||shortened_str[i]=='/'){
            //运算符号前只能是数字或x或)
            if(shortened_str[i-1]=='X'||shortened_str[i-1]==')'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
            else if(shortened_str[i]=='-'&&shortened_str[i-1]=='^'){}  //特殊 x^-2
            else{
                cout<<"before sign"<<endl;
                return false;
            }
            //运算符号后只能是数字或x或(
            if(shortened_str[i+1]=='X'||shortened_str[i+1]=='('||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
            else{
                cout<<"after sign"<<endl;
                return false;
            }
        }
        else if(shortened_str[i]=='('){
            //每个(前只能是^或+-/*或sctale
            if(shortened_str[i-1]=='^'||shortened_str[i-1]=='+'||shortened_str[i-1]=='-'||shortened_str[i-1]=='*'||shortened_str[i-1]=='/'||shortened_str[i-1]=='s'||shortened_str[i-1]=='c'||shortened_str[i-1]=='t'||shortened_str[i-1]=='a'||shortened_str[i-1]=='l'||shortened_str[i-1]=='e'){}
            else{
                cout<<"before ("<<endl;
                return false;
            }
            //每个(后只能是数字或x或sctale
            if(shortened_str[i+1]=='X'||shortened_str[i-1]=='s'||shortened_str[i-1]=='c'||shortened_str[i-1]=='t'||shortened_str[i-1]=='a'||shortened_str[i-1]=='l'||shortened_str[i-1]=='e'||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
            else{
                cout<<"after ("<<endl;
                return false;
            }
        }
        else if(shortened_str[i]==')'){
            //每个)前只能是数字或x
            if(shortened_str[i-1]=='X'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
            else{
                cout<<"before )"<<endl;
                return false;
            }
            //每个)后只能是^或+-/*
            if(shortened_str[i+1]=='^'||shortened_str[i+1]=='+'||shortened_str[i+1]=='-'||shortened_str[i+1]=='*'||shortened_str[i+1]=='/'){}
            else{
                cout<<"after )"<<endl;
                return false;
            }
        }
        else if(shortened_str[i]=='^'){
            //每个^前只能是)或数字或x
            if(shortened_str[i-1]==')'||shortened_str[i-1]=='X'||(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9')){}
            else{
                cout<<"before ^"<<endl;
                return false;
            }
            //每个^后只能是(或数字或x或-或sctlae
            if(shortened_str[i+1]=='('||shortened_str[i+1]=='X'||shortened_str[i+1]=='s'||shortened_str[i+1]=='c'||shortened_str[i+1]=='t'||shortened_str[i+1]=='a'||shortened_str[i+1]=='l'||shortened_str[i+1]=='e'||shortened_str[i+1]=='-'||(shortened_str[i+1]>='0'&&shortened_str[i+1]<='9')){}
            else{
                cout<<"after ^"<<endl;
                return false;
            }
        }
        else if(shortened_str[i]=='.'){
            //每个.前后只能是数字
            if(shortened_str[i-1]>='0'&&shortened_str[i-1]<='9'&&shortened_str[i+1]>='0'&&shortened_str[i+1]<='9'){}
            else{
                cout<<"near ."<<endl;
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
        cout<<"buckets error"<<endl;
        return false;
    }

    return true;
}
*/
/*
QString replace_x(QString str, double n){
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
            str = str_left + '(' + num + ')' + str_right;
            i = 0;
        }
        else i++;
    }
    return str;
}


//最终计算
double calculate_function(QString input, double x){

    QString out1 = replace_x(input,x);
    QString out2 = shorten_function(out1);
    if(out2==""){
        cout<<"error";
        return 0;
    }
    QString out3 = function_convert(out2);
    QString input2 = '(' + out3 + ")\0";
    qDebug()<<input2<<endl;
    qDebug()<<calculate(input2)<<endl;

    return 0;

}
*/
/*
int main(){

    string input;

//	string in;
//	cin>>input;
//	in = '(' + input + ")\0";
//	cout<<in<<endl;
//	cout<<calculate(in);


//	double x;
//	cin>>x;
//	cout<<double_to_string(x);

//	cin>>input;
//	negative_number(input);

    cin>>input;
    string out1 = replace_x(input,2);
    cout<<out1<<endl;
    string out2 = function_convert(shorten_function(out1));
    string input2 = '(' + out2 + ")\0";
    cout<<input2<<endl;
    cout<<calculate(input2)<<endl;

    return 0;
}
*/


