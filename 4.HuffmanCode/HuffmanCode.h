#ifndef _HUFFMANCODE_H_
#define _HUFFMANCODE_H_

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;

typedef struct chcode//存储字符的霍夫曼编码
{
    char ch;
    vector<bool> hufcode;
}chcode;

typedef struct Hufnode//霍夫曼树的节点
{
    char ch;
    int weight;
    int parent,lchild,rchild;
    Hufnode():ch(0),weight(0),parent(0),lchild(0),rchild(0){}
}Hufnode,*HufTree;


class HuffmanCode
{
private:
    int asc_code[127]={0};//用于统计文件字符出现次数
    void statistic_asccode(ifstream &file);//读文件统计字符频率
    void createtree(int n);//创建霍夫曼树
    void createcode(vector<bool> &code,int n);//通过dfs将霍夫曼树中的编码存储至容器中
    void select_two_small(int n,int &s1,int &s2);//找出两个权重最小的节点
    char recodeing_index(int index,ifstream& infile);//从当前位置开始读编码并解码
public:
    vector<chcode> Hcode;//存储生成的霍夫曼编码
    vector<Hufnode> HT;//存放霍夫曼树的节点

    void CreateHufCode(ifstream &file);//读取文件创建霍夫曼编码
    void CodingSource(ifstream &file);//对文本文件进行二进制编码
    void Recoding();//对霍夫曼编码的二进制文件进行解码
    void HufCode();//将字符统计与编码写入文件
};

void HuffmanCode::CreateHufCode(ifstream &file)//读取文件创建霍夫曼编码
{
    statistic_asccode(file);
    createtree(HT.size()-1);
}

void HuffmanCode::CodingSource(ifstream &infile)//对文本文件进行二进制编码
{
    ofstream outfile("code.dat",ios::binary);
    char c;
    infile.get(c);
    while(!infile.eof())
    {
        for(auto &i:Hcode)
        {
            if(i.ch==c)
            {
                for (bool bit : i.hufcode) 
                {
                    outfile.put(bit ? '\x01' : '\x00');  // 将 true 表示为 '\x01'，将 false 表示为 '\x00'
                }
            }
        }
        infile.get(c);
    }
}

void HuffmanCode::statistic_asccode(ifstream &file)//字符统计
{
    char c;
    file.get(c);
    while (!file.eof())
    {
        asc_code[(int)c]++;
        file.get(c);
    }
    Hufnode node;//0号位置不存数据
    HT.push_back(node);
    for(int i=0;i<127;i++)
    {
        if(asc_code[i]!=0)
        {
            node.ch=(char)i;
            node.weight=asc_code[i];
            HT.push_back(node);
        }
    }
}


void HuffmanCode::createtree(int n)//创建霍夫曼树
{
    if(n<=1) return;
    for(int i=1;i<=n-1;i++)//使容器中刚好有2n-1个节点存放数据
    {
        Hufnode node;
        HT.push_back(node);
    }
    int s1,s2;
    for(int i=n+1;i<=2*n-1;i++)
    {
        select_two_small(i-1,s1,s2);
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[s1].parent=HT[s2].parent=i;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
    vector<bool> code;
    createcode(code,2*n-1);
}

void HuffmanCode::createcode(vector<bool> &code,int n)//用dfs找到叶子结点即生成一个字符的编码
{
    if(HT[n].lchild==0)
    {
        chcode c;
        c.ch=HT[n].ch;
        c.hufcode=code;
        Hcode.push_back(c);
        return;
    }
    code.push_back(false);
    createcode(code,HT[n].lchild);
    code.pop_back();
    code.push_back(true);
    createcode(code,HT[n].rchild);
    code.pop_back();
}

void HuffmanCode::select_two_small(int n,int &s1,int &s2)//在所有节点中选出两个权重最小的节点
{
    s1=s2=0;
    for(int i=1;i<=n;i++)
    {
        if(HT[i].parent!=0) continue;
        if(s1==0) s1=i;
        else if(HT[i].weight<=HT[s1].weight)
        {
            s2=s1;
            s1=i;
        }
        else if(s2==0||HT[i].weight<HT[s2].weight)
        {
            s2=i;
        }
    }
}

void HuffmanCode::Recoding()//从霍夫曼编码的二进制文件读数据解码
{
    ifstream infile("code.dat",ios::binary);
    ofstream outfile("recode.txt");
    char c=recodeing_index(HT.size()-1,infile);
    while (c!=0)
    {
        outfile.put(c);
        c=recodeing_index(HT.size()-1,infile);
    }
    infile.close();
    outfile.close();
}

char HuffmanCode::recodeing_index(int index,ifstream &infile)//读取一个字符的霍夫曼编码并返回解码后的字符
{
    if(HT[index].lchild==0)
    {
        return HT[index].ch;
    }
    char c;
    infile.get(c);
    if(infile.eof()) return 0;
    else if(c==0)
    {
        return recodeing_index(HT[index].lchild,infile);
    }
    else
    {
        return recodeing_index(HT[index].rchild,infile);
    }
}

void HuffmanCode::HufCode()
{
    ofstream ofile("Huffman.txt");
    int n=HT.size()/2;
    ofile<<setw(10)<<left<<"字符"<<setw(10)<<left<<"权重"<<setw(10)<<left<<"编码"<<endl;
    for(int i=1;i<=n;i++)
    {
        if(HT[i].ch>=33&&HT[i].ch<=126)
            ofile<<setw(10)<<left<<HT[i].ch<<setw(10)<<left<<HT[i].weight;
        else
            ofile<<setw(10)<<left<<"空字符"<<setw(10)<<left<<HT[i].weight;
        for(auto &j:Hcode)
        {
            if(j.ch==HT[i].ch)
            {
                for(auto k:j.hufcode)
                {
                    ofile<<(int)k;
                }
            }
        }
        ofile<<endl;
    }
    ofile.close();
}

#endif