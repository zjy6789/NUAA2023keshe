#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include"HuffmanCode.h"

using namespace std;

int main()
{
    HuffmanCode code;
    ifstream infile("source.txt");
    code.CreateHufCode(infile);
    infile.close();

    code.HufCode();//���ַ�ͳ������봢�����ļ���

    ifstream ifile("source.txt");
    code.CodingSource(ifile);//���ı����б���
    infile.close();

    code.Recoding();//�Զ����ƵĻ�����������ļ����н���
    cout<<"�����ļ�����ɴ�����"<<endl;
    system("pause");
    return 0;
}