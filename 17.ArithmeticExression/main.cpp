#include<iostream>
#include<stdlib.h>
#include<vector>
#include<iomanip>

using namespace std;


void show(string s,int i,vector<double> sd,vector<char> so)
{
    cout<<"序列：";
    for(int j= i;j<s.size();j++)
    {
        cout<<s[j];
    }
    cout<<"      "<<"操作数：";
    for(auto j:sd)
    {
        cout<<j<<" ";
    }
    cout<<"      "<<"操作符：";
    for(auto j:so)
    {
        cout<<j<<" ";
    }
    cout<<endl;
}

//对栈顶的操作符和操作数进行计算
void compute(vector<char>&so,vector<double>&sd)
{
    double a,b,c;
    char d;
    //操作符栈弹出一个操作符
    //运算数弹出两个运算数
    d=so.back();
    so.pop_back();
    a=sd.back();
    sd.pop_back();
    b=sd.back();
    sd.pop_back();
    //计算
    switch (d)
    {
    case '*':c=b*a;break;
    case '/':c=b/a;break;
    case '+':c=b+a;break;
    case '-':c=b-a;break;
    default:cout<<"表达式有误！"<<endl;break;
    }
    sd.push_back(c);
}

//计算算术表达式
double ComputeInfix(string s)
{
    vector<double> sd;
    vector<char> so;
    int i=0;
    //将表达式中的所有字符入栈
    while(i!=s.size())
    {
        //若字符是操作数
        if('0'<=s[i] && s[i]<='9')
        {
            if(i!=0&&s[i-1]>='0'&&s[i-1]<='9')
            {
                double t=sd.back();
                sd.pop_back();
                t=10*t+(double)(s[i]-'0');
                sd.push_back(t);
                i++;
            }
            else sd.push_back((double)(s[i++]-'0'));
            show(s,i,sd,so);
            continue;
        }
        //若是左括号或操作符栈为空
        if(s[i]=='('||so.empty())
        {
            so.push_back(s[i++]);
            show(s,i,sd,so);
            continue;
        }
        //右括号
        if(s[i]==')')
        {
            char t;
            while (!so.empty()&&so.back()!='(')
            {
                compute(so,sd);
                show(s,i,sd,so);
            }
            so.pop_back();
            show(s,i,sd,so);
            i++;
            continue;
        }
        //乘除号
        if(s[i]=='*'||s[i]=='/')
        {
            if(!so.empty()&&(so.back()=='*'||so.back()=='/'))
            {
                compute(so,sd);
                show(s,i,sd,so);
            }
            so.push_back(s[i++]);
            show(s,i,sd,so);
            continue;
        }
        //加减号
        if(s[i]=='+'||s[i]=='-')
        {
            while (!so.empty()&&so.back()!='(')
            {
                compute(so,sd);
                show(s,i,sd,so);
            }
            so.push_back(s[i++]);
            show(s,i,sd,so);
            continue;
        }
    }
    //将剩余操作符栈全部计算
    while (!so.empty())
    {
        compute(so,sd);
        show(s,i,sd,so);
    }
    return sd.back();
}


int main()
{
    string s;
    cout<<"输入表达式:";
    cin>>s;
    double result = ComputeInfix(s);
    cout<<"结果："<<result<<endl;
    system("pause");
    return 0;
}