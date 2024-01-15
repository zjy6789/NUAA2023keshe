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

    code.HufCode();//将字符统计与编码储存在文件中

    ifstream ifile("source.txt");
    code.CodingSource(ifile);//对文本进行编码
    infile.close();

    code.Recoding();//对二进制的霍夫曼编码的文件进行解码
    cout<<"所需文件已完成创建！"<<endl;
    system("pause");
    return 0;
}