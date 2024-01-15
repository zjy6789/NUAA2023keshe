#include<iostream>
#include<stdlib.h>
#include<vector>
#include<iomanip>

using namespace std;


void show(string s,int i,vector<double> sd,vector<char> so)
{
    cout<<"���У�";
    for(int j= i;j<s.size();j++)
    {
        cout<<s[j];
    }
    cout<<"      "<<"��������";
    for(auto j:sd)
    {
        cout<<j<<" ";
    }
    cout<<"      "<<"��������";
    for(auto j:so)
    {
        cout<<j<<" ";
    }
    cout<<endl;
}

//��ջ���Ĳ������Ͳ��������м���
void compute(vector<char>&so,vector<double>&sd)
{
    double a,b,c;
    char d;
    //������ջ����һ��������
    //��������������������
    d=so.back();
    so.pop_back();
    a=sd.back();
    sd.pop_back();
    b=sd.back();
    sd.pop_back();
    //����
    switch (d)
    {
    case '*':c=b*a;break;
    case '/':c=b/a;break;
    case '+':c=b+a;break;
    case '-':c=b-a;break;
    default:cout<<"���ʽ����"<<endl;break;
    }
    sd.push_back(c);
}

//�����������ʽ
double ComputeInfix(string s)
{
    vector<double> sd;
    vector<char> so;
    int i=0;
    //�����ʽ�е������ַ���ջ
    while(i!=s.size())
    {
        //���ַ��ǲ�����
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
        //���������Ż������ջΪ��
        if(s[i]=='('||so.empty())
        {
            so.push_back(s[i++]);
            show(s,i,sd,so);
            continue;
        }
        //������
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
        //�˳���
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
        //�Ӽ���
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
    //��ʣ�������ջȫ������
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
    cout<<"������ʽ:";
    cin>>s;
    double result = ComputeInfix(s);
    cout<<"�����"<<result<<endl;
    system("pause");
    return 0;
}