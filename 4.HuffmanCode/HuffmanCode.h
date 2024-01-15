#ifndef _HUFFMANCODE_H_
#define _HUFFMANCODE_H_

#include<iostream>
#include<fstream>
#include<vector>
#include<iomanip>
using namespace std;

typedef struct chcode//�洢�ַ��Ļ���������
{
    char ch;
    vector<bool> hufcode;
}chcode;

typedef struct Hufnode//���������Ľڵ�
{
    char ch;
    int weight;
    int parent,lchild,rchild;
    Hufnode():ch(0),weight(0),parent(0),lchild(0),rchild(0){}
}Hufnode,*HufTree;


class HuffmanCode
{
private:
    int asc_code[127]={0};//����ͳ���ļ��ַ����ִ���
    void statistic_asccode(ifstream &file);//���ļ�ͳ���ַ�Ƶ��
    void createtree(int n);//������������
    void createcode(vector<bool> &code,int n);//ͨ��dfs�����������еı���洢��������
    void select_two_small(int n,int &s1,int &s2);//�ҳ�����Ȩ����С�Ľڵ�
    char recodeing_index(int index,ifstream& infile);//�ӵ�ǰλ�ÿ�ʼ�����벢����
public:
    vector<chcode> Hcode;//�洢���ɵĻ���������
    vector<Hufnode> HT;//��Ż��������Ľڵ�

    void CreateHufCode(ifstream &file);//��ȡ�ļ���������������
    void CodingSource(ifstream &file);//���ı��ļ����ж����Ʊ���
    void Recoding();//�Ի���������Ķ������ļ����н���
    void HufCode();//���ַ�ͳ�������д���ļ�
};

void HuffmanCode::CreateHufCode(ifstream &file)//��ȡ�ļ���������������
{
    statistic_asccode(file);
    createtree(HT.size()-1);
}

void HuffmanCode::CodingSource(ifstream &infile)//���ı��ļ����ж����Ʊ���
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
                    outfile.put(bit ? '\x01' : '\x00');  // �� true ��ʾΪ '\x01'���� false ��ʾΪ '\x00'
                }
            }
        }
        infile.get(c);
    }
}

void HuffmanCode::statistic_asccode(ifstream &file)//�ַ�ͳ��
{
    char c;
    file.get(c);
    while (!file.eof())
    {
        asc_code[(int)c]++;
        file.get(c);
    }
    Hufnode node;//0��λ�ò�������
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


void HuffmanCode::createtree(int n)//������������
{
    if(n<=1) return;
    for(int i=1;i<=n-1;i++)//ʹ�����иպ���2n-1���ڵ�������
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

void HuffmanCode::createcode(vector<bool> &code,int n)//��dfs�ҵ�Ҷ�ӽ�㼴����һ���ַ��ı���
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

void HuffmanCode::select_two_small(int n,int &s1,int &s2)//�����нڵ���ѡ������Ȩ����С�Ľڵ�
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

void HuffmanCode::Recoding()//�ӻ���������Ķ������ļ������ݽ���
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

char HuffmanCode::recodeing_index(int index,ifstream &infile)//��ȡһ���ַ��Ļ��������벢���ؽ������ַ�
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
    ofile<<setw(10)<<left<<"�ַ�"<<setw(10)<<left<<"Ȩ��"<<setw(10)<<left<<"����"<<endl;
    for(int i=1;i<=n;i++)
    {
        if(HT[i].ch>=33&&HT[i].ch<=126)
            ofile<<setw(10)<<left<<HT[i].ch<<setw(10)<<left<<HT[i].weight;
        else
            ofile<<setw(10)<<left<<"���ַ�"<<setw(10)<<left<<HT[i].weight;
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