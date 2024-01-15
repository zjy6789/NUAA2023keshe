#ifndef _MAZE_H_
#define _MAZE_H_

#include<iostream>
#include<vector>
#include<fstream>
#include<cstdlib>
#include<ctime>

using namespace std;

#define L 30

class Maze
{
private:
    int map[L][L]={0};//��ͼ����
public:
    pair<int,int> start,end;//�Թ��������յ�
    Maze();
    void Save_to_file();
};




Maze::Maze()//���캯�����Զ�����һ�����Թ�
{
    //����Prim�㷨���ɵ�����Թ�
    //����Χ����Ϊ·��������Ч�ı�������һ��ǽ�壬����ֹ����
    for (int i = 0; i < L; i++)
    {
        map[i][0] = 1;
        map[0][i] = 1;
        map[L - 1][i] = 1;
        map[i][L - 1] = 1;
    }

    //ǽ���У�����X , Y
    vector<int> X;
    vector<int> Y;

    //��ȡ��ʼֵ
    X.push_back(2);
    Y.push_back(2);
    //��ʼ�����������
    srand(time(0));

    //��ǽ����Ϊ��ʱ����ѭ��
    while (X.size())
    {
        //��ǽ���������ȡһ��
        int r = rand() % X.size();
        int x = X[r];
        int y = Y[r];

        //�ж����������ĸ������Ƿ�Ϊ·
        int count = 0;
        for (int i = x - 1; i < x + 2; i++)
        {
            for (int j = y - 1; j < y + 2; j++)
            {
                if (abs(x - i) + abs(y - j) == 1 && map[i][j] > 0)
                    ++count;
            }
        }

        if (count <= 1)
        {
            map[x][y] = 1;
            //��ǽ�����в����µ�ǽ
            for (int i = x - 1; i < x + 2; i++)
            {
                for (int j = y - 1; j < y + 2; j++)
                {
                    if (abs(x - i) + abs(y - j) == 1 && map[i][j] == 0)
                    {
                        X.push_back(i);
                        Y.push_back(j);
                    }
                }
            }
        }

        //ɾ����ǰǽ
        X.erase(X.begin() + r);
        Y.erase(Y.begin() + r);
    }

    //�����Թ�������
    map[2][1] = 3;
    for (int i = L - 3; i >= 0; i--)
    {
        if (map[i][L - 3] == 1)
        {
            map[i][L - 2] = 4;
            end={i,L-2};
            break;
        }
    }
    start={2,1};

    Save_to_file();//���Թ��������ı��ļ���
}

void Maze::Save_to_file()
{
    ofstream ofile("mazemap.txt");
    for(int i=0;i<L;i++)
    {
        for(int j=0;j<L;j++)
        {
            ofile<<map[i][j]<<" ";
        }
        ofile<<endl;
    }
    ofile<<start.first<<" "<<start.second<<" "<<end.first<<" "<<end.second;
    ofile.close();
}


#endif